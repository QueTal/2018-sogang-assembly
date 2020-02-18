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
int findOpcode(char*, int);
void makeHistory(char input[]);
void printHistory();
void freeHistory();
void freeHash();
int type(char*);
void pass1(char*);
void pass2(char*);
void hashSymbol(char*, int);
int retFormat(char*, int);
void printSymbol();
void findRegValue(char*, char*, int*, int*);
int findSymbol(char*);
int findSymAddr(char*);
void ObjectFile(char*);
void freeSymTable();
void fileDelete();

long long finish = -1;
unsigned char memo[1048576] = {0, };
int assembleFlag = 0;
int lineLength = 0;
unsigned int Length = 0, faddr = 0;

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

typedef struct _symbol_{
	char symbol[20];
	unsigned int addr;
	struct _symbol_* link;
}Symbol;
Symbol* sym_head[26] = {NULL,};
