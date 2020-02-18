#include"20151521.h"

/*-----------------------------------*/
/*함수 : main*/
/*목적 : 사용자로부터 입력을 받고 명령에
	맞는 함수를 실행한다.*/
/*리턴값 : 제대로 종료될 시 0*/
/*-----------------------------------*/
int main(void) {
	char ch[256] = { 0, }, copy[256] = { 0, };
	int i, j, flag = 0, key = 0, bp_flag = 0;
	long long start = 0, end = 0, value = 0;
	unsigned int addr = 0;
	char *tok, *real, *temp, *add;
	char name[20];

	/* make hash table */
	makeHash();
	while (1) {
		printf("sicsim> ");

		/* save the input */
		for (i = 0; i < 256; i++) {
			scanf("%c", &ch[i]);
			/*count the number of ','*/
			if (ch[i] == ',')	flag++;
			//prevent segmentation fault
			if (ch[0] == '\n')	break;
			//change last enter to null
			if (ch[i] == '\n') {
				ch[i] = '\0';
				break;
			}
		}
		
		/* copying the input value to other array with some transforming */
		for(i = 0, j = 0; i < strlen(ch); i++, j++){
			copy[j] = ch[i];
			if(ch[i] == '\t')	copy[j] = ' ';
			if(ch[i] == ','){
				j++; copy[j] = ' ';
			}
		}	
	
		/* trim the input data by tokenize */
		tok = strtok (copy, " ");
		real = tok;
		if(real == NULL){
			printf("Invalid input!\n");
			continue;
		}
		/*save the mnemonic in variable real */
		while (1) {
			/* save the arguments in variable tok if the instruction has*/
			tok = strtok (NULL, " ");

			/* instruction without argument */
			if (tok == NULL) { 
				/* find the same menmonic by comparing with variable real*/
				if (strcmp (real, "help") == 0 || strcmp (real, "h") == 0) {
					/* save the instruction and execute the function */
					makeHistory(ch);
					help();
					break;
				}
				else if (strcmp (real, "dir") == 0 || strcmp (real, "d") == 0) {
					/* save the instruction and execute the function */
					makeHistory(ch);
					dir();
					break;
				}
				else if (strcmp (real, "history") == 0 || strcmp (real, "hi") == 0) {
					/* save the instruction and execute the function */
					makeHistory(ch);
					printHistory();
					break;
				}
				else if (strcmp (real, "quit") == 0 || strcmp (real, "q") == 0){
					/* free the allocated memory and exit the program */
					freeHistory(); 
					freeHash();
					freeSymTable();
					freeEstab();
					return 0;
				}
				else if(strcmp(real, "opcodelist") == 0){
					/* save the instruction and execute the function */
					makeHistory(ch);
					opcodelist();
					break;
				}
				else if(strcmp(real, "dump") == 0 || strcmp(real, "du") == 0){
					/* save the instruction and execute the function */
					makeHistory(ch);
					dump(finish + 1, finish + 160);
					finish += 160;
					break;
				}
				else if(strcmp(real, "reset") == 0){
					/* save the instruction and initialize the memory */
					makeHistory(ch);
					memset(memo, 0, sizeof(memo)); 
					break;
				}
				else if(strcmp(real, "symbol") == 0){
					if(assembleFlag == 0){
						printSymbol();
						makeHistory(ch);
					}
					else printf("The symbol table is empty!\n");
					break;
				}
				else if(strcmp(real, "run") == 0){
					
					run(&bp_flag);
					 
					break;
				}
				else if(strcmp(real, "bp") == 0){
					bp(1);
					break;
				}
				else {
					/* print the error message if the input is wrong */
					printf ("Invalid input!\n");
					break;
				}
			}

			/*instruction with argument*/
			else { 
				/* find the same menmonic by comparing with variable real */
				if(strcmp(real, "dump") == 0 || strcmp(real, "du") == 0){
					real = tok;
					tok = strtok(NULL, " ");
					/* save the argument to real and tok */
					/* for one argument*/
					if(flag == 0 && tok == NULL && real != NULL){
					/* not consider the value of real is right yet */
						start = strtol(real, &temp, 16);
						/* change the string to hexadecimal number to execute the function dump */
						if(strcmp(temp, "\0") == 0 && start >= 0 && start <= 0xFFFFF){ 
							makeHistory(ch);
							/* save the last address to variable finish */
							finish = 0x9F + start;
							dump(start, finish);
							break;
						}
						else{
						/* print the error message if the input is wrong */
							printf("Invalid input!\n");
							break;
						}
					}
					/*for two argument*/
					else if(flag == 1 && tok != NULL && real != NULL){
						start = strtol(real, &temp, 16);
						if(strcmp(temp, ",") != 0 && strcmp(temp, "") != 0){
							/* if there is any other character that does not handle in hexadecimal */
							/* print the error message if the input is wrong */
							printf("Invalid input!\n");
							break;
						}
						end = strtol(tok, &temp, 16);
						if(strcmp(temp, ",") == 0)	end = strtol(tok, &temp, 16);
						if(strcmp(temp, "\0") == 0 && start >= 0 && end <= 0xFFFFF && start < end){
							/* if there no error point when transform string to hexadecimal */
							/* if the range of input is valid*/
							makeHistory(ch);
							finish = end;
							dump(start, end);
							break;
						}
						else{
							/* print the error message if the input is wrong */
							printf("Invalid input!\n");
							break;
						}
					}
					else{
						/* print the error message if the input is wrong */
						printf("Invalid input!\n");
						break;
					}
				}
				/*execute fill instruction*/
				else if(strcmp(real, "fill") == 0 || strcmp(real, "f") == 0){
					/* save the argument to real, add, tok */
					real = tok;
					tok = strtok(NULL, " ");
					add = strtok(NULL, " ");
					if(flag == 2 && real != NULL && tok != NULL && add != NULL){
						start = strtol(real, &temp, 16);
						if(strcmp(temp, ",") != 0){
							/* if there is any other character that does not handle in hexadecimal */
							/* print the error message if the input is wrong */
							printf("Invalid input!\n");
							break;
						}
						end = strtol(tok, &temp, 16);
						if(strcmp(temp, ",") != 0){
							/* if there is any other character that does not handle in hexadecimal */
							/* print the error message if the input is wrong */
							printf("Invalid input!\n");
							break;
						}
						value = strtol(add, &temp, 16);
						if(strcmp(temp, "\0") == 0 && start >= 0 && end <= 0xFFFFF && start <= end && 0 <= value && value <= 0xFF){
							/* if the instruction is valid, save the instruction to the history and execute the function */
							makeHistory(ch);
							fill(start, end, value);
							break;	
						}
						else{
							/* print the error message if the input is wrong */
							printf("Invalid input!\n");
							break;
						}
					}
				}
				/*execute edit instruction*/
				else if(strcmp(real, "edit") == 0 || strcmp(real, "e") == 0){
					/* save the arguments to the variables */
					real = tok;
					tok = strtok(NULL, " ");
					if(flag == 1 && real != NULL && tok != NULL){
						start = strtol(real, &temp, 16);
						if(strcmp(temp, ",") != 0){
							/* print the error message if the input is wrong */
							printf("Invalid input!\n");
							break;
						}
						value = strtol(tok, &temp, 16);
						if(strcmp(temp, "\0") == 0 && start >= 0 && start <= 0xFFFFF && value <= 0xFF && 0 <= value){
							/* if the instruction is valid, save the instruction to the history and execute the function */
							makeHistory(ch);
							edit(start, value);
							break;
						}
						else{
						/* print the error message if the input is wrong */
							printf("Invalid input!\n");
							break;
						}
					}
					else{
					/* print the error message if the input is wrong */
						printf("invalid input!\n");
						break;
					}
				}

				/*execute opcode instruction*/
				else if(strcmp(real, "opcode") == 0){
					for(i = 0; i < strlen(tok); i++){
						/* add the ascii code and mod the value and save it to the variable to make key value */
						if(tok[i] >= 65 && tok[i] <= 90)	key += (int)tok[i];
						else{
							/* print the error message if the input is wrong */
							printf("Invalid input!\n");
							flag = 1;
							break;
						}
					}
					if(flag != 1){
						/* if the instruction is valid, save the instruction to the history and execute the function */
						makeHistory(ch);
						if(findOpcode(tok, (int)(key % 20)) == 1)	printf("Invalid input!\n");
						else printf("opcode is %-.2X.\n", findOpcode(tok, (int)(key % 20)));
					}
					break;
				}
				else if(strcmp(real, "type") == 0){
					if(type(tok) == 0)	makeHistory(ch);
					break;
				}
				else if(strcmp(real, "assemble") == 0){
					assembleFlag = 0;
					freeSymTable();
					pass1(tok);
					if(assembleFlag == 1){
						printf("assemble failure!\n");
						freeSymTable();
						fileDelete();
						break;
					}
					pass2(tok);
					if(assembleFlag == 1){
						printf("assemble failure!\n");
						real = strtok(tok, ".");
						strcat(real, ".lst");
						remove(real);
						freeSymTable();
						fileDelete();
						break;
					}
					ObjectFile(tok);
					fileDelete();
					if(assembleFlag != 1) makeHistory(ch);
					real = strtok(tok, ".");
					printf("output file: [%s.lst], [%s.obj]\n", real, real);
					break;
				}
				else if(strcmp(real, "progaddr") == 0){
					progaddr[0] = strtol(tok, &temp, 16);
					if(strcmp(temp, "") != 0){
						printf("Invalid progaddr address\n");
						progaddr[0] = 0;
					}
					else printf("\nProgram starting address set to 0x%X.\n\n", progaddr[0]);
					break;
				}
				else if(strcmp(real, "loader") == 0){
					/*save the filename*/
					i = 0;
					while(i < 3){
						strcpy(name, tok);
						strcpy(filename[i], name);
						tok = strtok(NULL, " ");
						if(tok == NULL) break;
						i++;
					}
					/*pass 1*/
					j = 0;	
					while(j <= i){
						csaddr = progaddr[j];
						loader_pass1(filename[j], j);
						j++;
					}
					/*pass 2*/
					i = 0;
					while(i < j){
						csaddr = progaddr[i];
						loader_pass2(filename[i]);
						i++;
					}
					if(!loadFlag) show_estab();

					freeEstab();
					freeLinked_estab();
					estabHead = NULL; 
					temp_cslth = total_cslth; total_cslth = 0, loadFlag = 0;
					break;
				}
				else if(strcmp(real, "bp") == 0){
					if(strcmp(tok, "clear") == 0){
						bp(0);
						break;
					}

					addr = strtol(tok, &temp, 16);
					if(!search_bp(addr)){
						if(strcmp(temp, "") != 0)	printf("\nbp operand error\n");
						else store_bp(addr);
					}
					break;
				}
				else {
					/* print the error message if the input is wrong */
					printf("Invalid input!\n");
					break;
				}
			}
		}
		
		/*initialize variables*/
		memset(ch, 0, 256);	memset(copy, 0, 256);
		flag = 0; key = 0, addr = 0;
	}
	return 0;
}

