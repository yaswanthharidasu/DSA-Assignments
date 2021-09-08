#include<iostream>
#include<unordered_map>
#include"LRUNode.h"
#define Node LRUNode<key_type, value_type> 

using namespace std;

// Uses Doubly linked list for accessing least recentyly used key is located at the beginning of DLL
// hashtable for retreving the values of keys in O(1) 
template<class key_type, class value_type> 
class LRUCache{

    int capacity;
    // For doubly linked list
    Node *head, *tail;
    // For hashtable
    unordered_map<int, Node*> hashtable;

    public:
    // Constructor
    LRUCache(int capacity){
        this->capacity = capacity;
        // Initially DLL is empty, create head and tail nodes
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }

    // Inserts the addNode at the beginning of DLL
    void insertAtFront(Node *addNode){
        // At first, stored prev and next of the new node
        addNode->next = head->next;
        addNode->prev = head;
        // Then changed the links in DLL
        head->next = addNode;
        addNode->next->prev = addNode;
    }

    // Removes the deleteNode from the DLL and frees the memory
    void removeNode(Node *deleteNode){
        deleteNode->prev->next = deleteNode->next;
        deleteNode->next->prev = deleteNode->prev;
    }

    // Inserts new key value pair in the cache
    void set(key_type key, value_type value){
        // If key is already present then deleted corresponding node from DLL and bring that node to the first as it will be the Least recently used. 
        // Instead of bringing the node to the first, delete that node and insert at the first  
        if(hashtable.count(key) == 1){
            Node *present = hashtable[key];
            removeNode(present);
        }
        // Not present and if capacity is exceeded then remove the last node from DLL and its corresponding key from hashtable
        else if(hashtable.size() == capacity){
            // Last node is obtained using previous pointer of tail
            Node *deleteNode = tail->prev;
            // Key to be deleted from the hashtable
            key_type deleteKey = deleteNode->key;

            removeNode(deleteNode);
            hashtable.erase(deleteKey);
        }

        Node *newKey = new Node (key, value);
        insertAtFront(newKey);

        // After inserting in DLL, update in hashtable
        hashtable[key] = newKey;
    }
    
    // Returns the value associated with the key in cache
    value_type get(key_type key){
        // Key is not present in the cache
        if(hashtable.count(key) == 0){
            // cout<<"Key not present in the cache"<<endl;
            return -1; 
        }

        // Key present then return key using hashtable and also bring that node to the first as it is Least recently used
        Node *present = hashtable[key];
        value_type value = present->value;
        removeNode(present);

        // After removing and freeing the node, create new node with the same key, value and insert it at the beginning
        Node *newKey = new Node (key, value);
        insertAtFront(newKey);
        // After inserting in DLL, update in hashtable
        hashtable[key] = newKey;
        return value;
    }

};