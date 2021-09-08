#include"LRUNode.h"
#include<unordered_map>

using namespace std;

// Uses Doubly linked list for accessing least recentyly used key is located at the beginning of DLL
// hashtable for retreving the values of keys in O(1) 
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