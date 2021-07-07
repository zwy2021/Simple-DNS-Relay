#ifndef LRU_H
#define LRU_H

#pragma warning(disable:4996)
#include "hashmap.h"

void updateCache(unsigned char ipAddr[4], const char domain[]);
bool findInCache(unsigned char ipAddr[4], const char domain[]);
#endif //