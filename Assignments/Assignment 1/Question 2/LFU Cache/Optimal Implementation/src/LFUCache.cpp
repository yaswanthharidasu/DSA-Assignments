#include"LFUCache.h"
using namespace std;

LFUCache :: LFUCache(int capacity){
    this->capacity = capacity;
    freqHead = new FrequencyNode(0);
    freqTail = new FrequencyNode(0);

    freqHead->next = freqTail;
    freqTail->prev = freqHead;
}

template <class T>
void LFUCache :: insertNode(T *node, T *head){
    // At first, stored prev and next of the new node
    node->next = head->next;
    node->prev = head;
    // Then changed the links in DLL
    head->next = node;
    node->next->prev = node;
}

template <class T>
void LFUCache :: removeNode(T *node){
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void LFUCache :: keyPresent(KeyNode *nKey, FrequencyNode *nFreq){
    int currentFrequency = nFreq->frequency;
    // Next node in the frequency nodes DLL is of frequency = currentKey_Frequency + 1
    if(nFreq->next->frequency != currentFrequency+1){
        FrequencyNode *nextFreq = new FrequencyNode(currentFrequency+1);
        // Now adding the newly created Frequency node in the Frequency DLL
        insertNode<FrequencyNode>(nextFreq, nFreq);
    }

    FrequencyNode *nextFreq = nFreq->next;
    // Removing the key from the current frequency keys DLL
    removeNode<KeyNode>(nKey);
    // Insert the key in the next frequency keys DLL
    insertNode<KeyNode>(nKey, nextFreq->keysHead);
    
    if(nFreq->keysHead->next->key == -1){
        removeNode<FrequencyNode>(nFreq);
    }
    
    // Changing pointer in the keynode to the next frequency node
    nKey->freqNode = nextFreq;

}

void LFUCache :: set(int key, int value){

    if(capacity == 0)
        return ;

    // If key is already present in the cache
    if(hashtable.count(key) == 1){
        KeyNode *nKey = hashtable[key];
        FrequencyNode *nFreq = nKey->freqNode;
        nKey->value = value;
        keyPresent(nKey, nFreq);
        return ;
    }    
    
    // Cache is full
    if(capacity == hashtable.size()){
        // Pointing to the first node in the frequency nodes DLL
        FrequencyNode *firstFreqNode = freqHead->next;
        // Head of the keys in the current freqeuncy node
        KeyNode *keyHead = firstFreqNode->keysHead;
        // Tail of the keys in the current frequency node
        KeyNode *keyTail = firstFreqNode->keysTail;

        // Least frequent key of current frequency node which is at the end of DLL
        KeyNode *LFKey = keyTail->prev;
        // Removing the least frequent key from the hashtable
        hashtable.erase(LFKey->key);
        // Removing the least frequent key from the keys DLL
        removeNode<KeyNode>(LFKey);
        
        // After removing the least frequent key from the keys DLL, if it is empty then remove the that frequency node from the frequency DLL
        // Keys head points to tail .i.e. keys DLL is empty
        if(keyHead->next->key == -1){
            removeNode<FrequencyNode>(firstFreqNode);
        }
    }

    KeyNode *newKey = new KeyNode(key, value);

    // Intially every key has a frequency of 1. Hence check if there is a frequency node with value 1 or not
    // If there is no frequency node with value 1, create new frequency node with frequency = 1 and insert it at the beginning of the frequency nodes DLL
    if(freqHead->next->frequency != 1){
        FrequencyNode *nFreq = new FrequencyNode(1);
        insertNode<FrequencyNode>(nFreq, freqHead);
    }
    // Now there exists frequency node with value 1. Hence, add the key to the keys DLL of that frequency node
    FrequencyNode *firstFreqNode = freqHead->next;
    insertNode<KeyNode>(newKey, firstFreqNode->keysHead);

    // Point the new key node to the frequency node
    newKey->freqNode = firstFreqNode;
    // Inserting the key and its node in the hashtable
    hashtable[key] = newKey;
}

int LFUCache :: get(int key){
    // If key is not present in the cache
    if(hashtable.count(key) == 0){
        cout<<"Key not exists in the cache"<<endl;
        return -1;
    }

    // If key is present in the cache
    KeyNode *nKey = hashtable[key];
    FrequencyNode *nFreq = nKey->freqNode;
    int value = nKey->value;

    keyPresent(nKey, nFreq);

    return value;
}

void LFUCache :: printKeys(){
    FrequencyNode *temp = freqHead;
    while(temp!=NULL){
        cout<<"Freq:"<<temp->frequency<<" ";
        KeyNode *tempKey = temp->keysHead;
        while(tempKey != NULL){
            cout<<tempKey->key<<" ";
            tempKey = tempKey->next;
        }
        temp = temp->next;  
    }
}