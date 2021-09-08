#include"ExpressionEval.h"
#include<iostream>
#include<string>

typedef long long ll;

using namespace std;

int main(){

    cout<<"Enter expression: ";

    string input;
    getline(cin, input);

    ExpressionEval expEval;

    string result = expEval.evaluate(input);

    cout<<"Result: "<<endl;
    cout<<result<<endl;

    return 0;
}