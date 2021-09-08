#include<iostream>
#include"LRUCache.h"
#include"LFUCache.h"

using namespace std;

int main(){

    cout<<"======================================================================="<<endl;
    cout<<"Two Types of Caches Available:"<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<"1. LRU Cache"<<endl;
    cout<<"2. LFU Cache"<<endl;
    cout<<"======================================================================="<<endl<<endl;

    cout<<"Choose one of the options to proceed: ";
    int type;
    cin>>type;
    cout<<endl<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;

    if(type != 1 && type != 2){
        cout<<"Invalid option"<<endl;
        return 0;
    }
        
    cout<<"Enter Capacity of cache:";
    int capacity;
    cin>>capacity;

    cout<<endl<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;

    LRUCache lru(capacity);
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
            if(type == 1){
                lru.set(key, value);
            }
            else{
                lfu.set(key, value);
            }
        }
        else if(option == 2){
            cout<<"Enter key to retrieve its value: ";
            cin>>key;
            if(type == 1){
                value = lru.get(key);
            }
            else{
                value = lfu.get(key);
            }
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