/*---------------------------------------*/
/*함수 : help */
/*목적 : 지원하는 명령어를 모두 출력한다.*/
/*리턴 값 : 없음.*/
/*---------------------------------------*/
void help(){
	printf("h[elp]\n");
	printf("d[ir]\n");
	printf("q[uit]\n");
	printf("hi[story]\n");
	printf("du[mp] [start, end]\n");
	printf("e[dit] address, value\n");
	printf("f[ill] start, end, value\n");
	printf("reset\n");
	printf("opcode mnemonic\n");
	printf("opcodelist\n");
	printf("assemble filename\n");
	printf("type filename\n");
	printf("symbol\n");
}

/*-----------------------------------------------*/
/*함수 : dir*/
/*목적 : 디렉토리내의 파일과 디렉토리를 표시한다.*/
/*리던값 : 없음.*/
/*-----------------------------------------------*/
void dir(){
	DIR *dr = opendir(".");
	struct dirent *de;
	struct stat sb;

	while((de = readdir(dr)) != NULL){
		/* exception control */
		if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)	continue;
		stat(de->d_name, &sb);
		/* check the file whether it is directory or executable file or just file */
		if(S_ISDIR(sb.st_mode))	printf("%s/\n", de->d_name);
		else if(S_IEXEC & sb.st_mode)	printf("%s*\n", de->d_name);
		else if(S_ISREG(sb.st_mode))	printf("%s\n", de->d_name);
	}
	closedir(dr);
}

/*-----------------------------------------------------*/
/*함수 : dump*/
/*목적 : 사용자의 입력에 맞춰 메모리의 값들을 출력한다.*/
/*리턴값 : 없음.*/
/*-----------------------------------------------------*/
void dump(long long  last, long long end){
	int i = (last / 16) * 16, j = i, k = i, temp = i, cnt;
	
	/* confirm the number of line to print out */
	cnt = (end - last + 1) / 16;
	if(last % 16 != 0) cnt++;
	if(last % 16 == 1) cnt--;
	if((last / 16) != (end / 16))	cnt++;
	if(end - last == 159)	cnt--;

	while(cnt > 0){
		/* print the left most column */
		printf("%.5X ", i);
		
		/* print the middle column */
		for(; j < i + 16; j++){
			if(j < last || j > end)	printf("   ");
			else	printf("%.2X ", memo[j]);
			if(j == 1048576) 	break;
		}
		i = j;
		printf("; ");

		/* print the right most column */
		j = temp;
		for(; j < k + 16; j++){
			if(j < last || j > end)	printf(".");
			else if(32 <= memo[j] && memo[j] <= 127)	printf("%c", memo[j]);
			else printf(".");
			if(j == 1048576)	break;
		}
		k = j; temp = j;
		printf("\n");	

		cnt--;
		/* exception control */
		if(j == 1048576){
			finish = -1;
			return;
		}
	}
}

/*------------------------------------------*/
/*함수 : edit*/
/*목적 : 원하는 지점의 메모리의 값을 바꾼다.*/
/*리턴값 : 없음.*/
/*------------------------------------------*/
void edit(long long add, long long val){
	memo[add] = val;
}

/*-----------------------------------------------*/
/*함수 : fill*/
/*목적 : 원하는 메모리의 값들을 val 값으로 채운다.*/
/*리턴값 : 없음.*/
/*-----------------------------------------------*/
void fill(long long start, long long end, long long val){
	int i;
	for(i = start; i <= end; i++){
		memo[i] = val;
	}
}

/*-----------------------------------------------*/
/*함수 : makeHash*/
/*목적 : opcode.txt로 부터 정보를 읽어 hashNode로 
  	인자를 보내 hash table을 만든다.*/
/*리턴값 : 없음.*/
/*-----------------------------------------------*/
void makeHash() {
	FILE *fp = fopen ("opcode.txt", "r");
	int i, opcode, val = 0;
	char mnemo[10] = {0,}, format[10] = {0,}, buffer[30] = {0,}, *op, *temp;

	/* read the content of file line by line */
	fgets (buffer, 30, fp);
	while (!feof (fp)) {
		/* remove the '\t' to use function strtok */
		for (i = 0; i < 30; i++) {
			if (buffer[i] == '\t')	buffer[i] = ' ';
		}

		/* find and save the value by using strtok */
		op = strtok (buffer, " ");
		temp = strtok (NULL, " ");
		strcpy(mnemo, temp);
		temp = strtok (NULL, " ");
		strcpy(format, temp);
		opcode = strtol (op, &temp, 16);

		/* add the ascii code value to varibale and divide it by 20 to make the key value */
		for (i = 0; i < strlen (mnemo); i++) {
			val += mnemo[i];
		}
		val %= 20;

		/* call the function with argument to make hash table */
		hashNode (val, opcode, mnemo, format);

		/* initialize the variable to use again */
		memset(buffer, 0, 30); memset(mnemo, 0, 10); memset(format, 0, 10);
		fgets (buffer, 30, fp); val = 0;
	}
	fclose(fp);
}

/*----------------------------------------------*/
/*함수 : hashNode*/
/*목적 : 새로운 노드에 mnemonic의 정보를 저장하고
 	이를 linked list로 hash table로 만든다.*/
/*리턴값 : 없음.*/
/*----------------------------------------------*/
void hashNode (int val, int opcode, char* mnemo, char* format) {
	Table* new = (Table*)malloc(sizeof(Table));	
	Table* temp;

	/* save the argument to the new node */
	new->opcode = opcode;
	strcpy(new->mnemo, mnemo);
	strcpy(new->format, format);
	new->next = NULL;

	/* connect the node to head and make linked list */
	if(head[val] == NULL)	head[val] = new;
	else{
		temp = head[val];
		while(1){
			/* find the end of the linked list */
			if(temp->next == NULL) break;
			temp = temp->next;
		}
		temp->next = new;
	}
}

/*-------------------------------------------------*/
/*함수 : opcodelist*/
/*목적 : hash table로 만든 opcode table을 출력한다.*/
/*리턴값 : 없음.*/
/*-------------------------------------------------*/
void opcodelist(){
	int i;
	Table* temp;

	/* just print the hash table to show the opcode list */
	for(i = 0; i < 20; i++){
		printf("%3d: ", i);
		/* if there is no bucket */
		if(head[i] == NULL){
			printf("\n");
			continue;
		}
		else{
			temp = head[i];
			while(1){
				printf("[%s, %.2X]", temp->mnemo, temp->opcode);
				if(temp->next == NULL)	break;
				temp = temp->next;
				printf(" -> ");
			}
		}
		printf("\n");
	}
}

/*----------------------------------*/
/*함수 : findOpcode*/
/*목적 : 입력받은 mnemonic을 찾는다.*/
/*리턴값 : opcode를 찾으면 0, 없으면 1을 반환한다.*/
/*----------------------------------*/
int findOpcode(char* op, int key){
	Table* temp;
	
	/* if the head of the linked list is NULL*/
	if(head[key] == NULL){
		return 1;
	}
	else{
		temp = head[key];
		while(1){
			/*  print the opcode if find the exact mnemonic */
			if(strcmp(temp->mnemo, op) == 0){
				return temp->opcode;
			}
			/* if there is no same mnemonic*/
			if(temp->next == NULL){
				return 1;
			}
			temp = temp->next;
		}
	}
	
}

/*-------------------------------------------*/
/*함수 : makeHistory*/
/*목적 : linked list로 history 목록을 만든다.*/
/*리턴값 : 없음.*/
/*-------------------------------------------*/
void makeHistory(char input[]){
	History* new = (History*)malloc(sizeof(History));
	History* temp;

	/* save the new instruction to the new node */
	strcpy(new->inst, input);
	new->link = NULL;

	/* if the head is NULL */
	if(his_head == NULL)	his_head = new;
	else{
		temp = his_head;
		while(1){
			/* find the end of the linked list*/
			if(temp->link == NULL)	break;
			temp = temp->link;
		}
		temp->link = new;
	}
}

/*-------------------------------*/
/*함수 : printHistory*/
/*목적 : history 목록을 출력한다.*/
/*리턴값 : 없음.*/
/*-------------------------------*/
void printHistory(){
	History* temp;
	int i = 1;
	
	temp = his_head;
	while(1){
		printf("%-7d %s\n", i, temp->inst);
		if(temp->link == NULL) break;
		i++; temp = temp->link;
	}	
}

/*---------------------------------------*/
/*함수 : freeHistory*/
/*목적 : history를 만들기 위해 동적할당한 
 	노드들을 해제한다.*/
/*리턴값 : 없음.*/
/*---------------------------------------*/
void freeHistory(){
	History* temp;

	/*if there is no history list*/
	if(his_head == NULL) return;
	while(1){
		temp = his_head;
		his_head = his_head->link;
		/* if you free all the nodes */
		if(his_head == NULL)	break;
		free(temp);
	}
}

/*-----------------------------------*/
/*함수 : freeHash*/
/*목적 : hsh table을 만들기 위해 
  	동적할당한 노드들을 해제한다.*/
/*리턴값 : 없음.*/
/*-----------------------------------*/
void freeHash(){
	Table* temp;
	int i = 0;

	for(i = 0; i < 20; i++){
		/* if the head is NULL */
		if(head[i] == NULL)	continue;
		while(1){
			temp = head[i];
			head[i] = head[i]->next;
			/* if you free all the nodes*/
			if(head[i] == NULL) break;
			free(temp);
		}
	}
}


/*함수 : type*/
/*목적 : 입력받은 파일의 내용을 출력해준다.*/
/*리턴값 : 제대로 출력하면 0, 문제가 있으면 1 */
int type(char* file){
	FILE* fp = fopen(file, "r");
	char out[256] = {0 ,};
	DIR *dr = opendir(".");	
	struct stat sb;

	if(fp == NULL){
		printf("Input file error!\n");
		return 1;
	}
	
	/*check if input is directory*/
	stat(file, &sb);
	if(S_ISDIR(sb.st_mode)){
		printf("This is a directory!\n");
		return 1;
	}
	while(1){
		if(fgets(out, 256, fp) == NULL) break;
		printf("%s", out);
	}
	fclose(fp); closedir(dr);
	return 0;
}

