#include<iostream>
#include<string>
// #include"/home/yaswanth/M.Tech/1-1/DSA/Assignments/Assignment 1/Question 1/ExpressionEval.h"
// #include"/home/yaswanth/M.Tech/1-1/DSA/Assignments/Assignment 1/Question 1/Factorial.h"
// #include"/home/yaswanth/M.Tech/1-1/DSA/Assignments/Assignment 1/Question 1/GCD.h"
// #include"/home/yaswanth/M.Tech/1-1/DSA/Assignments/Assignment 1/Question 1/Exponentiation.h"
// #include"/home/yaswanth/M.Tech/1-1/DSA/Assignments/Assignment 1/Question 2/LRUCache.h"
#include"/home/yaswanth/M.Tech/1-1/DSA/Assignments/Assignment 1/Question 2/LFUCache.h"

using namespace std;

typedef long long ll;

int main(){

    #ifndef ONLINE_JUDGE
        freopen("/home/yaswanth/M.Tech/1-1/DSA/Assignments/Assignment 1/input.txt", "r", stdin);
        freopen("/home/yaswanth/M.Tech/1-1/DSA/Assignments/Assignment 1/output.txt", "w", stdout);
    #endif

    // LRUCache<int,int> cache(1);
    // while(true){
    //     int option;
    //     cin>>option;
    //     int k,v;
    //     if(option == -1)
    //         break;

    //     switch (option)
    //     {
    //     case 1:
    //          cin>>k>>v;
    //         cache.set(k, v);
    //         cache.traverseDLL();
    //         break;
        
    //     case 2: 
    //         cin>>k;
    //         cout<<"Value of "<<k<<": "<<cache.get(k)<<endl;
    //         cache.traverseDLL();
    //         break;
    //     }
    // }
    int capacity;           
    cin>>capacity;
    LFUCache<int,int> cache(capacity);
    // cout<<"[";
    // cout<<"null,";
    while(true){
        int option;
        cin>>option;
        int k,v;
        if(option == -1)
            break;

        switch (option)
        {
        case 1:
            cin>>k>>v;
            cache.set(k, v);
            cout<<"inserted: "<<k<<endl;
            cout<<endl;
            // cout<<"null,";
            break;
        
        case 2: 
            cin>>k;
            int val;
            if((val=cache.get(k)) == -1)
                cout<<k<<" not present"<<"-1"<<endl;
                // cout<<"-1,";
            else
                cout<<k<<" present: "<<val<<endl;
                // cout<<val<<",";
            cout<<endl;
            break;
        }
    }

    // cout<<"]";

}
