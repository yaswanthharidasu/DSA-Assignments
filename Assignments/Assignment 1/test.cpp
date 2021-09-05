#include<iostream>
#include<string>
#include"/home/yaswanth/M.Tech/1-1/DSA/Assignments/Assignment 1/Question 1/MyStack.h"

using namespace std;
typedef long long ll;

int main(){


    #ifndef ONLINE_JUDGE
        freopen("/home/yaswanth/M.Tech/1-1/DSA/Assignments/Assignment 1/input.txt", "r", stdin);
        freopen("/home/yaswanth/M.Tech/1-1/DSA/Assignments/Assignment 1/output.txt", "w", stdout);
    #endif

    MyStack<string> st;
    string str = "10", jtr = "20";
    st.push(str);
    st.push(jtr);
    st.push("30");
    st.push("40");

    // cout<<add(op2, op1);
    // cout<<mul(op2,op1);
    st.printStack();

}