/*함수 : pass1*/
/*목적 : 입력받은 파일을 읽고 symbol table과 inmmediate 파일을 만든다*/
/*리턴값 : 없음. */
void pass1(char* input){
	FILE* fp1 = fopen(input, "r");
	FILE* fp2 = fopen("temp.txt", "w");
	char out[100] = {0,}, copy[100] = {0,}, temp[20] = {0,};
	char *tok1, *tok2, *tok3;
	int faddr = 0, laddr, i, key = 0, eflag = 0;
	static int sflag = 0;	
	/* error checking */
	if(fp1 == NULL || fp2 == NULL){
		printf("File open error!\n");
		assembleFlag = 1;
		return;
	}

	while(1){
		/* END가 없어도 멈출 수 있게 break함 */
		if(fgets(out, 100, fp1) == NULL) break;
		strcpy(copy, out);

		/* line with no symbol */
		if(out[0] == ' '){
			tok1 = strtok(out, " ");
				
			if(strcmp(tok1, "END") == 0){
				eflag = 1;	
				break;
			}	
			
			if(tok1[0] == '+'){
				fprintf(fp2, "%.4X\t%s", laddr, copy);	
				laddr += 4;
			}
			else {
				for(i = 0; i < strlen(tok1); i++){
					if(tok1[i] == '\n') tok1[i] = '\0';
					key += tok1[i];	
				}
				/* checking format*/
				if(strcmp(tok1, "BASE") == 0)	fprintf(fp2, "\t%s", copy);
				else fprintf(fp2, "%.4X\t%s", laddr, copy);
				
				laddr += retFormat(tok1, key % 20);
			}	
		}	
		
		/* comment line */
		else if(out[0] == '.'){
			fprintf(fp2, "%s", copy);
			memset(out, '\0', 100); memset(copy,'\0', 100);
			continue;
		}

		/* line with symbol */
		else{ 	
			tok1 = strtok(out, " ");
			strcpy(temp, tok1);
			tok1 = strtok(NULL, " ");
			/* temp : sumbol, tok1 : opcode */
	
			if(strcmp(tok1, "START") == 0){
				tok1 = strtok(NULL, " ");
				if(tok1 == NULL) faddr = 0;
				faddr = strtol(tok1, &tok2, 16);
				laddr = faddr;
				sflag++;
			}

			fprintf(fp2, "%.4X\t%s", laddr, copy);

			/*make symbol table*/
			hashSymbol(temp, laddr);

			if(tok1[0] == '+'){
				laddr += 4;
			}
			else if(strcmp(tok1, "BYTE") == 0){
				tok2 = strtok(NULL, " ");
				if(tok2[0] == 'C'){
					if(strlen(tok2) > 30){
						assembleFlag = 1;
						printf("Too long Charcter for BYTE.\n");
						return;
					}
					laddr += strlen(tok2) - 4;
				}
				else if(tok2[0] == 'X'){
					if(strlen(tok2) > 60){
						assembleFlag = 1;
						printf("Too long Hexadecimal for BYTE.\n");
						return;
					}
					laddr += (strlen(tok2) - 4) / 2 + (strlen(tok2) - 4) % 2;
				}
			}
			else if(strcmp(tok1, "RESB") == 0){
				tok2 = strtok(NULL, " ");
				laddr += strtol(tok2, &tok3, 10);
			}
			else if(strcmp(tok1, "RESW") == 0){
				tok2 = strtok(NULL, " ");
				laddr += 3 * strtol(tok2, &tok3, 10);
			}
			else{
				for(i = 0; i < strlen(tok1); i++){
					if(tok1[i] == '\n')	tok1[i] = '\0';
					key += tok1[i];
				}
				
				/* checking format*/
				laddr += retFormat(tok1, key % 20);
			}
		}
		memset(out, 0, 100); memset(copy, 0, 100); memset(temp, 0, 20);
		tok1 = NULL; tok2 = NULL; key = 0;
	}
	/* checking START */
	if(sflag == 0 || eflag == 0){
		printf("There is no START or END.\n");
		assembleFlag = 1;
		return;
	}
	if(sflag  > 1){
		printf("There is more than one START.\n");
		assembleFlag = 1;
		return;
	}
	Length = laddr - faddr;
	fprintf(fp2, "\t%s", copy);
	fclose(fp1); fclose(fp2);
}


/*함수 : hashSymbol*/
/*목적 : pass1에서 넘어온 symbol을 가지고 hash table을 만들고 중복되면 
 	assembleFlag를 set하고 에러문구 출력과 종료한다. */
/*리턴값 : 없음 */
void hashSymbol(char* sym, int address){
	Symbol* temp, *prev;
	Symbol* new = (Symbol*)malloc(sizeof(Symbol));
	
	/*new node*/
	strcpy(new->symbol, sym);
	new->addr = address;
	new->link = NULL;
	
	/*make linking with easch other*/
	if(sym_head[sym[0] - 'A'] == NULL)	sym_head[sym[0] - 'A'] = new;
	else{
		temp = sym_head[sym[0] - 'A']; prev = temp;

		if(strcmp(sym, temp->symbol) > 0){
			sym_head[sym[0] - 'A'] = new;
			new->link = temp;
			return;
		}
		else if(strcmp(sym, temp->symbol) == 0){
			printf("'%s' this symbol is already in the hash table.\n", sym);
			assembleFlag = 1;
			return;
		}
		else {
			while(temp->link != NULL){
				temp = temp->link;
				if(strcmp(sym, temp->symbol) > 0){
					new->link = temp;
					prev->link = new;
					return;
				}
				else if(strcmp(sym, temp->symbol) == 0){
					printf("'%s' this symbol is already in the hash table.\n", sym);
					assembleFlag = 1;
					return;
				}
				else prev = temp;
			} 
			temp->link = new;
			return;
		}
	}
}


/*함수 : printSymbol */
/*목적 : 입력으로 symbol이 들어왔을때 symbol table을 출력한다. */
/*리턴값 : 없음 */
void printSymbol(){
	int i;
	Symbol* temp;

	for(i = 25; i >= 0; i--){
		if(sym_head[i] == NULL)	continue;
		else{
			temp = sym_head[i];
			while(1){
				printf("\t%s\t%.4X\n", temp->symbol, temp->addr);
				if(temp->link == NULL)	break;
				temp = temp->link;
			}
		}
	}
}


/*함수 : retFormat */
/*목적 : opcode table에 저장한 opcode의 format을 찾아서 반환한다.*/
/*리턴값 : opcode의 format을 반환한다. */
int retFormat(char* op, int key){
	Table* temp;
	char* error;
	int format;

	/* if the head of the linked list is NULL*/
	if(head[key] == NULL){
		return 0;
	}
	else{
		temp = head[key];
		while(1){
			/*  print the opcode if find the exact mnemonic */
			if(strcmp(temp->mnemo, op) == 0){
				format = strtol(temp->format, &error, 10);
				return format;
			}
			/* if there is no same mnemonic*/
			if(temp->next == NULL){
				return 0;
			}
			temp = temp->next;
		}
	}
}

/*함수 : findSymbol */
/*목적 : symbol table에서 해당 symbol이 있는지 확인한다. */
/*리턴값 : 있으면 0 없으면 1을 반환*/
int findSymbol(char* input){
	Symbol* temp;

	temp = sym_head[input[0] - 'A'];

	if(temp == NULL)	return 1;
	else{
		while(1){
			if(strcmp(input, temp->symbol) == 0)	return 0;
			if(temp->link == NULL) return 1;
			temp = temp->link;
		}
	}
}

/*함수 : findSymAddr */
/*목적 : symbol table에 있는 symbol의 주소를 찾고 반환한다. */
/*리턴값 : 입력받은 symbol의 주소 */
int findSymAddr(char* input){
	Symbol* temp;

	temp = sym_head[input[0] - 'A'];
	
	if(temp == NULL)	return -1;
	else {
		while(1){
			if(strcmp(input, temp->symbol) == 0)	return temp->addr;
			if(temp->link == NULL) return -1;
			temp = temp->link;
		}
	}
}


/*함수 : pass2*/
/*목적 : pass1에서 만든 symbol테이블을 가지고 object code를 만들어
 	궁극적으로 .lst파일을 만들고 .obj 파일을 만들기 위한 임시파일을 생성한다.*/
/*리턴값 : 없음. */

