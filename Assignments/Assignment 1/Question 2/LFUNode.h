#define Node LFUNode<key_type, value_type>
using namespace std;

// Node of the heap array
template< class key_type, class value_type>
class LFUNode{
    public:
    key_type key;
    value_type value;
    long long frequency;
    long long timer;

    Node(){
    }

    Node(key_type key, value_type value, long long timer){
        this->key = key;
        this->value = value;
        this->timer = timer;
        frequency = 1;
    }

};