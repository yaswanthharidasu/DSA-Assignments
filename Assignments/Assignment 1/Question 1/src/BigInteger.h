#include<string>
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
};