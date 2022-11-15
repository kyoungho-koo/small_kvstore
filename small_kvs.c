#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "small_kvs.h"




static void printCMDline (char **cmd_argv, int *cmd_argc);


int main () {

	while(1) {
		char *cmd_argv[5];
		int cmd_argc = 0;
		printCMDline (cmd_argv, &cmd_argc);

		if (!strcmp (cmd_argv[0], "put") || !strcmp(cmd_argv[0], "p")) {
			put_kv(cmd_argv[1], cmd_argv[2]);
		} else if (!strcmp(cmd_argv[0], "get") || !strcmp(cmd_argv[0], "g")) {
			char value[VALUE_SIZE];
			get_kv(cmd_argv[1], value);

			if (value == NULL || !strcmp(value, DEL_STR)) {
				  printf("key: %s NOTFOUND\n", cmd_argv[1]);
			} else {
				  printf("key: %s value: %s\n", cmd_argv[1], value);
			}
		} else if (!strcmp(cmd_argv[0], "del") || !strcmp(cmd_argv[0], "d")) {
			char value[VALUE_SIZE];
			get_kv(cmd_argv[1], value);

			if (value != NULL) {
				put_kv(cmd_argv[1], DEL_STR);
			}
		} else if (!strcmp(cmd_argv[0], "all") || !strcmp(cmd_argv[0], "a")) {
			get_all ();
		} else if (!strcmp(cmd_argv[0], "help") || !strcmp(cmd_argv[0], "h")) {
			printf( "[command]	[argv1]		[argv2]\n"
					"put		key		value\n"
					"	- put key-value record\n"
					"\n"
					"get		key\n"
					"	- get value from key"
					"\n"
					"del    key\n"
					"all\n"
					"quit\n");
		} else if (!strcmp(cmd_argv[0], "load")) {
			load_kv(atoi(cmd_argv[1]));

		} else if (!strcmp(cmd_argv[0], "quit") || !strcmp(cmd_argv[0], "q")) {
			break;
		}

	}

}

char cmd[CMD_LEN];
void printCMDline (char **cmd_argv, int *cmd_argc) {
	printf("small_kvs> ");
	scanf("%[^\n]s",cmd);
	// remove new line
	getchar();

	//printf("%s\n", cmd);
	
	*cmd_argc = 0;
	cmd_argv[*cmd_argc] = strtok(cmd, " ");

	while (cmd_argv[*cmd_argc] !=  NULL) {
		cmd_argv[++*cmd_argc] = strtok(NULL, " ");
		if (*cmd_argc == 5) {
			printf("cmd argument limit (<5)\n");
			break;
		}
	}
}

int put_kv (const char * key, const char * value) {
	FILE *fp;
	
	fp = fopen("/tmp/small_kvs.txt","a+");
	fprintf(fp, "%s %s\n", key, value);
	fclose(fp);
	//fp = fopen("/tmp/test.txt","r");
}

int get_kv (const char * key, char * value) {
	FILE *fp;
	char key_buf [KEY_SIZE];
	char value_buf [VALUE_SIZE];
	
	fp = fopen("/tmp/small_kvs.txt","r");
	while (fscanf(fp, "%s %s", key_buf, value_buf) != EOF) {
		if (!strcmp(key,key_buf)) {
			strcpy(value, value_buf);
		}
	}
	fclose(fp);
}

void get_all () {
	FILE *fp;
	char key_buf [KEY_SIZE];
	char value_buf [VALUE_SIZE];

	kv_tuple kvs[1024];
	int kvs_size = 0;
	
	fp = fopen("/tmp/small_kvs.txt","r");
	if (!fp) {
		return;
	}

	while (fscanf(fp, "%s %s", key_buf, value_buf) != EOF) {
		int new = 1;
		for (int i = 0; i < kvs_size; i++) {
			if (!strcmp(kvs[i].key, key_buf)) {
				new = 0;
				strcpy(kvs[i].value, value_buf);
			}
		}
		if (new) {
			strcpy(kvs[kvs_size].key, key_buf);
			strcpy(kvs[kvs_size].value, value_buf);
			kvs_size ++;
		}
	}

	for (int i = 0; i < kvs_size; i++) {
		printf("key: %s value: %s\n", kvs[i].key, kvs[i].value);
	}
	
	fclose(fp);
}

void load_kv(int number) {

	srand(time(NULL));
	for (int i = 0; i < number; i++) {
		char key[KEY_SIZE];
		char value[VALUE_SIZE];

		memset (key, 0, KEY_SIZE);
		memset (value, 0, VALUE_SIZE);

		for (int j = 0; j < KEY_SIZE - 1; j++) {
			key[j] = rand() % 26 + 'A';
		}
		
		for (int j = 0; j < VALUE_SIZE - 1; j++) {
			value[j] = rand() % 26 + 'a';
		}

		put_kv(key, value);

	}
}
