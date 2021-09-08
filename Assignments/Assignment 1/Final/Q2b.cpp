#include<iostream>
#include<unordered_map>
using namespace std;

// ================================================ Class LFUNode: Begin =============================================================================

// Node of the heap array
class LFUNode{
    public:
    int key, value;
    long long frequency, timer;
    // Empty Constructor
    LFUNode();

    LFUNode(int key, int value, long long timer);
};

LFUNode :: LFUNode(){
}

LFUNode :: LFUNode(int key, int value, long long timer){
    this->key = key;
    this->value = value;
    this->timer = timer;
    frequency = 1;
}

// ================================================ Class LFUNode: End ===============================================================================

// ================================================ Class LFUCache: Begin ============================================================================

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

// Constructor
LFUCache :: LFUCache(int capacity){
    this->capacity = capacity;  
    timer = 0;
    keyCount = 0;
    heap = new LFUNode[capacity];
}

// Swaps heap keys and their respective indices in the hashtable
void LFUCache :: swap(int index1, int index2){
    // Updating the index in hashtable to maintain consistency
    int key1 = heap[index1].key;
    int key2 = heap[index2].key;
    hashtable[key1] = index2;
    hashtable[key2] = index1;
    // Swapping in the heap array
    LFUNode temp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
}

// Returns least frequently used key
int LFUCache :: LFUKey(){
    return heap[0].key;
}

// Maintains heap property
void LFUCache :: heapify(int keyIndex){
    int leftChildIndex = (2*keyIndex)+1;
    int rightChildIndex = (2*keyIndex)+2;
    
    int leastFreqKeyIndex = keyIndex;

    // Checking with left child
    if(leftChildIndex < keyCount && heap[leftChildIndex].frequency < heap[leastFreqKeyIndex].frequency){
        leastFreqKeyIndex = leftChildIndex;
    }
    else if(leftChildIndex < keyCount && heap[leftChildIndex].frequency == heap[leastFreqKeyIndex].frequency){
        if(heap[leftChildIndex].timer < heap[leastFreqKeyIndex].timer){
            leastFreqKeyIndex = leftChildIndex;
        }
    }
    // Checking with right child
    if(rightChildIndex < keyCount && heap[rightChildIndex].frequency < heap[leastFreqKeyIndex].frequency){
        leastFreqKeyIndex = rightChildIndex;
    }
    else if(rightChildIndex < keyCount && heap[rightChildIndex].frequency == heap[leastFreqKeyIndex].frequency){
        if(heap[rightChildIndex].timer < heap[leastFreqKeyIndex].timer){
            leastFreqKeyIndex = rightChildIndex;
        }
    }

    // Parent is updated with one of its child
    if(leastFreqKeyIndex != keyIndex){
        swap(leastFreqKeyIndex, keyIndex);
        heapify(leastFreqKeyIndex);
    }
}

// Removes the least frequently used element which is nothing but the root of heap
void LFUCache :: removeLeastFrequentKey(){
    // Cache is empty
    if(keyCount == 0)
        return ;
    // Cache consists of only one element
    if(keyCount == 1){
        keyCount--;
        return ;
    }
    // Placing the last element of array as root
    heap[0] = heap[keyCount-1];
    // Updating the index of last element to 0, as it is placed as root
    hashtable[heap[0].key] = 0;
    keyCount--;
    // Heapify on the root
    heapify(0);
}

// Inserts new key value pair in the cache
void LFUCache :: set(int key, int value){
    // If capacity is zero then cannot insert keys in the cache
    if(capacity == 0)
        return ;

    // Key already present in the cache
    if(hashtable.count(key) == 1){
        // Finding the index of key using the hashtable
        int keyIndex = hashtable[key];
        // Updating the new value and increasing the frequency by 1;
        heap[keyIndex].value = value;
        heap[keyIndex].frequency++;
        // Increasing the timer as it is the newly referenced element
        heap[keyIndex].timer = ++timer;
        // Performing heapify to maintain the heap property
        heapify(keyIndex);
    }
    // Key not present in the cache
    else{
        // If cache capacity is exceeded then remove the least frequently used key
        if(capacity == keyCount){
            // Removing the least frequently used key from hashtable
            hashtable.erase(heap[0].key);
            // Removing the least frequently used key from the heap
            removeLeastFrequentKey();
        }

        // Insert the new key into heap and store in hashtable
        LFUNode newKey(key, value, ++timer);
        // Inserting the key at the end in the array
        heap[keyCount] = newKey;
        // Inserting the key and the index in the hashtable
        hashtable[key] = keyCount++;

        // After inserting the new key at the end of array perform heapify upto root
        int index = (hashtable[key]-1)/2;
        while(index>=0){
            heapify(index);
            // Perform heapify on the root once and then come out of the loop
            if(index == 0)
                break;
            // Updating index to its parent index
            index = (index-1)/2;
        }
    }
}

// Returns the value associated with the key in cache
int LFUCache :: get(int key){
    // If key is not present in the cache
    if(hashtable.count(key) == 0){
        // cout<<key<<" not present in cache"<<endl;
        return -1;
    }
    // If key is present then return value and update its frequency
    int keyIndex = hashtable[key];
    int value = heap[keyIndex].value;
    heap[keyIndex].frequency++;
    heap[keyIndex].timer = ++timer;
    // After incrementing the timer and frequency of the key, perform heapify on the updated key LFUNode
    heapify(keyIndex);
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