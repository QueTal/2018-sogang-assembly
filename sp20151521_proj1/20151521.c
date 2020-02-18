#include"20151521.h"

/*-----------------------------------*/
/*함수 : main*/
/*목적 : 사용자로부터 입력을 받고 명령에 
  	맞는 함수를 실행한다.*/
/*리턴값 : 제대로 종료될 시 0*/
/*-----------------------------------*/
int main(void){
	char ch[256] = {0,}, copy[256] = {0,};
	int i, j, flag = 0, key = 0;
	long long start = 0, end = 0, value = 0;
	char *tok, *real, *temp, *add;

	/* make hash table */
	makeHash();
	while (1) {
		printf ("sicsim> ");
		
		/* save the input */
		for (i = 0; i < 256; i++) {
			scanf ("%c", &ch[i]);
			/*count the number of ','*/
			if(ch[i] == ',')	flag++;
			//prevent segmentation fault
			if(ch[0] == '\n')	break;
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
					memset(memo, 0, 256); 
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
							finish = 159 + start;
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
						if(strcmp(temp, ",") != 0){
							/* if there is any other character that does not handle in hexadecimal */
							/* print the error message if the input is wrong */
							printf("Invalid input!\n");
							break;
						}
						end = strtol(tok, &temp, 16);
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
						if(strcmp(temp, "\0") == 0 && start >= 0 && end <= 0xFFFFF && start < end && 0 <= value && value <= 0xFF){
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
						findOpcode(tok, (int)(key % 20));
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
		flag = 0; key = 0;
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
	if(last % 16 != 0)	cnt++;
	if(end % 16 == 0) cnt++;

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
/*리턴값 : 없음.*/
/*----------------------------------*/
void findOpcode(char* op, int key){
	Table* temp;

	/* if the head of the linked list is NULL*/
	if(head[key] == NULL){
		printf("Invalid input!\n");
		return;
	}
	else{
		temp = head[key];
		while(1){
			/*  print the opcode if find the exact mnemonic */
			if(strcmp(temp->mnemo, op) == 0){
				printf("opcode is %-.2X.\n", temp->opcode);
				break;
			}
			/* if there is no same mnemonic*/
			if(temp->next == NULL){
				printf("Invalid input!\n");	
				break;
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
