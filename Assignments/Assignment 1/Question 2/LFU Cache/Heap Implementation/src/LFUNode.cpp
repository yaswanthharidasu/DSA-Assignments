#include "LFUNode.h"

LFUNode :: LFUNode(){
}

LFUNode :: LFUNode(int key, int value, long long timer){
    this->key = key;
    this->value = value;
    this->timer = timer;
    frequency = 1;
}

