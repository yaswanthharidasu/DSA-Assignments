#include<iostream>
#include"Node.h"

using namespace std;

// Custom stack which uses the linked list data structure
// Each node of is custom_type (.i.e. stack can be of any type according to given datatype)
template<class custom_type>
class MyStack{

    // Head node which points to the top of the stack
    Node<custom_type> *head;

    public:
    // Constructor which intializes head to NULL
    MyStack(){
        head = NULL;
    }

    // Clear the stack when the destructor is called
    ~MyStack(){
        // cout<<"Stack destructor is invoked"<<endl;
        this->clearStack();
    }

    // Used to check whether stack is empty or not
    bool empty(){
        if(head == NULL)
            return true;
        else   
            return false;
    }

    // Returns the top of the stack value
    custom_type top(){
        custom_type topToken;
        if(!this->empty()){
            topToken = head->current;
        }
        return topToken;
    }

    // Inserts new element into the stack
    void push(custom_type ch){
        // Creating a node with the current token
        Node<custom_type> *newNode = new Node<custom_type>(ch);
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
    custom_type pop(){
        custom_type poppedNode;
        // Check for underflow condition .i.e. stack is not empty
        if(!this->empty()){
            Node<custom_type> *temp = head;
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
    void printStack(){
        if(this->empty()){
            cout<<"Stack is empty"<<endl;
        }
        else{
            cout<<"Stack elements:"<<endl;
            Node<custom_type> *temp = head;
            while(temp != NULL){
                cout<<temp->current<<" ";
                temp = temp->next;
            }
            cout<<endl;
        }
    }

    // Removes all elements from the stack
    void clearStack(){
        // cout<<"Stack is being cleared"<<endl;
        while(!this->empty()){
            // Storing head node in temp so that the memory allocated to head can be freed.
            Node<custom_type> *temp = head;
            // Moving head to the next token
            head = head->next;
            temp->next = NULL;
            delete(temp);
        }
    }
    
};