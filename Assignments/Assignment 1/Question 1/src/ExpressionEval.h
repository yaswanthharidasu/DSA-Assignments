#include"BigInteger.h"
#include"ExpressionStack.h"

using namespace std;

class ExpressionEval{

    public:
    
    // Returns the precedence of the operators
    int precedence(string op);

    // Evaluates the given postfix expression and returns the result
    string postfixEval(string expression);

    // Converts the given infix expression into postfix expression
    string infixToPostfix(string input);

    // Utility function which uses the above functions and produces the result of the given arthimetic expression as following:
    // 1. Convert infix to postfix expression
    // 2. Evaluate the postfix expression to obtain the result
    string evaluate(string input);

};