void pass2(char* input){
	FILE* fp1 = fopen("temp.txt", "r");
	FILE *fp2, *fp4 = fopen("tempObject.txt", "w"), *fp5 = fopen("format4.txt","w");
	char line[256] = {0,}, copy[256] = {0,}, lst[50] = {0,}, object[50] = {0,};
	char *tok1 = strtok(input, "."), *tok2, *tok3, *tok4;
	int i, key = 0, reg1, reg2, base = 0, pc = 0, laddr = 0, xaddr = 0, taddr = 0, opcode = 0, lineNumber = 5;
	unsigned int  Ocode = 0;

	/*open list file*/
	strcpy(lst, tok1); strcat(lst, ".lst"); 
	fp2 = fopen(lst, "w"); 

	if(fp2 == NULL){
		printf("File input erorr!\n");
		assembleFlag = 1;
		return;
	}		
	while(1){
		fgets(line, 100, fp1);
		
		for(i = 0 ; i < strlen(line); i++){
			if(line[i] == '\t')	line[i] = ' ';
			else if(line[i] == '\n')	line[i] = '\0';
		}
		
		strcpy(copy, line);
		tok1 = strtok(line, " "); tok2 = strtok(NULL, " "); tok3 = strtok(NULL, " "); 
		
		if(strcmp(tok1, "END") == 0 ){
			for(i = 0; i < strlen(tok1); i++){
				if(tok1[i] == '\t')	tok1[i] = ' ';
			}
			fprintf(fp2, "%d\t    %s\n", lineNumber, copy);
			break;
		}
		else if(strcmp(tok1, "BASE") == 0){
			for(i = 0; i < strlen(tok1); i++){
				if(tok1[i] == '\t')	tok1[i] = ' ';
			}
			base = findSymAddr(tok2);
			fprintf(fp2, "%d\t    %s\n", lineNumber, copy);
			lineNumber += 5;
			continue;
		}

		if(copy[0] == '.'){
			fprintf(fp2, "%s\n", copy);
			memset(line, '\0', 256); memset(copy, '\0', 256);
			continue;
		}
	
		/* tok2 = symbol tok3 = opcode tok4 = operand */
		/* if tok2 is symbol */
		else if(findSymbol(tok2) == 0){
			tok4 = strtok(NULL, " ");
			
			if(strcmp(tok3, "START") == 0){
				/* list file*/
				fprintf(fp2, "%d\t%s\n", lineNumber, copy);
				
				/* object file */
				Ocode = strtol(tok1, &tok4, 16);	
				faddr = Ocode;
				fprintf(fp4, "H%-6s%.6X%.6X\n", tok2, Ocode, Length);
				lineNumber += 5;
				continue;
			}
			for(i = 0; i < strlen(tok3); i++)	key += tok3[i];

			opcode = findOpcode(tok3, key % 20);

			if(tok3[0] == '+'){
				/*format 4*/
				for(i = 0; i < strlen(tok3); i++)	tok3[i] = tok3[i + 1];
				for(i = 0, key = 0; i < strlen(tok3); i++)	key += tok3[i];

				opcode = findOpcode(tok3, key % 20);
				if(tok4[strlen(tok4) - 1] == ',') xaddr += 8;
				xaddr += 1;

				if(tok4[0] == '#' || tok4[0] == '@'){
					/* list file */
					if(tok4[0] == '#')	opcode += 1;
					else opcode += 2;
					
					for(i = 0; i < strlen(tok4); i++)	tok4[i] = tok4[i + 1];
					taddr = findSymAddr(tok4);
					if(taddr == -1)	taddr = strtol(tok4, &tok1, 10);

					fprintf(fp2, "%d\t%s   \t%.2X%X%.5X\n", lineNumber, copy, opcode, xaddr, taddr);
					
					/* object file */
					Ocode = strtol(tok1, &tok4, 16);
					if(lineLength == 0){
						fprintf(fp4, "T%.6X ", Ocode);
					}
					if(lineLength + 4 <= 30){
						lineLength += 4;
						fprintf(fp4, "%.2X%X%.5X", opcode, xaddr, taddr);
					}
					else if(lineLength + 4 > 30){
						fprintf(fp4, "\nT%.6X %.2X%X%.5X", Ocode, opcode, xaddr, taddr);
						lineLength = 4;
					}
				}
				else{
					opcode += 3;
					taddr =	findSymAddr(tok4);	
					/* list file */
					fprintf(fp2, "%d\t%s   \t%.2X%X%.5X\n", lineNumber, copy,opcode, xaddr, taddr);

					/* object file */
					Ocode = strtol(tok1, &tok4, 16);
					fprintf(fp5, "%X\n", Ocode + 1);
					if(lineLength == 0){
						fprintf(fp4, "T%.6X ", Ocode);
					}
					if(lineLength + 4 <= 30){
						lineLength += 4;
						fprintf(fp4, "%.2X%X%.5X", opcode, xaddr, taddr);
					}
					else if(lineLength + 4 > 30){
						fprintf(fp4, "\nT%.6X %.2X%X%.5X", Ocode, opcode, xaddr, taddr);
						lineLength = 4;
					}
				}
			}
			else if(retFormat(tok3, key % 20) == 1){
				/*format 1*/
				fprintf(fp2, "%d\t%s   \t\t\t%.2X\n", lineNumber, copy, findOpcode(tok3, key % 20));
				
				/* object file */
				Ocode = strtol(tok1, &tok4, 16);
				if(lineLength == 0){
					fprintf(fp4, "T%.6X ", Ocode);
				}
				if(lineLength + 1 <= 30){
					lineLength += 1;
					fprintf(fp4, "%.2X", findOpcode(tok3, key % 20));
				}
				else if(lineLength + 1 > 30){
					fprintf(fp4, "\nT%.6X %.2X", Ocode, findOpcode(tok3, key % 20));
					lineLength = 1;
				}

			}
			else if(retFormat(tok3, key % 20) == 2){
				/*foramt 2*/
				/* check if there is any ',' */
				if(tok4[strlen(tok4) - 1] == ','){
					tok2 = strtok(NULL, " ");
					tok4[strlen(tok4) - 1] = '\0';
				}
				else tok2 = NULL;
				findRegValue(tok4, tok2, &reg1, &reg2);
				fprintf(fp2, "%d\t%s\t\t%.2X%X%X\n", lineNumber, copy, findOpcode(tok3, key % 20), reg1, reg2);
					
				/* object file */
				Ocode = strtol(tok1, &tok4, 16);
				if(lineLength == 0){
					fprintf(fp4, "T%.6X ", Ocode);
				}
				if(lineLength + 2 <= 30){
					lineLength += 2;
					fprintf(fp4, "%.2X%X%X", findOpcode(tok3, key % 20), reg1, reg2);
				}
				else if(lineLength + 2 > 30){
					fprintf(fp4, "\nT%.6X %.2X%X%X", Ocode, findOpcode(tok3, key % 20), reg1, reg2);
					lineLength = 2;
				}
			}
			else if(retFormat(tok3, key % 20) == 3){
				/*format 3*/

				if(tok4[0] == '#'){
					for(i = 0; i < strlen(tok4); i++)	tok4[i] = tok4[i + 1];
					taddr = findSymAddr(tok4);
					if(opcode % 2 == 0)	opcode++;
					/*not symbol*/
					if(taddr == -1){
						taddr = strtol(tok4, &tok1, 10);
						fprintf(fp2, "%d\t%s   \t%.2X0%.3X\n", lineNumber, copy, opcode, taddr);
					
						/* object file */
						Ocode = strtol(tok1, &tok4, 16);
						if(lineLength == 0){
							fprintf(fp4, "T%.6X ", Ocode);
						}
						if(lineLength + 3 <= 30){
							lineLength += 3;
							fprintf(fp4, "%.2X0%.3X", opcode, taddr);
						}
						else if(lineLength + 3 > 30){
							fprintf(fp4, "\nT%.6X %.2X0%.3X", Ocode, opcode, taddr);
							lineLength = 3;
						}
					}
					/*symbol*/
					else {
						laddr = strtol(tok1, &tok2, 16);
						pc = laddr + 3; 
						if(tok4[strlen(tok4) - 1] == ',')	xaddr += 8;
						
						if(-2048 <= taddr - pc && taddr - pc < 2048){
							xaddr += 2;
							if(taddr - pc >= 0){
								fprintf(fp2, "%d\t%s   \t%.2X%X%.3X\n", lineNumber, copy, opcode, xaddr, taddr - pc);
						
								/* object file */
								Ocode = strtol(tok1, &tok4, 16);
								if(lineLength == 0){
									fprintf(fp4, "T%.6X ", Ocode);
								}
								if(lineLength + 3 <= 30){
									lineLength += 3;
									fprintf(fp4, "%.2X%X%.3X", opcode, xaddr, taddr - pc);
								}
								else if(lineLength + 3 > 30){
									fprintf(fp4, "\nT%.6X %.2X%X%.3X", Ocode, opcode, xaddr, taddr - pc);
									lineLength = 3;
								}
							}
							else{
								fprintf(fp2, "%d\t%s   \t%.2X%X", lineNumber, copy, opcode, xaddr);
								sprintf(object, "%.3X", taddr - pc);
								for(i = strlen(object) - 3; i < strlen(object); i++)	fprintf(fp2, "%c", object[i]);
								fprintf(fp2, "\n");

								/* objec file */
								Ocode = strtol(tok1, &tok4, 16);
								if(lineLength == 0){
									fprintf(fp4, "T%.6X ", Ocode);
								}
								if(lineLength + 3 <= 30){
									lineLength += 3;
									fprintf(fp4, "%.2X%X", opcode, xaddr);
									for(i = strlen(object) - 3; i < strlen(object); i++)	fprintf(fp4, "%c", object[i]);
								}
								else if(lineLength + 3 > 30){
									fprintf(fp4, "\nT%.6X %.2X%X", Ocode, opcode, xaddr);
									for(i = strlen(object) - 3; i < strlen(object); i++)	fprintf(fp4, "%c", object[i]);
									lineLength = 3;
								}
							}
						}
						else if(0 <= taddr - base && taddr - base < 4096){
							xaddr += 4;
							fprintf(fp2, "%d\t%s    \t%X%X%.3X\n", lineNumber, copy, opcode, xaddr, taddr - base);

							/* object file */
							Ocode = strtol(tok1, &tok4, 16);
							if(lineLength == 0){
								fprintf(fp4, "T%.6X ", Ocode);
							}
							if(lineLength + 3 <= 30){
								lineLength += 3;
								fprintf(fp4, "%.2X%X%.3X", opcode, xaddr, taddr - base);
							}
							else if( lineLength + 3 > 30){
								fprintf(fp4, "\nT%.6X %.2X%X%.3X", Ocode, opcode, xaddr, taddr - base);
								lineLength = 3;
							}
						}
						else {
							printf("%s\n This line is out of addressing range.\n", copy);
							assembleFlag = 1;
						}
					}
	
				}
				else if(tok4[0] == '@'){
					for(i = 0; i < strlen(tok4); i++)	tok4[i] = tok4[i + 1];

					laddr = strtol(tok1, &tok3, 16);
					pc = laddr + 3;

					taddr = findSymAddr(tok4);
					if(opcode % 4 == 1 || opcode % 4 == 0) opcode += 2;
					if(tok3[strlen(tok3) - 1] == ',')	xaddr += 8;

					if(-2048 <= taddr - pc && taddr - pc < 2048){
						xaddr += 2;
						if(taddr - pc >= 0){
							fprintf(fp2, "%d\t%s   \t%.2X%X%.3X\n", lineNumber, copy, opcode, xaddr, taddr - pc);

							/* object file */
							Ocode = strtol(tok1, &tok4, 16);
							if(lineLength == 0){
								fprintf(fp4, "T%.6X ", Ocode);
							}
							if(lineLength + 3 <= 30){
								lineLength += 3;
								fprintf(fp4, "%.2X%X%.3X", opcode, xaddr, taddr - pc);
							}
							else if(lineLength + 3 > 30){
								fprintf(fp4, "\nT%.6X %.2X%X%.3X", Ocode, opcode, xaddr, taddr - pc);
								lineLength = 3;
							}
						}
						else{
							/* list file */
							fprintf(fp2, "%d\t%s   \t%.2X%X", lineNumber, copy, opcode, xaddr);
							sprintf(object, "%.3X", taddr - pc);
							for(i = strlen(object) - 3; i < strlen(object); i++)	fprintf(fp2, "%c", object[i]);
							fprintf(fp2, "\n");

							/* object file */
							Ocode = strtol(tok1, &tok4, 16);
							if(lineLength == 0){
								fprintf(fp4, "T%.6X ", Ocode);
							}
							if(lineLength + 3 <= 30){
								lineLength += 3;
								fprintf(fp4, "%.2X%X", opcode, xaddr);
								for(i = strlen(object) - 3; i < strlen(object); i++)	fprintf(fp4, "%c", object[i]);
							}
							else if(lineLength + 3 > 30){
								fprintf(fp4, "\nT%.6X %.2X%X", Ocode, opcode, xaddr);
								for(i = strlen(object) - 3; i < strlen(object); i++)	fprintf(fp4, "%c", object[i]);
								lineLength = 3;
							}
						}
					}
					else if(0 <= taddr - base && taddr - base < 4096){
						xaddr += 4;
						fprintf(fp2, "%d\t%s   \t%.2X%X%.3X\n", lineNumber, copy, opcode, xaddr, taddr - base);

						/* object file */
						Ocode = strtol(tok1, &tok4, 16);
						if(lineLength == 0){
							fprintf(fp4, "T%.6X ", Ocode);
						}
						if(lineLength + 3 <= 30){
							lineLength += 3;
							fprintf(fp4, "%.2X%X%.3X", opcode, xaddr, taddr - base);
						}
						else if(lineLength + 3 > 30){
							fprintf(fp4, "\nT%.6X %.2X%X%.3X", Ocode, opcode, xaddr, taddr - base);
							lineLength = 3;
						}
					}
					else {
						printf("%s\n This line is out of addressing range.\n", copy);
						assembleFlag = 1;
					}
				}
				else{
					if(opcode % 2 == 0)	opcode++;
					if(opcode % 4 == 1 || opcode % 4 == 0)	opcode += 2;

					laddr = strtol(tok1, &tok2, 16);
					pc = laddr + 3;

					taddr = findSymAddr(tok4);

					if(tok4[strlen(tok4) - 1] == ',')	xaddr += 8;
				
					if(-2048 <= taddr - pc && taddr - pc < 2048){
						xaddr += 2;
						if(taddr - pc >= 0){
							fprintf(fp2, "%d\t%s   \t%.2X%X%.3X\n", lineNumber, copy, opcode, xaddr, taddr - pc);

							/* object file */
							Ocode = strtol(tok1, &tok4, 16);
							if(lineLength == 0){
								fprintf(fp4, "T%.6X ", Ocode);
							}
							if(lineLength + 3 <= 30){
								lineLength += 3;
								fprintf(fp4, "%.2X%X%.3X", opcode, xaddr, taddr - pc);
							}
							else if(lineLength + 3 > 30){
								fprintf(fp4, "\nT%.6X %.2X%X%.3X", Ocode, opcode, xaddr, taddr - pc);
								lineLength = 3;
							}
						}
						else{
							fprintf(fp2, "%d\t%s   \t%.2X%X", lineNumber, copy, opcode, xaddr);
							sprintf(object, "%.3X", taddr - pc);
							for(i = strlen(object) - 3; i < strlen(object); i++)	fprintf(fp2, "%c", object[i]);
							fprintf(fp2, "\n");

							/* object file */
							Ocode = strtol(tok1, &tok4, 16);
							if(lineLength == 0){
								fprintf(fp4, "T%.6X ", Ocode);
							}
							if(lineLength + 3 <= 30){
								lineLength += 3;
								fprintf(fp4, "%.2X%X", opcode, xaddr);
								for(i = strlen(object) - 3; i < strlen(object); i++)	fprintf(fp4, "%c", object[i]);
							}
							else if(lineLength + 3 > 30){
								fprintf(fp4, "\nT%.6X %.2X%X", Ocode, opcode, xaddr);
								for(i = strlen(object) - 3; i < strlen(object); i++)	fprintf(fp4, "%c", object[i]);
								lineLength = 3;
							}
						}
					}
					else if(0 <= taddr - base && taddr - base < 4096){
						xaddr += 4;
						fprintf(fp2, "%d\t%s   \t%.2X%X%.3X\n", lineNumber, copy, opcode, xaddr, taddr - base);

						/* object file */
						Ocode = strtol(tok1, &tok4, 16);
						if(lineLength == 0){
							fprintf(fp4, "T%.6X ", Ocode);
						}
						if(lineLength + 3 <= 30){
							lineLength += 3;
							fprintf(fp4, "%.2X%X%.3X", opcode, xaddr, taddr - base);
						}
						else if(lineLength + 3 > 30){
							fprintf(fp4, "\nT%.6X %.2X%X%.3X", Ocode, opcode, xaddr, taddr - base);
							lineLength = 3;
						}
					}
					else{
						printf("%s\n This line is out of addressing range.\n", copy);
						assembleFlag = 1;
					}
				}
			}
			else if(strcmp(tok3, "BYTE") == 0){
				if(tok4[0] == 'C'){
					for(i = 0; i < strlen(tok4) - 3; i++)	object[i] = tok4[i + 2];
					fprintf(fp2, "%d\t%s     \t", lineNumber, copy);
					for(i = 0; i < strlen(object); i++)	fprintf(fp2, "%X", object[i]);
					fprintf(fp2, "\n");

					/* object file */
					Ocode = strtol(tok1, &tok3, 16);
					if(lineLength == 0){
						fprintf(fp4, "T%.6X ", Ocode);
					}
					if(lineLength + (strlen(tok4) - 3) <= 30){
						lineLength += (strlen(tok4) - 3);
						for(i = 0; i < strlen(object); i++)	fprintf(fp4, "%X", object[i]);
					}
					else if(lineLength + (strlen(tok4) - 3) > 30){
						fprintf(fp4, "\nT%.6X ", Ocode);
						for(i = 0; i < strlen(object); i++)	fprintf(fp4, "%X", object[i]);
						lineLength = (strlen(tok4) - 3);
					}
				}
				else if(tok4[0] == 'X'){
					for(i = 0; i < strlen(tok4) - 3; i++)	object[i] = tok4[i + 2];
					fprintf(fp2, "%d\t%s     \t", lineNumber, copy);
					for(i = 0; i < strlen(object); i++)	fprintf(fp2, "%c", object[i]);
					fprintf(fp2, "\n");
	
					/* object file */
					Ocode = strtol(tok1, &tok3, 16);
					if(lineLength == 0){
						fprintf(fp4, "T%.6X ", Ocode);
					}
					if(lineLength + (strlen(tok4) - 3) <= 30){
						lineLength += (strlen(tok4) - 3);
						for(i = 0; i < strlen(object); i++)	fprintf(fp4, "%c", object[i]);
					}
					else if(lineLength + (strlen(tok4) - 3) > 30){
						fprintf(fp4, "\nT%.6X ", Ocode);
						for(i = 0; i < strlen(object); i++)	fprintf(fp4, "%c", object[i]);
						lineLength = (strlen(tok4) - 3);
					}
				}
			}

			else if(strcmp(tok3, "RESW") == 0 || strcmp(tok3, "RESB") == 0){
				fprintf(fp2, "%d\t%s\n", lineNumber, copy);
				if(lineLength != 0){
					fprintf(fp4, "\n");
					lineLength = 0;
				}
			}
		}
		/* tok2 = opcode tok3 = operand*/
		/* if tok2 is not a symbol */
		else {
			for(i = 0; i < strlen(tok2); i++)	key += tok2[i];

			if(strcmp(tok2, "RSUB") == 0){
				fprintf(fp2, "%d\t%s    \t\t%X\n", lineNumber, copy, 0x4F0000);	
				
				/* object file */
				Ocode = strtol(tok1, &tok4, 16);
				if(lineLength == 0){
					fprintf(fp4, "T%.6X ", Ocode);
				}
				if(lineLength + 3 <= 30){
					lineLength += 3;
					fprintf(fp4, "%X", 0x4F0000);
				}
				else if(lineLength + 3 > 30){
					fprintf(fp4, "\nT%.6X %X", Ocode, 0x4F0000);
					lineLength = 3;
				}
				lineNumber += 5;
				continue;
			}

			opcode = findOpcode(tok2, key % 20);

			if(tok2[0] == '+'){
				/*format 4*/
				for(i = 0; i < strlen(tok2); i++)	tok2[i] = tok2[i + 1];
				for(i = 0, key = 0; i < strlen(tok2); i++)	key += tok2[i];	
				
				opcode = findOpcode(tok2, key % 20);
				if(tok3[strlen(tok3) - 1] == ',')	xaddr += 8;
				xaddr += 1;

				if(tok3[0] == '#' || tok3[0] == '@'){
					if(tok3[0] == '#')	opcode += 1;
					else opcode += 2;
					for(i = 0; i < strlen(tok3); i++)	tok3[i] = tok3[i + 1];


					taddr = findSymAddr(tok3);
					if(taddr == -1)	taddr = strtol(tok3, &tok4, 10);

					fprintf(fp2, "%d\t%s   \t%.2X%X%.5X\n", lineNumber, copy, opcode, xaddr, taddr);

					/* object file */
					Ocode = strtol(tok1, &tok4, 16);
					if(lineLength == 0){
						fprintf(fp4, "T%.6X ", Ocode);
					}
					if(lineLength + 4 <= 30){
						lineLength += 4;
						fprintf(fp4, "%.2X%X%.5X", opcode, xaddr, taddr);
					}
					else if(lineLength + 4 > 30){
						fprintf(fp4, "\nT%.6X %.2X%X%.5X", Ocode, opcode, xaddr, taddr);
						lineLength = 4;
					}
				}
				else{
					opcode += 3;
					taddr =	findSymAddr(tok3);	
					fprintf(fp2, "%d\t%s   \t%.2X%X%.5X\n", lineNumber, copy,opcode, xaddr, taddr);
					
					/* object file */
					Ocode = strtol(tok1, &tok4, 16);
					fprintf(fp5, "%X\n", Ocode + 1);
					if(lineLength == 0){
						fprintf(fp4, "T%.6X ", Ocode);
					}
					if(lineLength + 4 <= 30){
						lineLength += 4;
						fprintf(fp4, "%.2X%X%.5X", opcode, xaddr, taddr);
					}
					else if(lineLength + 4 > 30){
						fprintf(fp4, "\nT%.6X %.2X%X%.5X", Ocode, opcode, xaddr, taddr);
						lineLength = 4;
					}
				}
			}
			else if(retFormat(tok2, key % 20) == 1){
				/*format 1*/
				fprintf(fp2, "%d\t%s  \t\t\t%.2X\n", lineNumber, copy, findOpcode(tok2, key % 20));
			
				/* object file */
				Ocode = strtol(tok1, &tok4, 16);
				if(lineLength == 0){
					fprintf(fp4, "T%.6X ", Ocode);
				}
				if(lineLength + 1 <= 30){
					lineLength += 1;
					fprintf(fp4, "%.2X", findOpcode(tok2, key % 20));
				}
				else if(lineLength + 1 > 30){
					fprintf(fp4, "\nT%.6X %.2X", Ocode, findOpcode(tok2, key % 20));
					lineLength = 1;
				}	
			}
			else if(retFormat(tok2, key % 20) == 2){
				/*format 2*/
				if(tok3[strlen(tok3) - 1] == ','){
					tok4 = strtok(NULL, " ");
					tok3[strlen(tok3) - 1] = '\0';
				}
				findRegValue(tok3, tok4, &reg1, &reg2);
				fprintf(fp2, "%d\t%s\t\t%.2X%X%X\n", lineNumber, copy, findOpcode(tok2, key % 20), reg1, reg2);
			
				/* object file*/
				Ocode = strtol(tok1, &tok4, 16);
				if(lineLength == 0){
					fprintf(fp4, "T%.6X ", Ocode);
				}
				if(lineLength + 2 <= 30){
					lineLength += 2;
					fprintf(fp4, "%.2X%X%X", findOpcode(tok2, key % 20), reg1, reg2);
				}
				else if(lineLength + 2 > 30){
					fprintf(fp4, "\nT%.6X %.2X%X%X", Ocode, findOpcode(tok2, key % 20), reg1, reg2);
					lineLength = 2;
				}
			}
			else if(retFormat(tok2, key % 20) == 3){
				/*format 3*/
				if(tok3[0] == '#'){
					/*eliminate the '#'*/
					for(i = 0; i < strlen(tok3); i++)	tok3[i] = tok3[i + 1];
					taddr = findSymAddr(tok3);
					if(opcode % 2 == 0)	opcode++;
					/*not symbol*/
					if(taddr == -1){
						taddr = strtol(tok3, &tok4, 10);
						fprintf(fp2, "%d\t%s   \t%.2X0%.3X\n", lineNumber, copy, opcode, taddr);

						/* object file */
						Ocode = strtol(tok1, &tok4, 16);
						if(lineLength == 0){
							fprintf(fp4, "T%.6X ", Ocode);
						}
						if(lineLength + 3 <= 30){
							lineLength += 3;
							fprintf(fp4, "%.2X0%.3X", opcode, taddr);
						}
						else if(lineLength + 3 > 30){
							fprintf(fp4, "\nT%.6X %.2X0%.3X", Ocode, opcode, taddr);
							lineLength = 3;
						}
					}
					/*symbol*/
					else {
						laddr = strtol(tok1, &tok4, 16);
						pc = laddr + 3; 
						if(tok3[strlen(tok3) - 1] == ',')	xaddr += 8;
						
						if(-2048 <= taddr - pc && taddr - pc < 2048){
							xaddr += 2;
							if(taddr - pc >= 0){
								fprintf(fp2, "%d\t%s   \t%X%X%.3X\n", lineNumber, copy, opcode, xaddr, taddr - pc);

								/* object file */
								Ocode = strtol(tok1, &tok4, 16);
								if(lineLength == 0){
									fprintf(fp4, "T%.6X ", Ocode);
								}
								if(lineLength + 3 <= 30){
									lineLength += 3;
									fprintf(fp4, "%.2X%X%.3X", opcode, xaddr, taddr - pc);
								}
								else if(lineLength + 3 > 30){
									fprintf(fp4, "\nT%.6X %.2X%X%.3X", Ocode, opcode, xaddr, taddr - pc);
									lineLength = 3;
								}
							}
							else{
								fprintf(fp2, "%d\t%s   \t%.2X%X", lineNumber, copy, opcode, xaddr);
								sprintf(object, "%.3X", taddr - pc);
								for(i = strlen(object) - 3; i < strlen(object); i++)	fprintf(fp2, "%c", object[i]);
								fprintf(fp2, "\n");

								/* object file */
								Ocode = strtol(tok1, &tok4, 16);
								if(lineLength == 0){
									fprintf(fp4, "T%.6X ", Ocode);
								}
								if(lineLength + 3 <= 30){
									lineLength += 3;
									fprintf(fp4, "%.2X%X", opcode, xaddr);
									for(i = (strlen(object) - 3); i < strlen(object); i++)	fprintf(fp4, "%c", object[i]);
								}
								else if(lineLength + 3 > 30){
									fprintf(fp4, "\nT%.6X %.2X%X", Ocode, opcode, xaddr);
									for(i = (strlen(object) - 3); i < strlen(object); i++)	fprintf(fp4, "%c", object[i]);
									lineLength = 3;
								}
							}
						}
						else if(0 <= taddr - base && taddr - base < 4096){
							xaddr += 4;
							fprintf(fp2, "%d\t%s   \t%X%X%.3X\n", lineNumber, copy, opcode, xaddr, taddr - base);
							
							/* object file */
							Ocode = strtol(tok1, &tok4, 16);
							if(lineLength == 0){
								fprintf(fp4, "T%.6X", Ocode);
							}
							if(lineLength + 3 <= 30){
								lineLength += 3;
								fprintf(fp4, "%.2X%X%.3X", opcode, xaddr, taddr - base);
							}
							else if(lineLength + 3 > 30){
								fprintf(fp4, "\nT%.6X %.2X%X%.3X", Ocode, opcode, xaddr, taddr - base);
								lineLength = 3;
							}
						}
						else{
							printf("%s\n This line is out of addressing range.\n", copy);
							assembleFlag = 1;
						}
					}
				}	
				else if(tok3[0] == '@'){
				//	printf("/*indirect*/ %s\n", tok2);
					for(i = 0; i < strlen(tok3); i++)	tok3[i] = tok3[i + 1];

					laddr = strtol(tok1, &tok4, 16);
					pc = laddr + 3;

					taddr = findSymAddr(tok3);
					
					if(opcode % 4 == 1 || opcode % 4 == 0) opcode += 2;
				
					if(tok3[strlen(tok3) - 1] == ',')	xaddr += 8;

					if(-2048 <= taddr - pc && taddr - pc < 2048){
						xaddr += 2;
						if(taddr - pc >= 0){
							fprintf(fp2, "%d\t%s   \t%.2X%X%.3X\n", lineNumber, copy, opcode, xaddr, taddr - pc);

							/* object file */
							Ocode = strtol(tok1, &tok4, 16);
							if(lineLength == 0){
								fprintf(fp4, "T%.6X", Ocode);
							}
							if(lineLength + 3 <= 30){
								lineLength += 3;
								fprintf(fp4, "%.2X%X%.3X", opcode, xaddr, taddr - pc);
							}
							else if(lineLength + 3 > 30){
								fprintf(fp4, "\nT%.6X %.2X%X%.3X", Ocode, opcode, xaddr, taddr - pc);
								lineLength = 3;
							}
						}
						else{
							fprintf(fp2, "%d\t%s   \t%.2X%X", lineNumber, copy, opcode, xaddr);
							sprintf(object, "%.3X", taddr - pc);
							for(i = strlen(object) - 3; i < strlen(object); i++)	fprintf(fp2, "%c", object[i]);
							fprintf(fp2, "\n");

							/* object file */
							Ocode = strtol(tok1, &tok4, 16);
							if(lineLength == 0){
								fprintf(fp4, "T%.6X ", Ocode);
							}
							if(lineLength + 3 <= 30){
								lineLength += 3;
								fprintf(fp4, "%.2X%X", opcode, xaddr);
								for(i = strlen(object); i < strlen(object); i++)	fprintf(fp4, "%c", object[i]);
							}
							else if(lineLength + 3 > 30){
								fprintf(fp4, "\nT%.6X %.2X%X", Ocode, opcode, xaddr);
								for(i = strlen(object); i < strlen(object); i++)	fprintf(fp4, "%c", object[i]);
								lineLength = 3;
							}
						}
					}
					else if(0 <= taddr - base && taddr - base < 4096){
						xaddr += 4;
						fprintf(fp2, "%d\t%s   \t%.2X%X%.3X\n", lineNumber, copy, opcode, xaddr, taddr - base);
						
						/* object file */
						Ocode = strtol(tok1, &tok4, 16);
						if(lineLength == 0){
							fprintf(fp4, "T%.6X ", Ocode);
						}
						if(lineLength + 3 <= 30){
							lineLength += 3;
							fprintf(fp4, "%.2X%X%.3X", opcode, xaddr, taddr - base);	
						}
						else if(lineLength + 3 > 30){
							fprintf(fp4, "\nT%.6X %.2X%X%.3X", Ocode, opcode, xaddr, taddr - base);
							lineLength = 3;
						}
					}
					else{
						printf("%s\n This line is out of addressing range.\n", copy);
						assembleFlag = 1;
					}
				}
				else{
					if(opcode % 2 == 0)	opcode++;
					if(opcode % 4 == 1 || opcode % 4 == 0)	opcode += 2;

					laddr = strtol(tok1, &tok4, 16);
					pc = laddr + 3;

					if(tok3[strlen(tok3) - 1] == ','){
						xaddr += 8;
						tok3[strlen(tok3) - 1] = '\0';
					}
					taddr = findSymAddr(tok3);
					
					if(-2048 <= taddr - pc && taddr - pc < 2048){
						xaddr += 2;
						if(taddr - pc >= 0){
							fprintf(fp2, "%d\t%s     \t%.2X%X%.3X\n", lineNumber, copy, opcode, xaddr, taddr - pc);

							/* object file */
							Ocode = strtol(tok1, &tok4, 16);
							if(lineLength == 0){
								fprintf(fp4, "T%.6X ", Ocode);
							}
							if(lineLength + 3 <= 30){
								lineLength += 3;
								fprintf(fp4, "%.2X%X%.3X", opcode, xaddr, taddr - pc);
							}
							else if(lineLength + 3 > 30){
								fprintf(fp4, "\nT%.6X %.2X%X%.3X", Ocode, opcode, xaddr, taddr - pc);
								lineLength = 3;
							}
						}	
						else{
							fprintf(fp2, "%d\t%s   \t%.2X%X", lineNumber, copy, opcode, xaddr);
							sprintf(object, "%.3X", taddr - pc);
							for(i = strlen(object) - 3; i < strlen(object); i++)	fprintf(fp2, "%c", object[i]);
							fprintf(fp2, "\n");

							/* object file */
							Ocode = strtol(tok1, &tok4, 16);
							if(lineLength == 0){
								fprintf(fp4, "T%.6X ", Ocode);
							}
							if(lineLength + 3 <= 30){
								lineLength += 3;
								fprintf(fp4, "%.2X%X", opcode, xaddr);
								for(i = strlen(object) - 3; i < strlen(object); i++)	fprintf(fp4, "%c", object[i]);
							}
							else if(lineLength + 3 > 30){
								fprintf(fp4, "\nT%.6X %.2X%X", Ocode, opcode, xaddr);
								for(i = strlen(object) - 3; i < strlen(object); i++)	fprintf(fp4, "%c", object[i]);
								lineLength = 3;
							}
						}
					}
					else if(0 <= taddr - base && taddr - base < 4096){
						xaddr += 4;
						fprintf(fp2, "%d\t%s   \t%.2X%X%.3X\n", lineNumber, copy, opcode, xaddr, taddr - base);

						/* object file */
						Ocode = strtol(tok1, &tok4, 16);
						if(lineLength == 0){
							fprintf(fp4, "T%.6X ", Ocode);
						}
						if(lineLength + 3 <= 30){
							lineLength += 3;	
							fprintf(fp4, "%.2X%X%.3X", opcode, xaddr, taddr - base);
						}
						else if(lineLength + 3 > 30){
							fprintf(fp4, "\nT%.6X %.2X%X%.3X", Ocode, opcode, xaddr, taddr - base);		
							lineLength = 3;	
						}
					}
					else{
						printf("%s\n This line is out of addressing range.\n", copy);
						assembleFlag = 1;
					}
				}
			}
		}
		memset(line, 0, 256); memset(copy, 0, 256); memset(object, 0, 50);
		tok1 = NULL; tok2 = NULL; tok3 = NULL; tok4 = NULL; key = 0; 
		taddr = 0; laddr = 0; xaddr = 0; Ocode = 0; opcode = 0; lineNumber += 5;
	}
	fprintf(fp4,"\n");
	fclose(fp1); fclose(fp2); fclose(fp4); fclose(fp5);
}


