#include<iostream>
#include"LFUCache.h"

using namespace std;
int main(){
    cout<<"Enter Capacity of cache:";
    int capacity;
    cin>>capacity;

    LFUCache lfu(capacity);

    cout<<"======================================================================="<<endl;
    cout<<"Available options:"<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<"1. Insert into cache"<<endl;
    cout<<"2. Get value of Key from cache"<<endl;
    cout<<"3. Exit"<<endl;
    cout<<"======================================================================="<<endl;
    cout<<endl;

    int option, key, value;
    while(true){
        cout<<"Select option: ";
        cin>>option;
        if(option == 1){
            cout<<"Enter key and value to insert into cache: ";
            cin>>key>>value;
            lfu.set(key, value);
            lfu.printKeys();
            cout<<endl;
        }
        else if(option == 2){
            cout<<"Enter key to retrieve its value: ";
            cin>>key;
            value = lfu.get(key);
            cout<<"Value of key "<<key<<" is: "<<value<<endl;
            lfu.printKeys();
            cout<<endl;

        }
        else if(option == 3){
            break;
        }
        else{
            cout<<"Enter Valid option"<<endl;
        }
        cout<<endl;
    }
}