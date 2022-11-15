#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "small_kvs_interface.h"


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