/*함수 : findRegValue*/
/*목적 : format2의 입력으로 들어온 레지스터의 값을 찾는다. */
/*리턴값 : 없음. */
void findRegValue(char* a, char* b, int* reg1, int* reg2){
	if(a != NULL){
		if(strcmp(a, "A") == 0)	*reg1 = 0;
		else if(strcmp(a, "X") == 0)	*reg1 = 1;
		else if(strcmp(a, "L") == 0)	*reg1 = 2;
		else if(strcmp(a, "PC") == 0) *reg1 = 8;
		else if(strcmp(a, "SW") == 0) *reg1 = 9;
		else if(strcmp(a, "B") == 0)	*reg1 = 3;
		else if(strcmp(a, "S") == 0)	*reg1 = 4;
		else if(strcmp(a, "T") == 0)	*reg1 = 5;
		else if(strcmp(a, "F") == 0)	*reg1 = 6;
		else{
			assembleFlag = 1;
			printf("%s is not supported register.\n", a);
		}
	}
	else *reg1 = 0;

	if(b != NULL){
		if(strcmp(b, "A") == 0)	*reg2 = 0;
		else if(strcmp(b, "X") == 0)	*reg2 = 1;
		else if(strcmp(b, "L") == 0)	*reg2 = 2;
		else if(strcmp(b, "PC") == 0) *reg2 = 8;
		else if(strcmp(b, "SW") == 0) *reg2 = 9;
		else if(strcmp(b, "B") == 0)	*reg2 = 3;
		else if(strcmp(b, "S") == 0)	*reg2 = 4;
		else if(strcmp(b, "T") == 0)	*reg2 = 5;
		else if(strcmp(b, "F") == 0)	*reg2 = 6;
		else{
			assembleFlag = 1;
			printf("%s is not supported register.\n", b);
		}
	}
	else *reg2 = 0;
}

