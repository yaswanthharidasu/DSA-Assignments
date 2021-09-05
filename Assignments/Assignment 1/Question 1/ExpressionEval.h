#include<iostream>
#include<string>
#include"MyStack.h"

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

// Performs addition of two integers which are provided as strings
string add(string op1, string op2){

    string rev1, rev2, result;

    // Make sure op1 is greater than op 2
    if(op2.size() > op1.size()){
        string temp = op1;
        op1 = op2;
        op2 = temp;
    }

    // As integers can be of varying lengths, reverse the strings so that we correctly add the integers from the unit's place
    rev1 = string(op1.rbegin(), op1.rend());
    rev2 = string(op2.rbegin(), op2.rend());

    // Initially the carry is set to zero
    int carry = 0;
    int i = 0;

    // Adding the digits of two strings along with the carry and the carry obtained is passed to next digits
    while(i < rev2.length()){
        int sum = (rev1[i]-'0') + (rev2[i]-'0') + carry;
        carry = sum/10;
        result += (sum%10 + '0');
        i++;
    }
    // There can be some characters left in the string 1 as it is greater number
    while(i < rev1.length()){
        int sum = (rev1[i]-'0') + carry;
        carry = sum/10;
        result += (sum%10 + '0');
        i++;    
    }
    // If any carry is left then append it to the result.
    if(carry != 0){
        result += (carry + '0');
    }

    // Reverse the result
    result = string(result.rbegin(), result.rend());

    return result;

}

// Performs subtraction of two integers which are provided as strings
string sub(string op1, string op2){
    
    if(op2.length() > op1.length()){
        string temp = op1;
        op1 = op2;
        op2 = temp;
    }

    string rev1, rev2, result;

    rev1 = string(op1.rbegin(), op1.rend());
    rev2 = string(op2.rbegin(), op2.rend());

    ll borrow = 0;

    ll i=0, n1, n2;
    while(i < op2.length()){
        n1 = rev1[i]-'0'-borrow;
        n2 = rev2[i]-'0';

        if(n1 >= n2){
            result += ((n1-n2)+'0');
            borrow = 0;
        }
        else{
            n1 += 10;
            result += ((n1-n2)+'0');
            borrow = 1;
        }
        i++;
    }

    // Process the greater number if there any digits left
    while(i < op1.length()){
        n1 = rev1[i]-'0'-borrow;
        if(n1 >= 0){
            result += (n1+'0');
            borrow = 0;
        }
        else{
            n1 += 10;
            result += (n1+'0');
            borrow = 1;
        }
        i++;
    }

    // Remove any leading zeroes
    while(result.length() > 1 && result[result.length()-1] == '0')
        result.pop_back();

    result = string(result.rbegin(), result.rend());
    return result;
}

// Performs multiplication of two integers which are provided as strings
string mul(string op1, string op2){
    // If any of the operand is zero then simply return zero
    if(op1 == "0" || op2 == "0")
        return "0";
    
    // Make sure op1 is greater than op 2
    if(op2.size() > op1.size()){
        string temp = op1;
        op1 = op2;
        op2 = temp;
    }

    // The result can atmost of size op1.length()+op2.length()
    // Hence create a string 'result' of size op1.length()+op2.length()
    string result(op1.length()+op2.length(), 0);

    for(int i=op2.length()-1; i>=0; i--){
        for(int j=op1.length()-1; j>=0; j--){
            // Adding result[i+j+1] if there exists carry
            int val = (op2[i]-'0')*(op1[j]-'0') + result[i+j+1];
            // Storing the carry 
            result[i+j] += val/10;
            result[i+j+1] = val%10;
        }
    }

    // Now convert the result into string by adding '0' to each character of string
    for(int i=0; i<result.length(); i++){
        result[i] += '0';
    }

    // Sometimes the result can be of size op1.length()+op2.length()-1
    // The first element of result will be zero in those cases. Thus return the result without the leading zero
    return result[0] == '0' ? result.substr(1) : result;
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