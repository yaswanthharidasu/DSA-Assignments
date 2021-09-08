#include<string>
#include"ArithmeticOperations.h"
using namespace std;

string exponentiation(string base, long long int exp){
    string result = "1";
    while(exp > 0){
        if(exp & 1){
            result = mul(result, base);
        }
        base = mul(base, base);
        cout<<base<<endl;
        exp = exp>>1;
    }
    return result;
}