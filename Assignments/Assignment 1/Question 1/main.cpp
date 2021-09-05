#include"ExpressionEval.h"
#include<iostream>
#include<string>

typedef long long ll;

using namespace std;

int main(){

    #ifndef ONLINE_JUDGE
        freopen("/home/yaswanth/M.Tech/1-1/DSA/Assignments/Assignment 1/input.txt", "r", stdin);
        freopen("/home/yaswanth/M.Tech/1-1/DSA/Assignments/Assignment 1/output.txt", "w", stdout);
    #endif

    string input;
    getline(cin, input);

    string result = expEval(input);

    cout<<result<<endl;

    return 0;
}