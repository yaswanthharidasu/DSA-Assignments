#ifndef __EXPRESSIONSTACK__
#define __EXPRESSIONSTACK__

#include"Node.h"

using namespace std;

// Custom stack which uses the linked list data structure
// Each node of is string (.i.e. stack can be of any type according to given datatype)
class ExpressionStack{

    // Head node which points to the top of the stack
    Node *head;

    public:
    // Constructor which intializes head to NULL
    ExpressionStack();

    // Clear the stack when the destructor is called
    ~ExpressionStack();

    // Used to check whether stack is empty or not
    bool empty();

    // Returns the top of the stack value
    string top();

    // Inserts new element into the stack
    void push(string ch);

    // Removes the top element from stack and returns it.
    string pop();

    // Prints the elements of stack
    void printStack();

    // Removes all elements from the stack
    void clearStack();
};
#endif