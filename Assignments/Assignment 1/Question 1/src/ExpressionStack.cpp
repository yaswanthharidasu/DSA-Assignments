#include<iostream>
#include"ExpressionStack.h"

using namespace std;

// Constructor which intializes head to NULL
ExpressionStack :: ExpressionStack(){
    head = NULL;
}

// Clear the stack when the destructor is called
ExpressionStack :: ~ExpressionStack(){
    // cout<<"Stack destructor is invoked"<<endl;
    this->clearStack();
}

// Used to check whether stack is empty or not
bool ExpressionStack :: empty(){
    if(head == NULL)
        return true;
    else   
        return false;
}

// Returns the top of the stack value
string ExpressionStack :: top(){
    string topToken;
    if(!this->empty()){
        topToken = head->current;
    }
    return topToken;
}

// Inserts new element into the stack
void ExpressionStack :: push(string ch){
    // Creating a node with the current token
    Node *newNode = new Node(ch);
    // Stack is empty
    if(head == NULL){
        head = newNode;
    }
    else{
        newNode->next = head;
        head = newNode;
    }
}

// Removes the top element from stack and returns it.
string ExpressionStack :: pop(){
    string poppedNode;
    // Check for underflow condition .i.e. stack is not empty
    if(!this->empty()){
        Node *temp = head;
        head = head->next;
        poppedNode = temp->current;
        temp->next = NULL;
        delete(temp);
    }
    else{
        cout<<"Stack underflow!!"<<endl;
    }  

    return poppedNode;
}

// Prints the elements of stack
void ExpressionStack :: printStack(){
    if(this->empty()){
        cout<<"Stack is empty"<<endl;
    }
    else{
        cout<<"Stack elements:"<<endl;
        Node *temp = head;
        while(temp != NULL){
            cout<<temp->current<<" ";
            temp = temp->next;
        }
        cout<<endl;
    }
}

// Removes all elements from the stack
void ExpressionStack :: clearStack(){
    // cout<<"Stack is being cleared"<<endl;
    while(!this->empty()){
        // Storing head node in temp so that the memory allocated to head can be freed.
        Node *temp = head;
        // Moving head to the next token
        head = head->next;
        temp->next = NULL;
        delete(temp);
    }
}
    
