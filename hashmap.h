#ifndef HASHMAP_H
#define HASHMAP_H


#pragma warning(disable:4996)
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include "hashmap.h"
#include <stdbool.h>
extern int HASHSIZE, CACHESIZE;
//Realise hashmap to store infomation in dnsrelay.txt
//key:domain name
//value::ip address
struct HashNode {
	char key[255];
	char val[20];
	struct HashNode *next;
};
struct Node {
	char domain[256];
	struct Node *next;
	struct Node *pre;
};
extern struct Node *head, *tail;
extern struct  HashNode* hashmap[1000], *cachemap[100];



//Realise hashmap to store infomation in dnsrelay.txt
//key:domain name
//value::ip address

unsigned int hash(char *str, int size);
void initHashMap(struct HashNode* map[], int size);
struct HashNode* lookup(char* s, struct HashNode* map[], int size);
char* get(char* key, struct HashNode* map[], int size);
void install(char* k, char* v, struct HashNode* map[], int size);
void cleanup(struct HashNode* map[], int size);
void deleteMapNode( const char domain[], struct HashNode* map[], int size);
bool findNode(unsigned char ipAddr[4], const char domain[], struct HashNode* map[], int size);
#endif //