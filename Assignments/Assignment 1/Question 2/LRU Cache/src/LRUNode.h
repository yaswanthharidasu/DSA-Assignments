// LRUNode of Doubly linked list
class LRUNode{
    public:
    int key;
    int value;
    LRUNode *prev, *next;

    LRUNode(int key, int value);
};