#include"LRUNode.h"
#include<iostream>

LRUNode :: LRUNode(){
    prev = NULL;
    next = NULL;
}

LRUNode :: LRUNode(int key, int value){
    this->key = key;
    this->value = value;
    prev = NULL;
    next = NULL;
}
