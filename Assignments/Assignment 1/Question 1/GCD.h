#include<iostream>
#include<string>
#include"ArithmeticOperations.h"

string GCD(string num1, string num2){

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
        // // num1 == num2
        // if(num1.compare(num2) == 0){
        //     gcd = num1;
        //     break;
        // }
        // num1 > num2
        // If num1.length() > num2.length() then num1 > num2
        // If num1.length() == num2.length() then there may be cases where num1 > num2 so compare method is used
        if((num1.length() > num2.length()) || (num1.length() == num2.length() && num1.compare(num2) > 0)){
            num1 = sub(num1, num2);
        }
        // num1 < num2
        else{
            num2 = sub(num2, num1); 
        }
    }
    return gcd;
}