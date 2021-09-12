#include"ExpressionEval.h"
#include"BigIntegerUtils.h"
#include<iostream>
#include<chrono>
typedef long long ll;

using namespace std;
using namespace std :: chrono;

void exponentiation(){
    string num, result;
    long long int exp;
    cout<<"Enter number and exponent:"<<endl;
    cin.ignore();
    getline(cin, num);  
    cin>>exp;
    BigInteger bigInteger;
    result = bigInteger.exponentiation(num, exp);
    cout<<"Ans: "<<endl;
    cout<<result<<endl;
}
void GCD(){
    string num1, num2, result;
    cout<<"Enter two numbers:"<<endl;
    cin.ignore();
    getline(cin, num1);
    getline(cin, num2);
    BigIntegerUtils utils;
    result = utils.GCD(num1, num2);
    cout<<"GCD: "<<endl;
    cout<<result<<endl;
}
void factorial(){
    string num, result;
    cout<<"Enter number:"<<endl;
    cin.ignore();
    getline(cin, num);
    BigIntegerUtils utils;
    result = utils.factorial(num);
    cout<<"Factorial: "<<endl;
    cout<<result<<endl;
}
void calculator(){
    string expression, result;
    cout<<"Enter expression:"<<endl;
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
    cout<<"Select an option:";
    cin>>option;

    if(option == 1)
        exponentiation();
    else if(option == 2)
        GCD();
    else if(option == 3)
        factorial();
    else if(option == 4)
        calculator();
    else
        cout<<"Select valid option"<<endl;
    return 0;
}