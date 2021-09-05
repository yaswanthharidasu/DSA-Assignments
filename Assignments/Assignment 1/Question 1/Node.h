#include<iostream>
#include<string>

using namespace std;

template<class custom_type>
class Node
{
    public:

    custom_type current;
    Node<custom_type> *next;

    Node(custom_type token){
        this->current = token;
        next = NULL;
    }

};