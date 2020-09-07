#define maxn 1000001
#define maxm 26+10+2
#define maxStr 1001

#define maxCacheSize 4
struct Trie{
    int tree[maxn][maxm];       //字典树
    int pre[maxn];              //记录父亲节点
    bool endFlag[maxn];         //判断节点是否为一个单词的结束
    int totalNode;              //总节点数
    unsigned char toIp[maxn][4]; //
}*cacheTrie , *tableTrie;;
struct Node{
    char domain[256];
    struct Node *next;
}*head,*tail;

int cacheSize;
void output();
bool findInCache(unsigned char ipAddr[4], const char domain[]);
bool findInTable(unsigned char ipAddr[4], const char domain[]);
void updateCache(unsigned char* ipAddr, char domain[]);
void simplifyName(char* str);
void insertNode(struct Trie* trie , char* str ,unsigned char ip[4]);
void deleteNode(struct Trie* trie ,char* str);
int findNode(struct Trie* trie ,char* str);
void transIp(unsigned char ip[4] , char *rowIp);