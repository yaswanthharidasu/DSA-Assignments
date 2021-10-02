#include<iostream>
using namespace std;

template<class T> 
class Deque{
    T *arr;
    int MAX_SIZE = 10;
    int pFront, pRear, pSize;

    public:
    // Constructor
    Deque();

    Deque(int n, T x);

    // Utility method: Return if Deque is full
    bool isFull();
    // Utility method: Return if Deque is empty
    bool empty();

    void push_back(T x);

    void pop_back();

    void push_front(T x);

    void pop_front();

    T front();

    T back();
    
    int size();

    void clear();

    T &operator [](int i);

    void print();

};

template<class T>
Deque<T> :: Deque(){
    arr = new T[MAX_SIZE];
    pFront = pRear = -1;
    pSize = 0;
}

template<class T>
Deque<T> :: Deque(int n, T x){
    arr = new T[MAX_SIZE];
    pFront = pRear = -1;
    pSize = 0;

    // Insert element x for 'n' times
    for(int i=0; i<n; i++){
        push_back(x);
    }
}

template<class T>
bool Deque<T> :: isFull(){
    if(pSize == MAX_SIZE)
        return true;
    else
        return false;
}

template<class T>
bool Deque<T> :: empty(){
    if(pSize == 0)
        return true;
    else
        return false;
}

template<class T>
void Deque<T> :: push_back(T x){
    // TODO: Size overflow
    if(isFull()){
        cout<<"FULL"<<endl;
        return ;
    }

    // Deque is Empty
    if(pFront == -1 && pRear == -1){
        pFront += 1;
        pRear += 1;
        arr[pRear] = x;
        // cout<<"1st element inserted: "<<arr[pRear]<<endl;
    }
    else{
        pRear = (pRear+1)%MAX_SIZE;
        arr[pRear] = x;
        // cout<<"Inserted: "<<arr[pRear]<<endl;
    }
    // Increasing the size by 1 as an element is inserted
    pSize += 1;
}

template<class T>
void Deque<T> :: pop_back(){
    // TODO:
    if(empty()){
        cout<<"Deque is empty"<<endl;
        return ;
    }
    // Only one element in deque
    if(pFront == pRear){
        pFront = -1;
        pRear = -1;
    }
    else{
        pRear = (pRear - 1)%MAX_SIZE;
    }
    // Decreasing the size by 1 as an element is deleted
    pSize -= 1;
}

template<class T>
void Deque<T> :: push_front(T x){
    // TODO: 
    if(isFull()){
        cout<<"Deque full"<<endl;
        return ;
    }
    // Deque is Empty
    if(pFront == -1 && pRear == -1){
        pFront += 1;
        pRear += 1;
        arr[pFront] = x;
        // cout<<"1st element inserted: "<<arr[pRear]<<endl;
    }
    else{
        pFront = (pFront-1)%MAX_SIZE;
        arr[pFront] = x;
        // cout<<"Inserted: "<<arr[pFront]<<endl;
    }
    // Increasing the size by 1 as an element is inserted
    pSize += 1;
}

template<class T>
void Deque<T> :: pop_front(){
    // Empty
    if(empty()){
        cout<<"Deque is empty"<<endl;
        return ;
    }
    // Only one element in deque
    if(pFront == pRear){
        pFront = -1;
        pRear = -1;
    }
    else{
        pFront = (pFront + 1)%MAX_SIZE;
    }
    // Decreasing the size by 1 as an element is deleted
    pSize -= 1;
}

template<class T>
T Deque<T> :: front(){
    // Deque is empty
    if(empty()){
        return -1;
    }
    return arr[pFront];
}

template<class T>
T Deque<T> :: back(){
    // Deque is empty
    if(empty()){
        return -1;
    }
    return arr[pRear];
}

template<class T>
int Deque<T> :: size(){
    return pSize;
}


template<class T>
T& Deque<T> :: operator[](int i){
    if(i>=pSize){
        cout<<"Out of Bounds index"<<endl;
        // exit(0);
        // Returning last element
        return arr[pSize-1];
    }
    return arr[pFront+i];
}

template<class T>
void Deque<T> :: clear(){
    // TODO: 
    // Already empty
    if(empty()){
        return ;
    }
    pFront = pRear = -1;
    pSize = 0;
}


template<class T>
void Deque<T> :: print(){
    if(empty()){
        cout<<"Deque is empty"<<endl;
        return ;
    }

    int i = pFront;
    while(i != pRear){
        cout<<arr[i]<<" ";
        i = (i+1)%MAX_SIZE;
    }
    if(i == pRear){
        cout<<arr[i]<<endl;
    }
    cout<<endl;
}


// ================================================= Driver code: main() ============================================================================

int main(){
    Deque<int> dq;
    cout<<"============== Available Options ================"<<endl;
    cout<<"1.push_back"<<endl;
    cout<<"2.pop_back"<<endl;
    cout<<"3.push_front"<<endl;
    cout<<"4.pop_front"<<endl;
    cout<<"5.front"<<endl;
    cout<<"6.back"<<endl;
    cout<<"7.empty"<<endl;
    cout<<"8.size"<<endl;
    cout<<"9.clear"<<endl;
    cout<<"10.Index"<<endl;
    cout<<"10.exit"<<endl;
    cout<<"=================================================="<<endl;
    int option;
    int x; 
    while(true){
        cout<<"Select option:"<<endl;
        cin>>option;
        if(option == 1){
            cin>>x;
            dq.push_back(x);
            cout<<"Elements:";
            dq.print();  
        }
        else if(option == 2){
            dq.pop_back();
            cout<<"Elements:";
            dq.print();  
        }
        else if(option == 3){
            cin>>x;
            dq.push_front(x);
            cout<<"Elements:";
            dq.print();  
        }
        else if(option == 4){
            dq.pop_front();
            cout<<"Elements:";
            dq.print();  
        }
        else if(option == 5){
            cout<<dq.front()<<endl;
        }
        else if(option == 6){
            cout<<dq.back()<<endl;
        }
        else if(option == 7){
            cout<<dq.empty()<<endl;
        }
        else if(option == 8){
            cout<<dq.size()<<endl;
        }
        else if(option == 9){
            dq.clear();
            cout<<"Elements:";
            dq.print();  
        }
        else if(option == 10){
            cin>>x;
            cout<<dq[x]<<endl;
        }
        else if(option == 11){
            break;
        } 
    }
    return 0;
}