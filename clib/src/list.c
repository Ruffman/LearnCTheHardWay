#include "lcthw/dbg.h"
#include "lcthw/list.h"
#include <assert.h>

void List_check_state(List* list)
{
	assert(List_count(list) >= 0 && "List had count of less than 0");
	if (List_count(list) > 1) {
		assert(List_first(list) != NULL &&
				"List bigger than 1 has invalid first item");
		assert(List_last(list) != NULL &&
				"List bigger than 1 has invalid last item");
	}
}

List* List_create()
{
	return calloc(1, sizeof(List));
}

void List_destroy(List* list)
{
	assert(list != NULL && "Invalid list parameter");
	LIST_FOREACH(list, first, next, cur) {
		if (cur->prev) {
			free(cur->prev);
		}
	}
	
	free(list->last);
	free(list);
}

void List_clear(List* list)
{
	assert(list != NULL && "Invalid list parameter");
	LIST_FOREACH(list, first, next, cur) {
		free(cur->value);
	}
}

void List_clear_destroy(List* list)
{
	assert(list != NULL && "Invalid list parameter");
	LIST_FOREACH(list, first, next, cur) {
		if (cur->value) {
			free(cur->value);
		}
		if (cur->prev) {
			free(cur->prev);
		}
	}
	free(list->last);
	free(list);
}

void List_push(List* list, void* value)
{
	List_check_state(list);
	assert(list != NULL && "Invalid list parameter");
	ListNode* node = calloc(1, sizeof(ListNode));
	check_mem(node);
	
	node->value = value;
	
	if (list->last == NULL) {
		list->first = node;
		list->last = node;
	} else {
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
	}
	list->count++;
	List_check_state(list);
error:
	return;
}

void* List_pop(List* list)
{
	List_check_state(list);
	assert(list != NULL && "Invalid list parameter");
	ListNode* node = list->last;
	List_check_state(list);
	return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List* list, void* value)
{
	List_check_state(list);
	assert(list != NULL && "Invalid list parameter");
	ListNode* node = calloc(1, sizeof(ListNode));
	check_mem(node);
	
	node->value = value;
	
	if (list->first == NULL) {
		list->first = node;
		list->last = node;
	} else {
		node->next = list->first;
		list->first->prev = node;
		list->first = node;
	}
	list->count++;
	List_check_state(list);
error:
	return;
}

void* List_shift(List* list)
{
	List_check_state(list);
	assert(list != NULL && "Invalid list parameter");
	ListNode* node = list->first;
	List_check_state(list);
	return node != NULL ? List_remove(list, node) : NULL;
}

void* List_remove(List* list, ListNode* node)
{
	List_check_state(list);
	assert(list != NULL && "Invalid list parameter");
	assert(node != NULL && "Invalid node-pointer to remove");
	void* result = NULL;
	
	check(list->first && list->last, "List is empty");
	check(node, "Node can't be NULL");
	
	if (node == list->first && node == list->last) {
		list->first = NULL;
		list->last = NULL;
	} else if (node == list->first) {
		list->first = node->next;
		check(list->first != NULL, "Invalid list, got a NULL as first");
		list->first->prev = NULL;
	} else if (node == list->last) {
		list->last = node->prev;
		check(list->last != NULL, "Invalid list, got a NULL as last");
		list->last->next = NULL;
	} else {
		ListNode* before = node->prev;
		ListNode* after = node->next;
		before->next = after;
		after->prev = before;
	}
	list->count--;
	result = node->value;
	free(node);
	List_check_state(list);
error:
	return result;
}

List* List_copy(List* list)
{
	List_check_state(list);
	assert(list != NULL && "Invalid list parameter");
	List* newList = List_create();
	check_mem(newList);
	
	LIST_FOREACH(list, first, next, cur) {
		List_push(newList, cur->value);
	}
	check(List_count(list) == List_count(newList), "Failed to copy list");
	List_check_state(list);
	
	return newList;
error:
	if (newList) free(newList);
	return NULL;
}

List* List_join(List* first, List* second)
{
	assert(first != NULL && "Invalid first argument");
	assert(second != NULL && "Invalid second argument");
	List_check_state(first);
	List_check_state(second);
	
	List* newList = List_copy(first);
	check_mem(newList);
	
	LIST_FOREACH(second, first, next, cur) {
		List_push(newList, cur->value);
	}
	check(List_count(newList) == List_count(first) + List_count(second), 
			"Invalid element count after joining");
	
	List_destroy(first);
	List_destroy(second);
	List_check_state(newList);
	
	return newList;
error:
	if (newList) free(newList);
	return NULL;
}

