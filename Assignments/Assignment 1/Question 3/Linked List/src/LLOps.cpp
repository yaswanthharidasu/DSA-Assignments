#include"LLOps.h"
#include<iostream>
using namespace std;

template <class T>
void LLOps<T> :: findMid(Node<T> *head, Node<T> **left, Node<T> **right){
    // Hare and tortoise algorithm to find mid point of Linked list
    Node<T> *tortoise = head, *hare = head->next;
    while(hare != NULL){
        hare = hare->next;
        if(hare != NULL){
            hare = hare->next;
            tortoise = tortoise->next;
        }
    }
    *left = head;
    *right = tortoise->next;
    // After assigning midpoint to right we need to break the list
    tortoise->next = NULL;
}

template <class T>
void LLOps<T> :: mergeSort(Node<T> **start){
    Node<T> *head = *start;
    if(head == NULL || head->next == NULL)
        return ;

    Node<T> *left, *right;
    // Finding midpoint of the linked list
    findMid(head, &left, &right);
    // Sort the left and right LL
    mergeSort(&left);
    mergeSort(&right);
    // Merge left and right LL
    *start = merge(left, right);
}

template <class T>
Node<T>* LLOps<T> :: merge(Node<T> *left, Node<T> *right){
    if(left == NULL)
        return right;
    if(right == NULL)
        return left;
    Node<T> *head = NULL;
    if((left->row < right->row) || (left->row == right->row && left->column < right->column)){
        head = left;
        head->next = merge(left->next, right);
    }
    else{
        head = right;
        head->next = merge(left, right->next);
    }
    return head;
}

template <class T>
Node<T>* LLOps<T> :: alreadyPresent(Node<T> *head, int row, int column){
    if(head == NULL)
        return NULL;
    while(head != NULL){
        if(head->row == row && head->column == column){
            return head;
        }
        head = head->next;
    }
    return head;
}

template <class T>
Node<T>* LLOps<T> :: addition(LinkedList<T> mat1, LinkedList<T> mat2){
    Node<T> *m1 = mat1.head, *m2 = mat2.head;
    if(m1->row != m2->row || m1->column != m2->column)
        return NULL;

    Node<T> *result = new Node<T>(m1->row, m1->column, 0); 

    int NNZ = 0;

    Node<T> *temp = result;

    m1 = m1->next, m2 = m2->next;

    while(m1 != NULL && m2 != NULL){
        if(m1->row == m2->row && m1->column == m2->column){
            Node<T> *newNode = new Node<T>(m1->row, m1->column, m1->value+m2->value);
            temp->next = newNode;
            m1 = m1->next, m2 = m2->next;
        }
        else if((m1->row > m2->row) || (m1->row == m2->row && m1->column > m2->column)){
            temp->next = m2;
            m2 = m2->next;
        }
        else{
            temp->next = m1;
            m1 = m1->next;
        }
        temp = temp->next;
        NNZ++;
    }
    while(m1 != NULL){
        temp->next = m1;
        temp = temp->next;
        m1 = m1->next;
        NNZ++;
    }
    while(m2 != NULL){
        temp->next = m2;
        temp = temp->next;
        m2 = m2->next; 
        NNZ++; 
    }
    result->value = NNZ;
    return result;
}

template <class T>
Node<T>* LLOps<T> :: transpose(LinkedList<T> mat){
    Node<T> *m = mat.head;
    Node<T> *result = new Node<T>(m->column, m->row, m->value);
    Node<T> *tempM = m->next, *tempResult = result;
    while(tempM != NULL){
        Node<T> *newNode = new Node<T>(tempM->column, tempM->row, tempM->value);
        tempResult->next = newNode;
        tempM = tempM->next;
        tempResult = tempResult->next;
    }
    // First node consists of no.of rows, columns, and NNZ values. Hence sort from the next element
    mergeSort(&result->next);
    return result;
}

template <class T>
Node<T>* LLOps<T> :: multiplication(LinkedList<T> mat1, LinkedList<T> mat2){
    Node<T> *m1 = mat1.head;
    Node<T> *m2 = mat2.head;
    if(m1->column != m2->row){
        cout<<"Multiplication not possible"<<endl;
        return NULL;
    }       
    Node<T> *result = new Node<T>(m1->row, m2->column, 0);
    Node<T> *tempOne = m1->next, *tempTwo = m2->next, *tempResult = result;
    int NNZ = 0;    
    while(tempOne != NULL){
        // Intializing tempTwo to beginning for every iteration
        tempTwo = m2->next;
        while(tempTwo != NULL){
            if(tempOne->column == tempTwo->row){
                Node<T> *temp;
                if((temp = alreadyPresent(result->next, tempOne->row, tempTwo->column)) != NULL){
                    temp->value += (tempOne->value * tempTwo->value);
                }
                else{
                    Node<T> *newNode = new Node<T>(tempOne->row, tempTwo->column, (tempOne->value * tempTwo->value));
                    tempResult->next = newNode;
                    tempResult = tempResult->next;
                    NNZ += 1;
                }
            }
            tempTwo = tempTwo->next;
        }
        tempOne = tempOne->next;
    }
    result->value = NNZ;
    mergeSort(&result->next);
    return result;
}