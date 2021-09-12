#include<iostream>
template <class T>
class Node{
    public:
    int row, column;
    T value;
    Node *next;
    Node(int row, int column, T value);
};

template<class T>
class LinkedList{
    public:
    Node<T> *head;
    T **matrix;
    // Constructor
    LinkedList(int rows, int columns, int NNZ, T **matrix);
    // Converts into sparse matrix
    void toSparse();
};