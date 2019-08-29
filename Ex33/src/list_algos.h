#ifndef _lcthw_list_h_
#define _lcthw_list_h_

#include <stdlib.h>

typedef int (*List_compare) (const void* a, const void* b);

struct ListNode;

typedef struct ListNode {
	struct ListNode* next;
	struct ListNode* prev;
	void* value;
} ListNode;

typedef struct List {
	int count;
	ListNode* first;
	ListNode* last;
	
} List;

void List_check_state(List* list);

List* List_create();
void List_destroy(List* list);
void List_clear(List* list);
void List_clear_destroy(List* list);

#define List_count(A) ((A)->count)
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

void List_push(List* list, void* value);
void* List_pop(List* list);
void List_unshift(List* list, void* value);
void* List_shift(List* list);

void* List_remove(List* list, ListNode* node);
List* List_copy(List* list);

// Appends the second list to the end of the first. Returns a new list and 
// destroys the old ones. Returns NULL on error
List* List_join(List* first, List* second);

int List_bubble_sort(List* list, List_compare);
List* List_merge_sort(List* list, List_compare);

#define LIST_FOREACH(L, S, N, V) ListNode *_node = NULL;\
								ListNode* V = NULL;\
				for(V = _node = L->S; _node != NULL; V = _node = _node->N)

#endif
