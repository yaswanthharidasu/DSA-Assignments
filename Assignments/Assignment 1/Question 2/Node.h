using namespace std;

// Node of Doubly linked list
template< class key_type, class value_type>
class Node{
    public:
    key_type key;
    value_type value;
    Node<key_type, value_type> *prev;
    Node<key_type, value_type> *next;

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