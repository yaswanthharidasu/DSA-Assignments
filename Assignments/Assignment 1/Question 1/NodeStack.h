#include<iostream>
#include"Node.h"

using namespace std;

class MyStack{

    Node *head;

    public:
    MyStack(){
        head = NULL;
    }

    // Remove all elements from stack when the destructor is called
    ~MyStack(){
        cout<<"Stack destructor is invoked"<<endl;
        this->clearStack();
    }

    bool empty(){
        if(head == NULL)
            return true;
        else   
            return false;
    }

    string top(){
        string topToken;
        if(!this->empty()){
            topToken = head->currentToken;
        }
        return topToken;
    }

    void push(string ch){

        // Creating a node with the current token
        Node *newNode = new Node(ch);

        // Stack is empty
        if(head == NULL){
            head = newNode;
        }
        else{
            newNode->nextToken = head;
            head = newNode;
        }
    }

    string pop(){
        string poppedToken;
        // Check for underflow condition .i.e. stack is not empty
        if(!this->empty()){
            Node *temp = head;
            head = head->nextToken;
            poppedToken = temp->currentToken;
            temp->nextToken = NULL;
            delete(temp);
        }
        else{
            cout<<"Stack underflow!!"<<endl;
        }  

        return poppedToken;
    }

    void printStack(){
        if(this->empty()){
            cout<<"Stack is empty"<<endl;
        }
        else{
            cout<<"Stack elements:"<<endl;
            Node *temp = head;
            while(temp != NULL){
                cout<<temp->currentToken<<" ";
                temp = temp->nextToken;
            }
            cout<<endl;
        }
    }

    void clearStack(){
        cout<<"Stack is being cleared"<<endl;
        while(!this->empty()){
            // Storing head node in temp so that the memory allocated to head can be freed.
            Node* temp = head;
            // Moving head to the next token
            head = head->nextToken;
            temp->nextToken = NULL;
            delete(temp);
        }
    }


};