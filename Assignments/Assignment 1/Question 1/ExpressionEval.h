#include<iostream>
#include<string>
#include"MyStack.h"
#include"ArithmeticOperations.h"

using namespace std;
typedef long long ll;

// Precedence of the operators are set as follows:
// * --> 1
// + --> 0
// - --> 0
int precedence(string op){
    if(op == "*")
        return 1;
    else
        return 0;
}

// Printing the string 
void printString(string str){
    for(auto ch: str){
        cout<<ch;
    }
    cout<<endl;
}

// Evaluates the given postfix expression and returns the result
string postfixEval(string expression){
    
    MyStack<string> operandStack;
    string operand;
    string op1, op2, result;

    for(int i=0; i<expression.size(); i++){
        if(expression[i] == '('){
            operand = "";
        }
        else if(expression[i] == ')'){
            operandStack.push(operand);
        }
        else if(expression[i] == '+'){
            op1 = operandStack.pop();
            op2 = operandStack.pop();
            operandStack.push(add(op2, op1));
        }
        else if(expression[i] == '-'){
            op1 = operandStack.pop();
            op2 = operandStack.pop();
            // Need to perfrom op2-op1
            // if op1.length() > op2.length() then it means op1 is greater than op2 hence negative number in intermediate output
            // if op1.length() == op2.length() then there may be cases where op1 is greater than op2
            if(op1.length()>op2.length()){
                cout<<"Negative integer occured in the expression"<<endl;
                return "-1";
            }
            if(op1.length() == op2.length() && op2.compare(op1) < 0){
                cout<<"Negative integer occured in the expression"<<endl;
                return "-1";
            }
            operandStack.push(sub(op2, op1));
        }
        else if(expression[i] == '*'){
            op1 = operandStack.pop();
            op2 = operandStack.pop();
            operandStack.push(mul(op2, op1));
        }
        else{
            operand += expression[i];
        }
    }

    return operandStack.pop();
}

// Converts the given infix expression into postfix expression
string infixToPostfix(string input){    

    // postfixExp holds the postfix expression of the given infix expression
    string postfixExp;
    // operandStack stores the operands based on their precedence
    MyStack<string> operandStack;

    // Making sure that each Integer is enclosed within the brackets so that we can identify the integers separately
    postfixExp += '(';

    for(int i=0; i<input.size(); i++){
        if(input[i] == '+' || input[i] == '-' || input[i] == '*'){
            // Whenever we come across an operator it means we crossed an integer. Thus, close the bracket.
            postfixExp += ')';      

            string token = "";
            token += input[i];

            while(!operandStack.empty() && precedence(token) <= precedence(operandStack.top())){
                postfixExp += operandStack.pop();
            }
            operandStack.push(token);

            // After processing the operator, next Integer will be processed. Thus, open the bracket.
            postfixExp += '(';
        }
        else{
            postfixExp += input[i];
        }
    }

    postfixExp += ')';
    while(!operandStack.empty()){
        postfixExp += operandStack.pop();
    }
    
    // printString(postfixExp);

    return postfixExp;
}

// Utility function which uses the above functions and produces the result of the given arthimetic expression as following:
// 1. Convert infix to postfix expression
// 2. Evaluate the postfix expression to obtain the result
string expEval(string input){
    string postfix = infixToPostfix(input);
    // cout<<"postfix:"<<postfix<<endl;
    string result = postfixEval(postfix);
    return result;
}