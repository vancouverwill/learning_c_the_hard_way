#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

int DEBUG = 0;
struct Address {
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

struct Database {
    int max_rows;
    struct Address rows[];
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void Database_close(struct Connection *conn);
int Database_size(int rows);

void die(const char *message, struct Connection *conn)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    Database_close(conn);
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
	// first check row count so we know how big db is and how much memory to allocate
	int rows = 0;
	int rca = fread(&rows, sizeof(int), 1, conn->file);
    if (rca != 1) die("Failed to load database size.", conn);
	printf("rows:%d", rows);
    conn->db = malloc(Database_size(rows));
    if(!conn->db) die("Memory error with database", conn);
	
	/* Seek to the beginning of the file */
   	fseek(conn->file, 0, SEEK_SET);
    int rc = fread(conn->db, Database_size(rows), 1, conn->file);
    if (rc != 1) die("Failed to load database.", conn);
}

struct Connection *Database_open(const char *filename, char mode, int max_rows)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn) die("Memory error with connection", conn);

    if(mode == 'c') {
    	conn->db = malloc(Database_size(max_rows));
		conn->db->max_rows = max_rows;
    	if(!conn->db) die("Memory error with database", conn);
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if(conn->file) {
            Database_load(conn);
        }
    }

    if (!conn->file) die("Failed to open the file", conn);
	printf("safely setup conection! rows:%d\n", conn->db->max_rows);
    return conn;
}

void Database_close(struct Connection *conn)
{
    if (DEBUG) {
		printf("Database_close start\n");
	}
	if(conn) {
        if(conn->file) fclose(conn->file);
        if(conn->db) free(conn->db);
        free(conn);
    }
    if (DEBUG) {
		printf("Database_close end\n");
	}
}

int Database_size(int max_rows)
{
	return sizeof(int) + sizeof(struct Address) * max_rows;
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file);
    int rc = fwrite(conn->db, Database_size(conn->db->max_rows), 1, conn->file);
    if(rc != 1) die("Failed to write database.", conn);

    rc = fflush(conn->file);
    if(rc == -1) die("Cannot flush database.", conn);
    if (DEBUG) {
		printf("Database_write end. size:%lu\n", sizeof(struct Database));
	}
}

void Database_create(struct Connection *conn)
{
    int i = 0;
    
    for(i = 0; i < conn->db->max_rows; i++) {
        // make a prototype to initialize it
        struct Address addr = {.id = i, .set = 0};
        // then just assign it
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    if(addr->set) die("Already set, delete it first", conn);

    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, sizeof(addr->name) - 2);
    // demonstrate the strncpy bug
    if(!res) die("Name copy failed", conn);

	printf("res:%c of saving size:%lu\n", *res, sizeof(addr->name));
    if (sizeof(name) > 0) {
        addr->name[sizeof(name) - 1]= '\0';
    }
    
    res = strncpy(addr->email, email, sizeof(addr->email) - 1);
    if(!res) die("Email copy failed", conn);
	printf("res:%c\n", *res);
    if (sizeof(email) > 0) {
        addr->name[sizeof(email) - 1]= '\0';
    }
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if (addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set", conn);
    }
}

void Database_delete(struct Connection *conn, int id)
{
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    for (i = 0; i < conn->db->max_rows; i++) {
        struct Address *cur = &db->rows[i];

        if(cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
	int max_rows = 0;

    char *filename = argv[1];
    char action = argv[2][0];

	if (action == 'c' && argc > 3) {
		max_rows = atoi(argv[3]);
	} else if (action == 'c') {
		max_rows = 100;
	}
	printf("file:%s  mode:%c\n\n",filename, action);
    struct Connection *conn = Database_open(filename, action, max_rows);
    int id = 0;

    if(argc < 3)
		die("USAGE: ex17 <dbfile> <action> [action params]", conn);
    if (argc > 3) id = atoi(argv[3]);
    if (id >= MAX_ROWS) die("There's not that many records.", conn);

    switch(action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if(argc != 4) die("Need id to get", conn);

            Database_get(conn, id);
            break;

        case 's':
            if(argc != 6) die("Need id, name, email to set", conn);

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if(argc != 4) die("Need id to delete", conn);

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list", conn);
    }

    Database_close(conn);

    return 0;
}
