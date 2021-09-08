#include<unordered_map>
#include"LFUNode.h"

// Uses Heap for accessing least frequently used keys 
// hashtable for retreving the values of keys in O(1) 
class LFUCache{
    
    private:
    LFUNode *heap;
    // Capacity of the cache
    int capacity;
    // No.of keys currently in the cache
    int keyCount;
    // The count of no.of operations performed on the cache
    long long timer;
    // Hashtable stores keys and indices of the key in the heap array
    unordered_map<int, int> hashtable;

    public:
    // Constructor
    LFUCache(int capacity);

    // Swaps heap keys and their respective indices in the hashtable
    void swap(int index1, int index2);

    // Returns least frequently used key
    int LFUKey();

    // Maintains heap property
    void heapify(int keyIndex);

    // Removes the least frequently used element which is nothing but the root of heap
    void removeLeastFrequentKey();

    // Inserts new key value pair in the cache
    void set(int key, int value);

    // Returns the value associated with the key in cache
    int get(int key);
};