/*함수 : ObjecFile*/
/*목적 : pass2()에서 만들어둔 파일들을 토대로 .obj파일을 만든다. */
/*리턴값 : 없음. */
void ObjectFile(char* input){
	FILE* fp1 = fopen("tempObject.txt", "r"), *fp2 = fopen("format4.txt", "r"), *fp3;
	char name[100] = {0,}, line[256] = {0,};
	char* temp;
	unsigned int addr;

	temp = strtok(input, "."); strcpy(name, temp);
	strcat(name, ".obj");
	fp3 = fopen(name, "w");

	while(1){
		if(fgets(line, 256, fp1) == NULL) break;

		if(line[0] == 'H'){
			fprintf(fp3, "%s", line);
		}
		else if(line[0] == 'T'){
			temp = strtok(line, " "); fprintf(fp3, "%s", temp); 
			temp = strtok(NULL, " "); 
			addr = strlen(temp); fprintf(fp3, "%.2X%s", addr / 2, temp);
		}
	}	
	memset(line, 0, 256); addr = 0;

	while(1){
		if(fgets(line, 256, fp2) == NULL) break;
		
		addr = strtol(line, &temp, 16);
		fprintf(fp3, "M%.6X05\n", addr);
	}	
	fprintf(fp3, "E%.6X\n", faddr);

	fclose(fp1); fclose(fp2); fclose(fp3);
}

