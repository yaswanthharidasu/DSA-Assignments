#include<iostream>
class Node{
    public:
    int row, column, value;
    Node *next;
    Node(int row, int column, int value);
};


class LinkedList{
    public:
    Node *head;
    int **matrix;
    LinkedList(int rows, int columns, int NNZ, int **matrix);
    void toSparse();
};