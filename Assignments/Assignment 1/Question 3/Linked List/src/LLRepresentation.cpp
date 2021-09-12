#include"LLRepresentation.h"
#include<iostream>
using namespace std;

template<class T>
Node<T> :: Node(int row, int column, T value){
    this->row = row;
    this->column = column;
    this->value = value;
    this->next = NULL;
}

template<class T>
LinkedList<T> :: LinkedList(int rows, int columns, int NNZ, T **matrix){
    this->matrix = matrix;
    head = new Node<T>(rows, columns, NNZ);
}

template<class T>
void LinkedList<T> :: toSparse(){
    int rows = head->row, columns = head->column;
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(matrix[i][j] == 0)
                continue;
            Node<T> *newNode = new Node<T>(i, j, matrix[i][j]);
            Node<T> *temp = head;
            while(temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    }

    Node<T> *temp = head;
    while(temp != NULL){
        cout<<temp->row<<"\t| "<<temp->column<<"\t| "<<temp->value<<endl;
        temp = temp->next;
    }
}