/*함수 : freeSymTable */
/*목적 : symbol table의 노드들을 해제시킨다.. */
/*리턴값 : 없음.  */
void freeSymTable(){
	Symbol* temp;
	int i;

	for(i = 0; i < 26; i++){
		if(sym_head[i] == NULL)	continue;
		else{
			while(1){	
				temp = sym_head[i];
				sym_head[i] = sym_head[i]->link;
				if(sym_head[i] == NULL)	break;
				free(temp);
			}
		}
	}

}

/*함수 : fileDelete */
/*목적 : intermediate file을 지운다. */
/*리턴값 : 없음. */
void fileDelete(){
	remove("temp.txt");
	remove("tempObject.txt");
	remove("format4.txt");
}

void loader_pass1(char* input, int current){
	FILE* fp = fopen(input, "r");
	char line[100] = {'\0',};
	int cslth = 0, i, temp_addr = 0;
	char token[10] = {0,};

	memset(line, '\0', sizeof(line));
	if(fp == NULL){
		printf("Input file error!\n");
		return;
	}
	while(1){
		fgets(line, 100, fp);
		if(line[0] == 'H'){
			strncpy(token, line + 13, 6);
			sscanf(token, "%X", &cslth);
			strncpy(token, line + 1, 6);
			externSymTab(token, csaddr, cslth);	
		}
		else if(line[0] == 'D'){
			for(i = 0; i < strlen(line) - 12; i += 12){
				strncpy(token, line + 7 + i, 6);
				sscanf(token, "%X", &temp_addr);
				strncpy(token, line + 1 + i, 6);
				externSymTab(strtok(token, " "), csaddr + temp_addr, 0);
			}
		}
		else if(line[0] == 'E'){
			break;
		}
	}
	progaddr[current + 1] = progaddr[current] + cslth;
	total_cslth += cslth;
	fclose(fp);
}

int externSymTab(char* input, int csaddr, int cslth){
	int key = 0, i;
	LinkedList* new = (LinkedList*)malloc(sizeof(LinkedList));
	LinkedList* temp;

	if(input == NULL)	
		return 0;
	
	strcpy(new->name, input);
	new->addr = csaddr;
	new->length = cslth;
	new->next = NULL;

	/*for showing estab*/
	if(estabHead == NULL)
		estabHead = new;
	else{
		temp = estabHead;
		while(1){
			if(strcmp(temp->name, input) == 0)	continue;
			if(temp->next == NULL){
				temp->next = new;
				break;
			}
			else	temp = temp->next;
		}
	}
	
	/*key for hash table*/
	for(i = 0; i < strlen(input); i++){
		key += input[i];
	}
	key %= 20;
	
	/*hash table*/
	if(estab_head[key] == NULL)	
		estab_head[key] = new;
	else{
		temp = estab_head[key];
		while(1){
			if(strcmp(temp->name, input) == 0){
				return 1; //중복
			}
			if(temp->next == NULL){
				temp->next = new;
				break;
			}
			else temp = temp->next;
		}
	}
	return 0;
}
void freeLinked_estab(){
	LinkedList* temp;

	if(estabHead == NULL) return;
	else{
		while(1){
			if(estabHead->next != NULL){
				temp = estabHead;
				estabHead = estabHead->next;
				free(temp);
			}
			else{		
				temp = estabHead;
				free(temp);
				break;
			}	
		}
	}
}
void show_estab(){
	LinkedList* temp;
	
	temp = estabHead;
	printf("\ncontrol\tsymbol\taddress\t\tlength\n");
	printf("section\tname\n");
	printf("-----------------------------------------\n");
	while(1){
		if(temp == NULL) break;

		if(temp->length != 0){
			printf("%s\t\t%.4X\t\t%.4X\n", temp->name, temp->addr, temp->length);
		}
		else {
			printf("\t%s\t%.4X\t\n", temp->name, temp->addr);
		}
		temp = temp->next;
	}
	printf("-----------------------------------------\n");
	printf("\t\t%s\t%.4X\n", "total length", total_cslth);
}

int loader_pass2(char* filename){
	FILE* fp = fopen(filename, "r");
	int cslth = 0, i = 0, j = 0, index = 0, offset = 1, len = 0, temp_addr = 0, hex = 0, sum = 0x0, flag = 0, R_flag = 0, referNum = 0;
	int extern_sym_addr[15] = {0,};
	char line[100] = {0,}, token[10] = {0,}, idx[3] = {0,}, address[10] = {0,};
//	char no_referNum_extern[10][10] = {0,};
	LinkedList* node = NULL;

	if(fp == NULL)	return 1;

	for(i = 0; i < 15; i++)	extern_sym_addr[i] = -1;
	extern_sym_addr[1] = csaddr;

	while(fgets(line, sizeof(line), fp) != NULL){
		if(line[0] == 'H'){
			strncpy(token, line + 13, 6);
			sscanf(token, "%X", &cslth);
		}

		while(line[0] != 'E'){
			if(fgets(line, sizeof(line), fp) == NULL)
				break;
			if(line[0] == 'R'){ 
				R_flag = 1;
				len = strlen(line);
				offset = 1;

				for(i = 0; i < (len / 8); i++){
//				for(i = 0; ; i++){
					index = j = 0;
					memset(idx, '\0', 3);

					for(j = 0; j < 10; j++){
						token[j] = 0;
					}
					strncpy(token, line + offset, 8);
					strncpy(idx, token, 2);
					
					if(token[0] == '0') referNum = 1;

					if(referNum){
					//	if(i < (len / 8)) break;
						sscanf(idx, "%X", &index);
						node = find_externSym(strtok(token + 2, " \n"));
						if(node == NULL){
							printf("Undefined external symbol in %s\n", filename);
							flag = 1; loadFlag = 1;
							fclose(fp);
							return 1;
						}
						extern_sym_addr[index] = node->addr;
						offset += 8;
					}
					else{
					//	strcpy(no_referNum_extern[i], strtok(token, " \n"));	
					//	printf("%s\n", no_referNum_extern[i]);
					//	if(i < (len / 6)) break;
						memset(token, '\0', sizeof(token));
						strncpy(token, line + offset, 6);
						printf("%s\n", token);
						offset += 6;
						
					}
				}
			}
			else if(line[0] == 'T'){
				temp_addr = len = 0;
				offset = 9;

				strncpy(token, line + 1, 6);
				sscanf(token, "%X", &temp_addr);
				temp_addr += csaddr;

				memset(token, '\0', 10);
				strncpy(token, line + 7, 2);
				sscanf(token, "%X", &len);

				for(i = 0; i < len; i++){
					memo[temp_addr] = make_hex(line, offset);
					offset += 2;
					temp_addr++;
				}
			}
			else if(line[0] == 'M' && referNum){
				index = 0;
				memset(idx, '\0', 3);

				/*get external reference index*/
				strncpy(token, line + 10, 2);
				strncpy(idx, token, 2);
				sscanf(idx, "%X", &index);

				/*No R record == No external symbol in M record*/
				if(!R_flag){
					memset(address, '\0', 10);
					temp_addr = j = len = hex = 0;
					sum = 0x0;

					/*get length and address*/
					strncpy(address, line + 7, 2);
					sscanf(address, "%X", &len);
					strncpy(address, line + 1, 6);
					sscanf(address, "%X", &temp_addr);
					temp_addr += csaddr;

					/*length is odd*/
					if(len % 2 == 1){
						for(j = temp_addr + len / 2; j > temp_addr; j--){
							sum += memo[j] << hex;
							hex += 8;
						}	
						sum += (memo[temp_addr] & 0x0F) << hex;
					}
					/*length is even*/
					else{
						for(j = temp_addr + len / 2 - 1; j > temp_addr; j--){
							sum += memo[j] << hex;
							hex += 8;
						}	
						sum += (memo[temp_addr]) << hex;
					}

					sum += extern_sym_addr[1];	
					sum &= 0xFFFFFF;

					if(len % 2 == 1){
						for(j = temp_addr + len / 2; j > temp_addr; j--){
							hex = 0xFF;
							memo[j] = (sum&hex);
							sum >>= 8;
						}	
						hex = 0xF0;
						memo[temp_addr] &= hex;
						hex = 0xF;
						memo[temp_addr] |= (sum&hex) << 4;
						sum >>= 4;
					}
					else{
						for(j = temp_addr + len / 2 - 1; j > temp_addr; j--){
							hex = 0xFF;
							memo[j] = (sum&hex);
							sum >>= 8;
						}
						hex = 0xFF;
						memo[temp_addr] = sum&hex;
						sum >>= 4;
					}

				}
				/*if external symol exist*/
				else if(R_flag && extern_sym_addr[index] != -1){
					memset(address, '\0', 10);
					temp_addr = j = len = hex = 0;
					sum = 0x0;

					/*get length and address*/
					strncpy(address, line + 7, 2);
					sscanf(address, "%X", &len);
					strncpy(address, line + 1, 6);
					sscanf(address, "%X", &temp_addr);
					temp_addr += csaddr;

					/*length is odd*/
					if(len % 2 == 1){
						for(j = temp_addr + len / 2; j > temp_addr; j--){
							sum += memo[j] << hex;
							hex += 8;
						}	
						sum += (memo[temp_addr] & 0x0F) << hex;
					}
					/*length is even*/
					else{
						for(j = temp_addr + len / 2 - 1; j > temp_addr; j--){
							sum += memo[j] << hex;
							hex += 8;
						}	
						sum += (memo[temp_addr]) << hex;
					}

					if(line[9] == '+'){
						sum += extern_sym_addr[index];
					}
					else if(line[9] == '-'){
						sum -= extern_sym_addr[index];
					}
					sum &= 0xFFFFFF;

					if(len % 2 == 1){
						for(j = temp_addr + len / 2; j > temp_addr; j--){
							hex = 0xFF;
							memo[j] = (sum&hex);
							sum >>= 8;
						}	
						hex = 0xF0;
						memo[temp_addr] &= hex;
						hex = 0xF;
						memo[temp_addr] |= (sum&hex) << 4;
						sum >>= 4;
					}
					else{
						for(j = temp_addr + len / 2 - 1; j > temp_addr; j--){
							hex = 0xFF;
							memo[j] = (sum&hex);
							sum >>= 8;
						}
						hex = 0xFF;
						memo[temp_addr] = sum&hex;
						sum >>= 4;
					}
				}
				else{
					printf("Undefined external symbol in %s\n", filename);
					flag = 1; loadFlag = 1;
					fclose(fp);
					return 1;
				}
			}
			else if(line[0] == 'M' && !referNum){
				

			}
			if(flag){
				memset(memo, '\0', sizeof(memo));
				fclose(fp);
				break;
			}
		}
	//	if(line[0] == 'E'){
				
	//	}
	}

	fclose(fp);
	return 0;
}

