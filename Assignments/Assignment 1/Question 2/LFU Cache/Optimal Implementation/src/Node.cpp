#include"Node.h"
using namespace std;

KeyNode :: KeyNode(int key, int value){
    this->key = key;
    this->value = value;
    prev = NULL;
    next = NULL;
    freqNode = NULL;
}

FrequencyNode :: FrequencyNode(int frequency){
    this->frequency = frequency;
    prev = NULL;
    next = NULL;

    keysHead = new KeyNode(-1, -1);
    keysTail = new KeyNode(-1, -1);
    keysHead->next = keysTail;
    keysTail->prev = keysHead;
}