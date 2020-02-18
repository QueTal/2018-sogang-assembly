#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>

void help();
void dir();
void dump(long long, long long);
void edit(long long, long long);
void fill(long long, long long, long long);
void makeHash();
void hashNode(int, int, char*, char*);
void opcodelist();
void findOpcode(char*, int);
void makeHistory(char input[]);
void printHistory();
void freeHistory();
void freeHash();

long long finish = -1;
unsigned char memo[1048576] = {0, };

typedef struct _table_{
	int opcode;
	char mnemo[10];
	char format[10];
	struct _table_* next;
}Table;

Table* head[20] = {NULL,};

typedef struct _history_{
	char inst[256];
	struct _history_* link;
}History;
History* his_head = NULL;
