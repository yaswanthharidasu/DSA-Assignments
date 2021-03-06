#include<string>
#include<iostream>
using namespace std;
typedef long long int ll;

// ================================================ Class Node: Begin ================================================================================
class Node
{
    public:
    string current;
    Node *next;

    Node(string token);
};

Node :: Node(string token){
    this->current = token;
    next = NULL;
}

// ================================================ Class Node: End ==================================================================================

// ================================================ Class Big Integer: End ===========================================================================

class BigInteger{

    public:
    // Performs addition of two integers which are provided as strings
    string add(string op1, string op2);

    // Performs subtraction of two integers which are provided as strings
    string subtract(string op1, string op2);

    // Performs multiplication of two integers which are provided as strings
    string multiply(string op1, string op2);

    // Performs exponentiation
    string exponentiation(string base, ll exp);

    // Performs num % mod
    string modulo(string num, string mod);

};

// Performs addition of two integers which are provided as strings
string BigInteger :: add(string op1, string op2){

    string rev1, rev2, result;

    // Make sure op1 is greater than op 2
    if(op2.size() > op1.size()){
        string temp = op1;
        op1 = op2;
        op2 = temp;
    }

    // As integers can be of varying lengths, reverse the strings so that we correctly add the llegers from the unit's place
    rev1 = string(op1.rbegin(), op1.rend());
    rev2 = string(op2.rbegin(), op2.rend());

    // Initially the carry is set to zero
    ll carry = 0;
    ll i = 0;

    // Adding the digits of two strings along with the carry and the carry obtained is passed to next digits
    while(i < rev2.length()){
        ll sum = (rev1[i]-'0') + (rev2[i]-'0') + carry;
        carry = sum/10;
        result += (sum%10 + '0');
        i++;
    }
    // There can be some characters left in the string 1 as it is greater number
    while(i < rev1.length()){
        ll sum = (rev1[i]-'0') + carry;
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
string BigInteger :: subtract(string op1, string op2){

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
string BigInteger :: multiply(string op1, string op2){
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

    for(ll i=op2.length()-1; i>=0; i--){
        for(ll j=op1.length()-1; j>=0; j--){
            int num1 = op1[j]-'0', num2 = op2[i]-'0';
            int ans = num1 * num2;
            // Adding result[i+j+1] if there exists carry
            ans += result[i+j+1];
            // Ans can be atmost of two digits. Hence, LSD is the result and MSD is the carry
            // Storing the carry for the next digit
            result[i+j] += ans/10;
            // Storing the value
            result[i+j+1] = ans%10;
        }
    }

    // Now convert the result into string by adding '0' to each character of string
    for(ll i=0; i<result.length(); i++){
        result[i] += '0';
    }

    // Sometimes the result can be of size op1.length()+op2.length()-1
    // The first element of result will be zero in those cases. Thus return the result without the leading zero
    return result[0] == '0' ? result.substr(1) : result;
}

// Performs exponentiation
string BigInteger :: exponentiation(string base, long long int exp){
    string result = "1";
    while(exp > 0){
        if(exp & 1){
            result = multiply(result, base);
        }
        base = multiply(base, base);
        exp = exp>>1;
    }
    return result;
}

// Performs num % mod
string BigInteger :: modulo(string num, string mod){
// Performing modulo by doubling the mod value until it is smaller than num
// Whenever the max value of mod is reached then subtract it from the num 
// Then again repeat the process.
// The doubled values are stored in the form of Linked list inorder to avoid calculating again
    Node *head = new Node(mod);
    string currentMod = mod;

    while(num.length() > currentMod.length() || (num.length() == currentMod.length() && num.compare(currentMod) > 0)){
        Node *twice = new Node(multiply(head->current, "2"));
        currentMod = twice->current;
        twice->next = head;
        head = twice;
    }
    // After reaching the max value of mod, do subtraction
    while(head!=NULL){
        if(num.length() < head->current.length() || (num.length() == head->current.length() && head->current.compare(num) > 0))
            head = head->next;
        else{
            num = subtract(num, head->current);
        }
    }
    return num;
}

// ================================================ Class BigInteger: End ============================================================================

// ================================================ Class BigInegerUtils: Begin ======================================================================

class BigIntegerUtils{
    public:
    // Performs factorial of input
    string factorial(string input);
    // Performs GCD of num1 and num2
    string GCD(string num1, string num2);
};

string BigIntegerUtils :: factorial(string input){
    BigInteger bigInteger;
    string op1, op2;
    op1 = input;
    op2 = bigInteger.subtract(op1, "1");

    while(op2 != "0"){
        op1 = bigInteger.multiply(op1, op2);
        op2 = bigInteger.subtract(op2, "1");
    }
    return op1;
}

string BigIntegerUtils :: GCD(string num1, string num2){
    BigInteger bigInteger;
    string gcd;
    if(num1 == "0"){
        gcd = num2;
        return gcd;
    }
    while(true){
        if(num2 == "0"){
            gcd = num1;
            break;
        }
        string ab = bigInteger.modulo(num1, num2);
        num1 = num2;
        num2 = ab;
    }
    return gcd;
}

// ================================================ Class BigInegerUtils: End ========================================================================

// ================================================ Class ExpressionStack: Begin =====================================================================

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

// ================================================ Class ExpressionStack: End =======================================================================

// ================================================ Class ExpressionEval: Begin ======================================================================

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

// Precedence of the operators are set as follows:
// *    ==> 1
// +, - ==> 0
int ExpressionEval :: precedence(string op){
    if(op == "x")
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
        if(input[i] == '+' || input[i] == '-' || input[i] == 'x'){
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
        else if(expression[i] == 'x'){
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

// Returns the result of given arithmetic expression
string ExpressionEval :: evaluate(string input){
    string postfix = infixToPostfix(input);
    string result = postfixEval(postfix);
    return result;
}

// ================================================ Class ExpressionEval: End ========================================================================

// ================================================ Driver Code: main() ==============================================================================

void exponentiation(){
    string num, result;
    long long int exp;
    cin>>num>>exp;
    BigInteger bigInteger;
    result = bigInteger.exponentiation(num, exp);
    // cout<<"Ans: "<<endl;
    cout<<result<<endl;
}

void GCD(){
    string num1, num2, result;
    cin>>num1>>num2;
    BigIntegerUtils utils;
    result = utils.GCD(num1, num2);
    // cout<<"GCD: "<<endl;
    cout<<result<<endl;
}

void factorial(){
    string num, result;
    // cout<<"Enter number:"<<endl;
    cin>>num;
    BigIntegerUtils utils;
    result = utils.factorial(num);
    // cout<<"Factorial: "<<endl;
    cout<<result<<endl;
}

void calculator(){
    string expression, result;
    // cout<<"Enter expression:"<<endl;
    cin.ignore();
    getline(cin, expression);
    ExpressionEval eval;
    result = eval.evaluate(expression);
    cout<<"Ans: "<<endl;
    cout<<result<<endl;
}

int main(){
    cout<<"======================================================================="<<endl;
    cout<<"Available options:"<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<"1. Exponentiation"<<endl;
    cout<<"2. GCD"<<endl;
    cout<<"3. Factorial"<<endl;
    cout<<"4. Calculator"<<endl;
    cout<<"======================================================================="<<endl;
    cout<<endl;

    int option;
    // cout<<"Select an option:";
    cin>>option;

    if(option == 1)
        exponentiation();
    else if(option == 2)
        GCD();
    else if(option == 3)
        factorial();
    else if(option == 4)
        calculator();
    return 0;
}

