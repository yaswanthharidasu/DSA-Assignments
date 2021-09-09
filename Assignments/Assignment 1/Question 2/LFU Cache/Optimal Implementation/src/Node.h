#include<iostream>
using namespace std;

class FrequencyNode;

class KeyNode{

    public:
    int key, value;
    KeyNode *prev, *next;
    FrequencyNode *freqNode;

    KeyNode(int key, int value);
};

class FrequencyNode{

    public:
    int frequency;
    FrequencyNode *prev, *next;
    KeyNode *keysHead, *keysTail;

    FrequencyNode(int frequency);
};