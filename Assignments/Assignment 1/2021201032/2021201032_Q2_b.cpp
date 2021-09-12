#include<iostream>
#include<unordered_map>
using namespace std;

// Using FrequencyNode class in KeyNode as well as KeyNode class in FrequencyNode
// Hence delcaring FrequencyNode class above so that it can be used in KeyNode class
class FrequencyNode;

// ================================================ Class KeyNode: Begin =============================================================================

// Node of Keys Doubly Linked list
class KeyNode{
    public:
    int key, value;
    KeyNode *prev, *next;
    FrequencyNode *freqNode;
    // Constructor
    KeyNode(int key, int value);
};

KeyNode :: KeyNode(int key, int value){
    this->key = key;
    this->value = value;
    prev = NULL;
    next = NULL;
    freqNode = NULL;
}

// ================================================ Class KeyNode: End ===============================================================================

// ================================================ Class FrequencyNode: Begin =======================================================================

// Node of Frequencies Doubly Linked List
class FrequencyNode{
    public:
    int frequency;
    FrequencyNode *prev, *next;
    KeyNode *keysHead, *keysTail;
    // Constructor
    FrequencyNode(int frequency);
};

FrequencyNode :: FrequencyNode(int frequency){
    this->frequency = frequency;
    prev = NULL;
    next = NULL;

    keysHead = new KeyNode(-1, -1);
    keysTail = new KeyNode(-1, -1);
    keysHead->next = keysTail;
    keysTail->prev = keysHead;
}

// ================================================ Class FrequencyNode: End =========================================================================

// ================================================ Class LFUCache: Begin ============================================================================

class LFUCache{
    int capacity;
    FrequencyNode *freqHead, *freqTail;
    unordered_map<int, KeyNode*> hashtable;

    public: 
    // Constructor
    LFUCache(int capacity);

    // Removes "node" from Doubly Linked List
    template <class T>
    void removeNode(T *node);

    // Inserts "node" after "head" in Doubly Linked List
    template <class T>
    void insertNode(T *node, T *head);

    // If key is present in cache then need it increment its frequency by 1 and peform necessary actions
    void keyPresent(KeyNode *nKey, FrequencyNode *nFreq);

    // Inserts new key,value pair in the cache
    void set(int key, int value);

    // Retrieves the value of key from the cache
    int get(int key);
};

LFUCache :: LFUCache(int capacity){
    this->capacity = capacity;
    freqHead = new FrequencyNode(0);
    freqTail = new FrequencyNode(0);

    freqHead->next = freqTail;
    freqTail->prev = freqHead;
}

template <class T>
void LFUCache :: insertNode(T *node, T *head){
    // At first, updated prev and next of the new node
    node->next = head->next;
    node->prev = head;
    // Then changed the links in the DLL
    head->next = node;
    node->next->prev = node;
}

template <class T>
void LFUCache :: removeNode(T *node){
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void LFUCache :: keyPresent(KeyNode *nKey, FrequencyNode *nFreq){
    // Frequency of the current key
    int currentFrequency = nFreq->frequency;
    // if next node in the frequencies DLL is of frequency != currentKey_Frequency + 1
    if(nFreq->next->frequency != currentFrequency+1){
        // Then create the new frequency node
        FrequencyNode *nextFreq = new FrequencyNode(currentFrequency+1);
        // Now adding the newly created Frequency node in the Frequencies DLL
        insertNode<FrequencyNode>(nextFreq, nFreq);
    }

    FrequencyNode *nextFreq = nFreq->next;
    // Removing the key from the current frequency keys DLL
    removeNode<KeyNode>(nKey);
    // Insert the key in the next frequency keys DLL
    insertNode<KeyNode>(nKey, nextFreq->keysHead);
    
    // After removing the key from the current frequency keys DLL, if the keys DLL becomes empty then remove that frequency node from the frequencies DLL
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
        // Pointing to the first node in the frequencies DLL
        FrequencyNode *firstFreqNode = freqHead->next;
        // Head of the keys in the current freqeuncy node
        KeyNode *keyHead = firstFreqNode->keysHead;
        // Tail of the keys in the current frequency node
        KeyNode *keyTail = firstFreqNode->keysTail;

        // Least frequent key of current frequency node is at the end of keys DLL
        KeyNode *LFKey = keyTail->prev;
        // Removing the least frequent key from the hashtable
        hashtable.erase(LFKey->key);
        // Removing the least frequent key from the keys DLL
        removeNode<KeyNode>(LFKey);
        
        // After removing the least frequent key from the keys DLL, if it is empty then remove the that frequency node from the frequencies DLL
        // Keys head points to tail .i.e. keys DLL is empty
        if(keyHead->next->key == -1){
            removeNode<FrequencyNode>(firstFreqNode);
        }
    }

    // Creating new key node with given key and value
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

// ================================================ Class LFUCache: End ==============================================================================

// ================================================ main() ===========================================================================================

int main(){
    cout<<"Enter Capacity of cache:";
    int capacity;
    cin>>capacity;

    LFUCache lfu(capacity);

    cout<<"======================================================================="<<endl;
    cout<<"Available options:"<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<"1. Insert into cache"<<endl;
    cout<<"2. Get value of Key from cache"<<endl;
    cout<<"3. Exit"<<endl;
    cout<<"======================================================================="<<endl;
    cout<<endl;

    int option, key, value;
    while(true){
        cout<<"Select option: ";
        cin>>option;
        if(option == 1){
            cout<<"Enter key and value to insert into cache: ";
            cin>>key>>value;
            lfu.set(key, value);
        }
        else if(option == 2){
            cout<<"Enter key to retrieve its value: ";
            cin>>key;
            value = lfu.get(key);
            cout<<"Value of key "<<key<<" is: "<<value<<endl;
        }
        else if(option == 3){
            break;
        }
        else{
            cout<<"Enter Valid option"<<endl;
        }
        cout<<endl;
    }
}