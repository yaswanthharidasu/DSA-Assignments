#include<iostream>
#include<unordered_map>
using namespace std;

// ================================================ Class LRUNode: Begin =============================================================================

// LRUNode of Doubly linked list
class LRUNode{
    public:
    int key;
    int value;
    LRUNode *prev, *next;

    LRUNode(int key, int value);
};

LRUNode :: LRUNode(int key, int value){
    this->key = key;
    this->value = value;
    prev = NULL;
    next = NULL;
}

// ================================================ Class LRUNode: End ===============================================================================

// ================================================ Class LRUCache: Begin ============================================================================

class LRUCache{
    private:
    int capacity;
    // For doubly linked list
    LRUNode *head, *tail;
    // Stores the key along with its prespective node of DLL
    unordered_map<int, LRUNode*> hashtable;

    public:
    // Constructor
    LRUCache(int capacity);

    // Inserts the addLRUNode at the beginning of DLL
    void insertAtFront(LRUNode *addLRUNode);

    // Removes the deleteLRUNode from the DLL and frees the memory
    void removeNode(LRUNode *deleteLRUNode);

    // Inserts new key value pair in the cache
    void set(int key, int value);
    
    // Returns the value associated with the key in cache
    int get(int key);
};

// Constructor
LRUCache :: LRUCache(int capacity){
    this->capacity = capacity;
    // Initially DLL is empty, create head and tail nodes
    head = new LRUNode(-1, -1);
    tail = new LRUNode(-1, -1);
    head->next = tail;
    tail->prev = head;
}

// Inserts the addNode at the beginning of DLL
void LRUCache :: insertAtFront(LRUNode *addNode){
    // At first, stored prev and next of the new node
    addNode->next = head->next;
    addNode->prev = head;
    // Then changed the links in DLL
    head->next = addNode;
    addNode->next->prev = addNode;
}

// Removes the deleteNode from the DLL and frees the memory
void LRUCache :: removeNode(LRUNode *deleteNode){
    deleteNode->prev->next = deleteNode->next;
    deleteNode->next->prev = deleteNode->prev;
}

// Inserts new key value pair in the cache
void LRUCache :: set(int key, int value){
    // If key is already present then deleted corresponding node from DLL and bring that node to the first as it will be the Least recently used. 
    // Instead of bringing the node to the first, delete that node and insert at the first  
    if(hashtable.count(key) == 1){
        LRUNode *present = hashtable[key];
        removeNode(present);
    }
    // Not present and if capacity is exceeded then remove the last node from DLL and its corresponding key from hashtable
    else if(hashtable.size() == capacity){
        // Last node is obtained using previous pointer of tail
        LRUNode *deleteNode = tail->prev;
        // Key to be deleted from the hashtable
        int deleteKey = deleteNode->key;

        removeNode(deleteNode);
        hashtable.erase(deleteKey);
    }

    LRUNode *newKey = new LRUNode(key, value);
    insertAtFront(newKey);

    // After inserting in DLL, update in hashtable
    hashtable[key] = newKey;
}

// Returns the value associated with the key in cache
int LRUCache :: get(int key){
    // Key is not present in the cache
    if(hashtable.count(key) == 0){
        // cout<<"Key not present in the cache"<<endl;
        return -1; 
    }

    // Key present then return key using hashtable and also bring that node to the first as it is Least recently used
    LRUNode *present = hashtable[key];
    int value = present->value;
    removeNode(present);

    // After removing and freeing the node, create new node with the same key, value and insert it at the beginning
    LRUNode *newKey = new LRUNode (key, value);
    insertAtFront(newKey);
    // After inserting in DLL, update in hashtable
    hashtable[key] = newKey;
    return value;
}

// ================================================ Class LRUCache: End ==============================================================================

// ================================================ main() ===========================================================================================

int main(){
    cout<<"Enter Capacity of cache:";
    int capacity;
    cin>>capacity;

    LRUCache lru(capacity);

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
            lru.set(key, value);
        }
        else if(option == 2){
            cout<<"Enter key to retrieve its value: ";
            cin>>key;
            value = lru.get(key);
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