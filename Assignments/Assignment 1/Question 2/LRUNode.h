#define Node LRUNode<key_type, value_type>
using namespace std;

// Node of Doubly linked list
template< class key_type, class value_type>
class LRUNode{
    public:
    key_type key;
    value_type value;
    Node *prev, *next;

    Node(){
        prev = NULL;
        next = NULL;
    }

    Node(key_type key, value_type value){
        this->key = key;
        this->value = value;
        prev = NULL;
        next = NULL;
    }

};