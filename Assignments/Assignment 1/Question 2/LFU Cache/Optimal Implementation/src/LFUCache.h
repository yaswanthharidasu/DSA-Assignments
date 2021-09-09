#include "Node.h"
#include<unordered_map>
using namespace std;

class LFUCache{

    int capacity;
    FrequencyNode *freqHead, *freqTail;
    unordered_map<int, KeyNode*> hashtable;

    public: 
    LFUCache(int capacity);

    template <class T>
    void removeNode(T *node);

    template <class T>
    void insertNode(T *node, T *head);

    void keyPresent(KeyNode *nKey, FrequencyNode *nFreq);

    void set(int key, int value);

    int get(int key);

    void printKeys();
};