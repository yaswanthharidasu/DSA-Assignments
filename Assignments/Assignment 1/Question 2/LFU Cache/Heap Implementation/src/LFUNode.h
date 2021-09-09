using namespace std;

// Node of the heap array
class LFUNode{
    public:
    
    int key;
    int value;
    long long frequency;
    long long timer;

    // Empty Constructor
    LFUNode();

    LFUNode(int key, int value, long long timer);

};