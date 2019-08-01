#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 128

struct Address {
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];
};

struct Database {
	struct Address rows[MAX_ROWS];
};

struct Connection {
	FILE* file;
	struct Database* db;
};

void die(const char* message)
{
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}
}

void print_address(struct Address* addr) 
{
	printf("Address No.: %d; %s; %s\n", addr->id, addr->name, addr->email);
}

void load_database(struct Connection* conn)
{
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if (rc != 1)
		die("Failed to load database");
}

struct Connection* open_database(const char* filename, char mode)
{
	struct Connection* conn = malloc(sizeof(struct Connection));
	if (!conn)
		die("Failed to create a connection");
	
	conn->db = malloc(sizeof(struct Database));
	if (!conn->db)
		die("Failed to create Database");
	
	if (mode == 'c') {
		conn->file = fopen(filename, "w");
	} else {
		conn->file = fopen(filename, "r+");
		
		if (conn->file) {
			load_database(conn);
		}
	}
	
	if (!conn->file) {
		die("Failed to open the file");
	}
	
	return conn;
}

void close_database(struct Connection* conn)
{
	if (conn) {
		if (conn->file) {
			fclose(conn->file);
		}
		if (conn->db) {
			free(conn->db);
		}
		free(conn);
	}
}

void write_database(struct Connection* conn)
{
	rewind(conn->file);
	
	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if (rc != 0)
		die("Failed to write database");
	
	rc = fflush(conn->file);
	if (rc == -1)
		die("Cannot flush database");
}

void delete_database_address(struct Connection* conn, int id)
{
	struct Address addr = { .id = id, .set = 0 };
	conn->db->rows[id] = addr;
}

void list_database(struct Connection* conn)
{
	struct Database* db = conn->db;
	
	for (int i = 0; i < MAX_ROWS; ++i) {
		struct Address* cur = &db->rows[i];
		
		if (cur->set) {
			print_address(cur);
		}
	}
}

void create_database(struct Connection* conn)
{
	for (int i = 0; i < MAX_ROWS; ++i) {
		struct Address addr = { .id = i, .set = 0 };
		
		conn->db->rows[i] = addr;
	}
}

void set_database(struct Connection* conn, int id, const char* name, 
					const char* email)
{
	struct Address* addr = &conn->db->rows[id];
	if (addr->set)
		die("Already set, delete it first");
	
	addr->set = 1;
	char* res = strncpy(addr->name, name, MAX_DATA);
	
	if (!res)
		die("Name copy failed");
		
	res = strncpy(addr->email, email, MAX_DATA);
	if (!res)
		die("Name copy failed");
}

void get_database(struct Connection *conn, int id)
{
	struct Address* addr = &conn->db->rows[id];
	
	if (addr->set) {
		print_address(addr);
	} else {
		die("ID is not set");
	}
}

int main(int argc, char* argv[])
{
	if (argc < 3)
		die("USAGE: ex17 <dbfile> <action> [action params]");
	
	char* filename = argv[1];
	char action = argv[2][0];
	struct Connection* conn = open_database(filename, action);
	int id = 0;
	
	if (argc > 3)
		id = atoi(argv[3]);
	
	if (id >= MAX_ROWS)
		die("There are not that many records");
	
	switch (action) {
		case 'c':
			create_database(conn);
			write_database(conn);
			break;
		case 'g':
			if (argc != 4)
				die("Need an id to get");
			
			get_database(conn, id);
			break;
		case 's':
			if (argc != 6)
				die("Need id, name, email to set");
			
			set_database(conn, id, argv[4], argv[5]);
			write_database(conn);
			break;
		case 'd':
			if (argc != 4)
				die("Need an id to delete");
			
			delete_database_address(conn, id);
			write_database(conn);
			break;
		case 'l':
			list_database(conn);
			break;
		default:
			die("Invalid action: c=create, g=get, s=set, d=del, l=list");
	}
	
	close_database(conn);
	
	return 0;
}
