#include<iostream>
#include<string>
#include"ArithmeticOperations.h"

using namespace std;
typedef long long ll;

string factorial(string input){

    string op1, op2;
    op1 = input;
    op2 = sub(op1, "1");

    while(op2 != "0"){
        op1 = mul(op1, op2);
        op2 = sub(op2, "1");
    }

    return op1;
}