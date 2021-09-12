#ifndef __BIGINTEGER__
#define __BIGINTEGER__

#include<string>
#include"Node.h"
using namespace std;

class BigInteger{

    public:
    // Performs addition of two integers which are provided as strings
    string add(string op1, string op2);

    // Performs subtraction of two integers which are provided as strings
    string subtract(string op1, string op2);

    // Performs multiplication of two integers which are provided as strings
    string multiply(string op1, string op2);

    // Performs exponentiation
    string exponentiation(string base, long long int exp);

    // Performs num % mod
    string modulo(string num, string mod);
};

#endif