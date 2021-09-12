#include"LLRepresentation.h"

template <class T>
class LLOps{
    public: 
    Node<T>* addition(LinkedList<T> m1, LinkedList<T> m2);

    Node<T>* multiplication(LinkedList<T> m1, LinkedList<T> m2);

    Node<T>* transpose(LinkedList<T> m);

    void findMid(Node<T> *head, Node<T> **left, Node<T> **right);
    
    void mergeSort(Node<T> **start);
    
    Node<T>* merge(Node<T> *left, Node<T> *right);

    Node<T>* alreadyPresent(Node<T> *head, int row, int column);
};