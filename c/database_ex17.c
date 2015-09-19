#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>

#define MAX_ROWS 512
#define MAX_DATA 100

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
	FILE *file;
	struct Database *db;
};

//note: errno, perror and exit(1)
//first version
void die(char *message)
{
	if(errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	exit(1);
}

//void die(const char *format, ...)
//{
//	va_list arg;
//
//	va_start(arg, format);
//	vprintf(format, arg);
//	va_end(arg);
//}

void Address_print(struct Address *addr)
{
	printf("id %d, name %s, email %s\n", addr->id, addr->name, addr->email);
}

/*database initialize*/
void Database_create(struct Connection *conn)
{
	int i;

	for(i = 0; i < MAX_ROWS; i++) {
		struct Address addr = {
			.id = i,
			.set = 0
		};

		conn->db->rows[i] = addr;
	}
}

void Database_load(struct Connection *conn)
{
	int read_count = 0;
	read_count = fread(conn->db, sizeof(struct Database), 1, conn->file);
	if(read_count != 1)
		die("Failed to load database");
}

/* create new file and allocate database */
struct Connection *Database_open(char *name, char mode)
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	if(!conn)
		die("conn memory alloc failed");

	conn->db = malloc(sizeof(struct Database));
	if(!conn->db)
		die("db memory alloc failed");
	
	if(mode == 'c') {
		//create a new file named name
		conn->file = fopen(name, "w");
	} else {
		//open a file with read and write permission
		conn->file = fopen(name, "r+");
		if(conn->file)
			Database_load(conn);
	}

	if(!conn->file)
		die("Failed to open file");

	return conn;
}

/*write database to file*/
void Database_write(struct Connection *conn)
{
	int write_count = 0;
	int ret = 0;

	if(conn) {
		if(conn->file)
			rewind(conn->file);
		else
			die("conn->file is null");		

		if(conn->db){
			write_count = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
			if(write_count != 1)
				die("fwrite to file failed");
			ret = fflush(conn->file);
			if(ret)
				die("fflush file failed");
		} else {
			die("conn->db is null");
		}
	} else {
		die("conn is null");	
	}
}

void Database_set(struct Connection *conn, int id, char *name, char *email)
{
	struct Address *addr = &conn->db->rows[id];
    if(addr->set) die("Already set, delete it first");

    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, MAX_DATA);
    // demonstrate the strncpy bug
    if(!res) die("Name copy failed");

    res = strncpy(addr->email, email, MAX_DATA);
    if(!res) die("Email copy failed");
}

void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = &conn->db->rows[id];

	if(addr->set)
		Address_print(addr);
	else
		die("ID is not set");
}

void Database_delete(struct Connection *conn, int id)
{
	struct Address *addr = &conn->db->rows[id];

	if(addr)
		addr->id = 0;
}

void Database_close(struct Connection *conn)
{
	if(conn) {
		if(conn->db)
			free(conn->db);
		if(conn->file)
			fclose(conn->file);
		free(conn);
	}
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    for(i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &db->rows[i];

        if(cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
    if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0;

    if(argc > 3) id = atoi(argv[3]);
    if(id >= MAX_ROWS) die("There's not that many records.");

    switch(action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if(argc != 4) die("Need an id to get");

            Database_get(conn, id);
            break;

        case 's':
            if(argc != 6) die("Need id, name, email to set");

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if(argc != 4) die("Need id to delete");

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(conn);

    return 0;
}
