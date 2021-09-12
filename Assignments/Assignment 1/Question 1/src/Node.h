#ifndef __NODE__
#define __NODE__

#include<string>
using namespace std;

// Node of a singly linked list
class Node
{
    public:
    string current;
    Node *next;

    Node(string token);
};

#endif