#include"LLOps.h"

Node* LLOps :: addition(LinkedList mat1, LinkedList mat2){
    Node *m1 = mat1.head, *m2 = mat2.head;
    if(m1->row != m2->row || m1->column != m2->column)
        return NULL;

    Node *result = new Node(m1->row, m1->column, 0); 

    int NNZ = 0;

    Node *temp = result;

    m1 = m1->next, m2 = m2->next;

    while(m1 != NULL && m2 != NULL){
        if(m1->row == m2->row && m1->column == m2->column){
            Node *newNode = new Node(m1->row, m1->column, m1->value+m2->value);
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