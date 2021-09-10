#include"LLRepresentation.h"
#include<iostream>
using namespace std;

Node :: Node(int row, int column, int value){
    this->row = row;
    this->column = column;
    this->value = value;
    this->next = NULL;
}

LinkedList :: LinkedList(int rows, int columns, int NNZ, int **matrix){
    this->matrix = matrix;
    head = new Node(rows, columns, NNZ);
}

void LinkedList :: toSparse(){
    int rows = head->row, columns = head->column;
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(matrix[i][j] == 0)
                continue;
            Node *newNode = new Node(i, j, matrix[i][j]);
            Node *temp = head;
            while(temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    }

    Node *temp = head;
    while(temp != NULL){
        cout<<temp->row<<"\t| "<<temp->column<<"\t| "<<temp->value<<endl;
        temp = temp->next;
    }
}