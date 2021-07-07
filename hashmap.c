#pragma warning(disable:4996)
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include "hashmap.h"
#include <stdbool.h>

//Realise hashmap to store infomation in dnsrelay.txt
//key:domain name
//value::ip address

unsigned int hash(char *str , int size) {
	unsigned int h = 0;
	for (; *str; str++) {
		h = *str + h * 31;

	}
	return h % size;
}
void initHashMap(struct HashNode* map[], int size) {
	int i ;
	for (i = 0; i < size; i++) {
		map[i] = NULL;
	}
}
//collide
struct HashNode* lookup(char* s, struct HashNode* map[], int size) {
	unsigned index = hash(s,size);
	struct HashNode *n = map[hash(s,size)];
	for (; n != NULL; n = n->next) {
		if (!strcmp(n->key, s)) {
			return n;
		}
	}
	return NULL;
}

char* get(char* key, struct HashNode* map[], int size) {
	struct HashNode* hn = lookup(key,map,size);
	if (hn == NULL) {
		return NULL;

	}
	else {
		return hn->val;
	}
}

void install(char* k, char* v, struct HashNode* map[], int size) {
	struct HashNode* n;
	if ((n = lookup(k,map,size)) == NULL) {
		n = (struct HashNode*)malloc(sizeof(struct HashNode));
		strcpy(n->key, k);
		unsigned index = hash(k,size);
		strcpy(n->val, v);
		n->next =map[index];
		map[index] = n;
	}
	else if(!strcmp(map[hash(k,size)]->val,"0.0.0.0")){
		return;
	}
	else {
		strcpy(n->val, v);
	}
}
void cleanup(struct HashNode* map[], int size) {
	struct HashNode *n, *t;
	for (int i = 0; i <size ; i++) {
		if (map[i] != NULL) {
			n = map[i];
			while (n != NULL) {
				t = n->next;
				free(n->key);
				free(n->val);
				free(n);
				n = t;
			}
		}
	}
}
void deleteMapNode(const char domain[], struct HashNode* map[], int size) {
	char* cht;
	strcpy(cht,domain);
	int index=hash(cht,size);
	struct HashNode* q = map[index],*t;
	if (q!=NULL&&strcmp(q->key, domain) == 0){
		q=q->next;
		map[index]=q;
	}
	else {
		while (q->next != NULL) {
			if (strcmp(q->next->key, domain) == 0) {
				t=q->next;
				q->next=q->next->next;
				//free(t);
				return;
			}
			q = q->next;
		}
	}
	

}
bool findNode(unsigned char ipAddr[4], const char domain[], struct HashNode* map[],int size) {
	char *cht;
	strcpy(cht,domain);
	char *tmp = get(cht, map,size);
	if (tmp == NULL) {
		return false;
	}
	char byte[3];
	int n = 0;
	unsigned char t[4];
	for (int i = 0; i < 4; i++)
	{
		int value = 0;
		for (int j = 0; j < 3; j++)
		{
			if ((*tmp == '.') || (*tmp == '\0'))
				break;
			byte[j] = *tmp;
			value = value * 10 + byte[j] - '0';
			tmp += 1;
		}

		t[n] = value;

		if (*tmp == '\0')
		{
			break;
		}
		else
		{
			tmp += 1;
			n += 1;
		}
	}
	memcpy(ipAddr, t, sizeof(unsigned char) * 4);

	return true;
}