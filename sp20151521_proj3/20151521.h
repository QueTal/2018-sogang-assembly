#include<sys/stat.h>
#include<dirent.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

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

typedef struct _linkedList_{
	char name[20];
	int addr;
	int length;
	struct _linkedList_* next;
}LinkedList;
LinkedList* estab_head[20] = {NULL,};
LinkedList* estabHead = NULL;

typedef struct _breakPoint_{
	int addr;
	struct _breakPoint_* next;
}bp_list;
bp_list* bp_head;

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
void loader_pass1(char*, int);
int externSymTab(char*, int , int);
void show_estab();
void freeLinked_estab();
int loader_pass2();
LinkedList* find_externSym(char* );
char make_hex(char*, int);
int run(int*);
int target_addr(int, int);
void print_reg();
void store(unsigned int , unsigned int);
int search_bp(int);
void bp(int);
void store_bp(int);
int find_bp(int);
void freeEstab();

long long finish = -1;
unsigned char memo[1048576] = {0, };
int assembleFlag = 0;
int lineLength = 0;
unsigned int Length = 0, faddr = 0;
unsigned int progaddr[3] = {0,};
unsigned int csaddr = 0;
unsigned int total_cslth = 0;
unsigned int temp_cslth = 0;
char filename[4][20] = {0,};
static int regist[8] = {0,};
int loadFlag = 0;