LinkedList* find_externSym(char* input){
	LinkedList* temp;
	int key = 0, i;

	for(i = 0; i < strlen(input); i++) key += input[i];
	key %= 20;
	
	if(estab_head[key] == NULL){ 
		return NULL;
	}
	else{
		temp = estab_head[key];
		while(temp != NULL){
			if(strcmp(temp->name, input) == 0)
				return temp;
			temp = temp->next;
		}
	}
	return NULL;
}

char make_hex(char* input, int count){
	char c1[2] = {input[count]}, c2[2] = {input[count + 1]};
	int i1, i2;

	sscanf(c1, "%X", &i1);
	sscanf(c2, "%X", &i2);

	return (char)(i1 * 16 + i2);
}

int run(int* bp_flag){
	int opcode, ni, format, end_exec = progaddr[0] + temp_cslth;
	int reg1, reg2, extend, i, pc_flag = 0, ch_flag = 0, brk_point;
	unsigned int target, value = 0;
	static int cond, cond_flag = 0;

	//if first run
	if(!*bp_flag){
		regist[8] = progaddr[0];
		regist[2] = end_exec; 	
		*bp_flag = 1;
	}

	while(regist[8] < end_exec){
		ni = memo[regist[8]] % 4;
		opcode = memo[regist[8]] - ni;
		
		//format 2
		if(opcode == 0xA0 || opcode == 0xB4 || opcode == 0xB8){
			format = 2;
			reg1 = memo[regist[8] + 1] / 16;
			reg2 = memo[regist[8] + 1] % 16;

			if(reg1 < 0 || reg1 > 9 || reg1 == 7){
				printf("Error: Invalid operand - register not defined\n");
				return 0;
			}
		}

		// format 3/4
		else{
			extend = memo[regist[8] + 1] & 0x10;
			if(extend) format = 4;
			else format = 3;

			target = target_addr(format, regist[8]);
			if(ni == 1) value = target;
			else{
				//error handling with target address
				if(target < 0 || target > end_exec){
					printf("Error : Invalid target address\n");
					return 0;
				}
				for(i = 0; i < 3; i++){
					value += memo[target + i] * pow(16.0, 4.0 - 2 * i);
				}
				if(ni == 2) target = value;
			}
		}
		
		switch(opcode){
			//clear
			case 0xB4: regist[reg1] = 0; break;
			//compr
			case 0xA0: cond_flag = 1;
				   if(regist[reg1] > regist[reg2]) cond = 1;
				   else if(regist[reg1] == regist[reg2]) cond = 0;
				   else cond = -1; 
				   break;
			//TIXR
			case 0xB8: regist[1] = regist[1] + 1;
				   cond_flag = 1;
				   if(regist[1] > regist[reg1]) cond = 1;
				   else if(regist[1] == regist[reg1]) cond = 0;
				   else cond = -1;
				   break;
			//comp
			case 0x28: cond_flag = 1;
				   if(regist[0] > value) cond = 1;
				   else if(regist[0] == value) cond = 0;
				   else cond = -1;
				   break;
			//J
			case 0x3C: regist[8] = target;
				   pc_flag = 1;
				   break;
			//JEQ
			case 0x30: if(!cond_flag){
					printf("Error: No condition exists!\n");
					return 0;
				   }
				   if(!cond){
					regist[8] = target;
					pc_flag = 1;
				   }
				   break;
			//JLT
			case 0x38: if(!cond_flag){
					printf("Error: No condition exists!\n");
					return 0;
				   }
				   if(cond < 0){
					regist[8] = target;
					pc_flag = 1;
				   }
				   break;
			//JSUB
			case 0x48: regist[2] = regist[8] + format;
				   regist[8] = target;
				   pc_flag = 1;
				   break;
			//LDA
			case 0x00: regist[0] = value; break;
			//LDB
			case 0x68: regist[3] = value; break;
			//LDCH
			case 0x50: regist[0] = value / (int)pow(16.0, 4.0); break;
			//LDT
			case 0x74: regist[5] = value; break;
			//Rd
			case 0xD8: regist[0] = 0; break;
			//RSUB
			case 0x4C: regist[8] = regist[2];
				   pc_flag = 1;
				   break;
			//STA
			case 0x0C: store(target, regist[0]); break;
			//STCH
			case 0x54: store(target, regist[0] % 256); break;
			//STL
			case 0x14: store(target, regist[2]); break;
			//STX
			case 0x10: store(target, regist[1]); break;
			//TD
			case 0xE0: cond = -1; cond_flag = 1; break;
		}
		if(!pc_flag) regist[8] += format;
		pc_flag = 0;
		value = 0;

		if(search_bp(regist[8])){
			ch_flag = 1;
			brk_point = regist[8];
		}

		if(ch_flag) break;
	}

	// if breakpoint
	if(ch_flag){
		print_reg();
		printf("Stop at check point[%04X]\n\n", brk_point);
		ch_flag = 0;
	}

	//if the program ends
	else{
		print_reg();
		printf("End program\n\n");
		*bp_flag = 0;
	}
	
	return 1;
}

int target_addr(int format, int idx){
	unsigned int target = 0, xbpe, sign_flag = 0;

	xbpe = memo[idx + 1];
	if((xbpe % 16) & 0x08) sign_flag = 1;

	//modify the target address with bpe address
	if(xbpe & 0x80) target += regist[1];
	if(xbpe & 0x40) target += regist[3];
	if(xbpe & 0x20) target += (regist[8] + format);

	//calculate the target address
	if(format == 4)
		target += (memo[idx + 1] % 16) * 16 * 16 * 16* 16 + (memo[idx + 2] / 16) * 16 * 16 * 16;
	target += (memo[idx + format - 2] % 16) * 16 * 16 + memo[idx + format - 1];
	
	if(sign_flag){
		target += 0xF000;
		if(format == 3)
			target &= 0x0FFFF;
	}
	return target;
}

void store(unsigned int target, unsigned int value){
	int i;

	for(i = 0; i < 3; i++){
		memo[target + i] = (value % (int)pow(16.0, 6.0 -2*i)) / (int)pow(16.0, 4.0 - 2*i);	 
	}	
	return;
}

void print_reg(){
	printf("\nA : %.6X X : %.6X\nL : %.6X PC: %.6X\nB : %.6X S : %.6X\nT : %.6X\n", regist[0], regist[1], regist[2], regist[8], regist[3], regist[4], regist[5]);
	return;
}

int search_bp(int target){
	bp_list* temp;

	for(temp = bp_head; temp != NULL; temp = temp->next){
		if(temp->addr == target) return 1;
	}
	return 0;
}	

void bp(int hd_flag){
	bp_list* temp = bp_head, *next;

	if(!hd_flag){
		while(temp != NULL){
			next = temp->next;
			free(temp);
			temp = next;
		}
		bp_head = NULL;
		printf("\n[ok] clear all breakpoints\n\n");
	}
	else{
		if(bp_head){
			printf("\nbreakpoints\n-----------\n");
			for(temp = bp_head; temp != NULL; temp = temp->next){
				printf("%.4X\n", temp->addr);
			}
		}
		else printf("\nno breakpoints set.\n\n");
	}
	return;
}

void store_bp(int bpAddr){
	bp_list* temp, *node;

	/*inintialize node*/
	node = (bp_list*)calloc(1, sizeof(bp_list));
	node->addr = bpAddr;
	node->next = NULL;

	if(!bp_head){
		bp_head = node;
	}
	else{
		temp = bp_head;
		while(1){
			if(temp->next == NULL) break;
			temp = temp->next;
		}
		temp->next = node;
	}
	printf("\n[ok] create breakpoint %.4X\n\n", bpAddr);
	return;
}

void freeEstab(){
	LinkedList* temp = NULL;
	int i;
	
	
	for(i = 0; i < 20; i++){
		if(estab_head[i] == NULL) continue;
		for(temp = estab_head[i]; estab_head[i] != NULL; temp = estab_head[i]){
			estab_head[i] = estab_head[i]->next;
			free(temp);
		}
	}
}
