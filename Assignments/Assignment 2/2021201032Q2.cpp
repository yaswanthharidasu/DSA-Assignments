#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#define TABLE_SIZE 5099
#define poly 63

using namespace std;

template<class K, class V>
class Node{
    public:
    K key;
    V value;
    Node<K,V> *next;
    Node<K,V> ();
    Node<K,V> (K key, V value);
};

template<class K, class V>
Node<K,V> :: Node(){
    next = NULL;
}

template<class K, class V>
Node<K,V> :: Node(K key, V value){
    this->key = key;
    this->value = value;
    next = NULL;
}

// =========================================== class: un_map ===================================================

template<class K, class V>
class un_map{
    public:
    Node<K,V> *table[TABLE_SIZE];
    // Constructor
    un_map<K,V> ();
    int computeHashValue(K key);
    void insert(K key, V val);
    void erase(K key);
    bool find(K key);
    V operator [](K key);
};

template<class K, class V>
un_map<K,V> :: un_map(){
    // table = new Node<K,V>* [TABLE_SIZE];
    for(int i=0; i<TABLE_SIZE; i++)
        table[i] = NULL;
}

template<class K, class V>
int un_map<K,V> :: computeHashValue(K key) {
    // string s = to_string(key);
    ostringstream ost;
    ost << key;

    string s = ost.str();

    int hashValue = 0;
    int x = 1;
    for (char ch : s) {
        hashValue = (hashValue + (ch - '0' + 1) * x) % TABLE_SIZE;
        x = (x * poly) % TABLE_SIZE;
    }
    return hashValue;
}

template<class K, class V>
void un_map<K,V> :: insert(K key, V val){
    int hashValue = computeHashValue(key);

    Node<K,V> *head = table[hashValue];
    Node<K,V> *newNode = new Node<K,V>(key, val);

    if(head == NULL){
        cout<<"Inserted first at that location"<<endl;
        table[hashValue] = newNode;
    }
    else{
        Node<K,V> *prev = head;
        while(head != NULL){
            // If already present
            if(head->key == key){
                head->value = val;
                cout<<"Updated"<<endl;
                return ;
            }
            prev = head;
            head = head->next;
        }
        prev->next = newNode;
    }
}

template<class K, class V>
void un_map<K,V> :: erase(K key){
    int hashValue = computeHashValue(key);
    Node<K,V> *head = table[hashValue];
    // Key not present
    if(head == NULL){
        cout<<"Key not present"<<endl;
        return ;
    }
    // First key is the required key
    if(head->key == key){
        table[hashValue] = NULL;
        return ;
    }
    Node<K,V> *prev = head;
    while(head != NULL){
        // Element found
        if(head->key == key){
            prev->next = NULL;
        }
        prev = head;
        head = head->next;
    }
}

template<class K, class V>
bool un_map<K,V> :: find(K key){
    int hashValue = computeHashValue(key);
    Node<K,V> *head = table[hashValue];
    while(head != NULL){
        if(head->key == key)
            return true;
        head = head->next;
    }
    return false;
}

template<class K, class V>
V un_map<K,V> :: operator[](K key){
    int hashValue = computeHashValue(key);

    Node<K,V> *head = table[hashValue];
    // No element present at that location: Insert default value
    if(head == NULL){
        cout<<"Not present"<<endl;
        static V defaultVal;
        Node<K,V> *newNode = new Node<K,V>(key, defaultVal);
        table[hashValue] = newNode;
        return defaultVal;
    }

    Node<K,V> *prev = head;
    while(head != NULL){
        if(head->key == key)
            return head->value;
        prev = head;
        head = head->next;
    }

    // Key not present in the links
    cout<<"Not Present"<<endl;
    static V defaultVal;
    Node<K,V> *newNode = new Node<K,V>(key, defaultVal);
    prev->next = newNode;
    return defaultVal;
}

vector<int> countDisinctElements(int k, vector<int> arr){
    vector<int> result;
    if(arr.size() < k)
        return result;

    int distinctElements = 0;
    un_map<int,int> um;
    
    for(int i=0; i<k; i++){
        if(um[arr[i]] == 0){
            distinctElements += 1;
        }
        int val = um[arr[i]];
        um.insert(arr[i], val+1);
    }

    result.push_back(distinctElements);

    for(int i=k; i<arr.size(); i++){
        // Removing the element of the previous window
        if(um[arr[i-k]] == 1)
            distinctElements -= 1;

        int val = um[arr[i-k]];
        um.insert(arr[i-k], val-1);

        // Adding new element into the window
        if(um[arr[i]] == 0)
            distinctElements += 1;

        val = um[arr[i]];
        um.insert(arr[i], val+1);
        result.push_back(distinctElements);
    }
    return result;
}

int main(){
    un_map<string,string> um;

    int option;
    string key, val;

    cout << "================================================================" << endl;
    cout << "Available options:" << endl;
    cout << "1.Insert" << endl;
    cout << "2.Erase" << endl;
    cout << "3.Find" << endl;
    cout << "4.Map[Key]" << endl;
    cout<<"5.Distinct elements"<<endl;
    cout << "================================================================" << endl;
    
    while (true) {
        cout << "Enter option: ";
        // cin.ignore();
        cin >> option;
        if (option == 1) {
            cin >> key>>val;
            um.insert(key, val);
        } else if (option == 2) {
            cin >> key;
        } else if (option == 3) {
            cin >> key;
            cout<<um.find(key)<<endl;
        } else if (option == 4) {
            cin >> key;
            cout<<um[key]<<endl;
        }
        else if(option == 5){
            int n,k;
            cin>>n>>k;
            vector<int> arr(n);
            for(int i=0; i<n; i++){
                cin>>arr[i];
            }
            vector<int> result = countDisinctElements(k, arr);
            for(int i=0; i<result.size(); i++)
                cout<<result[i]<<" ";
            cout<<endl;
        } 
        else if(option == 6){
            cout<<"Exit"<<endl;
            break;
        }
        cout << endl;
    }
    return 0;
}