#include<iostream>
#include"BigInteger.h"

using namespace std;
typedef long long int ll;

// Performs addition of two integers which are provided as strings
string BigInteger :: add(string op1, string op2){

    string rev1, rev2, result;

    // Make sure op1 is greater than op 2
    if(op2.size() > op1.size()){
        string temp = op1;
        op1 = op2;
        op2 = temp;
    }

    // As integers can be of varying lengths, reverse the strings so that we correctly add the llegers from the unit's place
    rev1 = string(op1.rbegin(), op1.rend());
    rev2 = string(op2.rbegin(), op2.rend());

    // Initially the carry is set to zero
    ll carry = 0;
    ll i = 0;

    // Adding the digits of two strings along with the carry and the carry obtained is passed to next digits
    while(i < rev2.length()){
        ll sum = (rev1[i]-'0') + (rev2[i]-'0') + carry;
        carry = sum/10;
        result += (sum%10 + '0');
        i++;
    }
    // There can be some characters left in the string 1 as it is greater number
    while(i < rev1.length()){
        ll sum = (rev1[i]-'0') + carry;
        carry = sum/10;
        result += (sum%10 + '0');
        i++;    
    }
    // If any carry is left then append it to the result.
    if(carry != 0){
        result += (carry + '0');
    }

    // Reverse the result
    result = string(result.rbegin(), result.rend());

    return result;
}

// Performs subtraction of two integers which are provided as strings
string BigInteger :: subtract(string op1, string op2){

    string rev1, rev2, result;

    rev1 = string(op1.rbegin(), op1.rend());
    rev2 = string(op2.rbegin(), op2.rend());

    ll borrow = 0;

    ll i=0, n1, n2;
    while(i < op2.length()){
        n1 = rev1[i]-'0'-borrow;
        n2 = rev2[i]-'0';

        if(n1 >= n2){
            result += ((n1-n2)+'0');
            borrow = 0;
        }
        else{
            n1 += 10;
            result += ((n1-n2)+'0');
            borrow = 1;
        }
        i++;
    }

    // Process the greater number if there any digits left
    while(i < op1.length()){
        n1 = rev1[i]-'0'-borrow;
        if(n1 >= 0){
            result += (n1+'0');
            borrow = 0;
        }
        else{
            n1 += 10;
            result += (n1+'0');
            borrow = 1;
        }
        i++;
    }

    // Remove any leading zeroes
    while(result.length() > 1 && result[result.length()-1] == '0')
        result.pop_back();

    result = string(result.rbegin(), result.rend());
    return result;
}

// Performs multiplication of two integers which are provided as strings
string BigInteger :: multiply(string op1, string op2){
    // If any of the operand is zero then simply return zero
    if(op1 == "0" || op2 == "0")
        return "0";
    
    // Make sure op1 is greater than op 2
    if(op2.size() > op1.size()){
        string temp = op1;
        op1 = op2;
        op2 = temp;
    }
    // The result can atmost of size op1.length()+op2.length()
    // Hence create a string 'result' of size op1.length()+op2.length()
    string result(op1.length()+op2.length(), 0);

    for(ll i=op2.length()-1; i>=0; i--){
        for(ll j=op1.length()-1; j>=0; j--){
            int num1 = op1[j]-'0', num2 = op2[i]-'0';
            int ans = num1 * num2;
            // Adding result[i+j+1] if there exists carry
            ans += result[i+j+1];
            // Ans can be atmost of two digits. Hence, LSD is the result and MSD is the carry
            // Storing the carry for the next digit
            result[i+j] += ans/10;
            // Storing the value
            result[i+j+1] = ans%10;
        }
    }

    // Now convert the result into string by adding '0' to each character of string
    for(ll i=0; i<result.length(); i++){
        result[i] += '0';
    }

    // Sometimes the result can be of size op1.length()+op2.length()-1
    // The first element of result will be zero in those cases. Thus return the result without the leading zero
    return result[0] == '0' ? result.substr(1) : result;
}

// Performs exponentiation
string BigInteger :: exponentiation(string base, ll exp){
    string result = "1";
    while(exp > 0){
        if(exp & 1){
            result = multiply(result, base);
        }
        base = multiply(base, base);
        // cout<<base<<endl;
        exp = exp>>1;
    }
    return result;
}

// Performs num % mod
string BigInteger :: modulo(string num, string mod){
// Performing modulo by doubling the mod value until it is smaller than num
// Whenever the max value of mod is reached then subtract it from the num 
// Then again repeat the process.
// The doubled values are stored in the form of Linked list inorder to avoid calculating again
    Node *head = new Node(mod);
    string currentMod = mod;
    while(num.length() > currentMod.length() || (num.length() == currentMod.length() && num.compare(currentMod) > 0)){
        Node *twice = new Node(multiply(head->current, "2"));
        if(twice->current.length() > num.length() || (twice->current.length() == num.length() && num.compare(twice->current) < 0))
            break;
        currentMod = twice->current;
        twice->next = head;
        head = twice;
    }
    // After reaching the max value of mod then perfoming the subtraction
    while(head!=NULL){
        if(head->current.length() > num.length() || (head->current.length() == num.length() && head->current.compare(num) > 0))
            head = head->next;
        else{
            num = subtract(num, head->current);
        }
    }
    return num;
}