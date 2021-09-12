#include<iostream>
#include"BigIntegerUtils.h"

using namespace std;

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