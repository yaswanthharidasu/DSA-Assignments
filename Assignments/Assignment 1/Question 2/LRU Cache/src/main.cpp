#include<iostream>
#include"LRUCache.h"

using namespace std;
int main(){
    cout<<"Enter Capacity of cache:";
    int capacity;
    cin>>capacity;

    LRUCache lru(capacity);

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
            lru.set(key, value);
        }
        else if(option == 2){
            cout<<"Enter key to retrieve its value: ";
            cin>>key;
            value = lru.get(key);
            cout<<"Value of key "<<key<<" is: "<<value<<endl;
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