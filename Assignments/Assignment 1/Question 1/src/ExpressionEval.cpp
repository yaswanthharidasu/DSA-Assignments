#include<iostream>
#include<string>
#include"ExpressionEval.h"

using namespace std;

// Precedence of the operators are set as follows:
// *    ==> 1
// +, - ==> 0
int ExpressionEval :: precedence(string op){
    if(op == "*")
        return 1;
    else
        return 0;
}

// Converts the given infix expression into postfix expression
string ExpressionEval :: infixToPostfix(string input){    

    ExpressionStack operatorStack;

    // postfixExp holds the postfix expression of the given infix expression
    string postfixExp;

    // Making sure that each Integer is enclosed within the brackets so that we can identify the integers separately
    postfixExp += '(';

    for(int i=0; i<input.size(); i++){
        if(input[i] == '+' || input[i] == '-' || input[i] == '*'){
            // Whenever we come across an operator it means we crossed an integer. Thus, close the bracket.
            postfixExp += ')';      

            string token = "";
            token += input[i];

            while(!operatorStack.empty() && precedence(token) <= precedence(operatorStack.top())){
                postfixExp += operatorStack.pop();
            }
            operatorStack.push(token);

            // After processing the operator, next Integer will be processed. Thus, open the bracket.
            postfixExp += '(';
        }
        else{
            postfixExp += input[i];
        }
    }

    postfixExp += ')';
    while(!operatorStack.empty()){
        postfixExp += operatorStack.pop();
    }
    
    // printString(postfixExp);

    return postfixExp;
}

// Evaluates the given postfix expression and returns the result
string ExpressionEval :: postfixEval(string expression){
    
    BigInteger bigInteger;
    ExpressionStack operandStack;

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
            operandStack.push(bigInteger.add(op2, op1));
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
            operandStack.push(bigInteger.subtract(op2, op1));
        }
        else if(expression[i] == '*'){
            op1 = operandStack.pop();
            op2 = operandStack.pop();
            operandStack.push(bigInteger.multiply(op2, op1));
        }
        else{
            operand += expression[i];
        }
    }

    return operandStack.pop();
}

// Utility function which uses the above functions and produces the result of the given arthimetic expression as following:
// 1. Convert infix to postfix expression
// 2. Evaluate the postfix expression to obtain the result
string ExpressionEval :: evaluate(string input){
    string postfix = infixToPostfix(input);
    // cout<<"postfix:"<<postfix<<endl;
    string result = postfixEval(postfix);
    return result;
}