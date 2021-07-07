#pragma warning(disable:4996)
#include "hashmap.h"
#include <stdbool.h>
int curSize=0;

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

void updateCache(unsigned char ipAddr[4], const char domain[])
{   char* cht;
	strcpy(cht,domain);
	char *tmp = get(cht, cachemap, CACHESIZE);
	if (tmp) {
		//find in cache, update its position to the head
		struct Node *t=head,*tmp=NULL;
		if (memcmp(t->domain, domain, strlen(domain)) == 0) {
			return;
		}
		while (t->next != NULL) {
			if (memcmp(t->next->domain, domain, strlen(domain)) == 0) {
				if (tail == t->next) {
					tail = t;
				}
				tmp = t->next;
				t->next->pre->next = t->next->next;
				tmp->pre = NULL;
				tmp->next = head;
				head->pre = tmp;
				head = tmp;
				break;
			}
			t = t->next;
		}
	}
	else {
		struct Node* q= (struct Node *)malloc(sizeof(struct Node));
		memcpy(q->domain, domain, sizeof(q->domain));
		//not in cache
		//check current size whether less than or equals to cache size
		if (curSize < CACHESIZE) {
			char* cht;
			strcpy(cht,domain);
			install(cht, (char*)ipAddr, cachemap, CACHESIZE);
			if (curSize == 0) {
				struct Node * tmp = head;
				head = q;
				tail = q;
				free(tmp);
				head->pre = NULL;
				head->next = NULL;
				curSize++;
				return;
			}
			curSize++;
			head->pre = q;
			q->next = head;
			head = q;
			head->pre = NULL;
		}
		else {
			//delete tail
			char* cht;
	strcpy(cht,domain);
			install(cht, (char*)ipAddr, cachemap,CACHESIZE);
			q->next = head;
			head->pre=q;
			head = q;
			head->pre = NULL;
			q = tail;
			tail = tail->pre;
			tail->next = NULL;
			deleteMapNode(q->domain, cachemap, CACHESIZE);
			free(q);
		}

	}

}

bool findInCache(unsigned char ipAddr[4], const char domain[])
{
	if (!findNode(ipAddr, domain, cachemap,CACHESIZE)) {
				return false;
	}

	updateCache(ipAddr, domain);
	return true;
}