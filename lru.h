#ifndef LRU_H
#define LRU_H

#pragma warning(disable:4996)
#include "hashmap.h"

/*void printCache()
{
	printf("\n===============Cache=============\n");
	struct Node *p = head->next;
	int cacheCount = 0;
	while (p != NULL)
	{
		int num = findNode(cacheTrie, p->domain);
		printf("%2d: %s => ", cacheCount++, p->domain);
		unsigned char ip[4];
		memcpy(ip, cacheTrie->toIp[num], sizeof(ip));
		printf("%u.%u.%u.%u\n", ip[0], ip[1], ip[2], ip[3]);
		p = p->next;
	}
	printf("\n");
}*/

void updateCache(unsigned char ipAddr[4], const char domain[]);
bool findInCache(unsigned char ipAddr[4], const char domain[]);
#endif //