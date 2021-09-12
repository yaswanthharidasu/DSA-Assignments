#include<iostream>
using namespace std;

// ================================================ Class Node: Begin ================================================================================

template <class T>
class Node{
    public:
    int row, column;
    T value;
    Node *next;
    Node(int row, int column, T value);
};

template<class T>
Node<T> :: Node(int row, int column, T value){
    this->row = row;
    this->column = column;
    this->value = value;
    this->next = NULL;
}

// ================================================ Class Node: End ==================================================================================

// ================================================ Class LinkedList: Begin ==========================================================================

template<class T>
class LinkedList{
    public:
    Node<T> *head;
    T **matrix;
    // Constructor
    LinkedList(int rows, int columns, int NNZ, T **matrix);
    // Converts into sparse matrix
    void toSparse();
};

template<class T>
LinkedList<T> :: LinkedList(int rows, int columns, int NNZ, T **matrix){
    this->matrix = matrix;
    head = new Node<T>(rows, columns, NNZ);
}

template<class T>
void LinkedList<T> :: toSparse(){
    int rows = head->row, columns = head->column;
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(matrix[i][j] == 0)
                continue;
            Node<T> *newNode = new Node<T>(i, j, matrix[i][j]);
            Node<T> *temp = head;
            while(temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    }

    Node<T> *temp = head;
}

// ================================================ Class LinkedList: End ============================================================================

// ================================================ Class LLOps: Begin ===============================================================================

template <class T>
class LLOps{
    public: 
    Node<T>* addition(LinkedList<T> m1, LinkedList<T> m2);

    Node<T>* multiplication(LinkedList<T> m1, LinkedList<T> m2);

    Node<T>* transpose(LinkedList<T> m);

    void findMid(Node<T> *head, Node<T> **left, Node<T> **right);
    
    void mergeSort(Node<T> **start);
    
    Node<T>* merge(Node<T> *left, Node<T> *right);

    Node<T>* alreadyPresent(Node<T> *head, int row, int column);
};

template <class T>
void LLOps<T> :: findMid(Node<T> *head, Node<T> **left, Node<T> **right){
    // Hare and tortoise algorithm to find mid point of Linked list
    Node<T> *tortoise = head, *hare = head->next;
    while(hare != NULL){
        hare = hare->next;
        if(hare != NULL){
            hare = hare->next;
            tortoise = tortoise->next;
        }
    }
    *left = head;
    *right = tortoise->next;
    // After assigning midpoint to right we need to break the list
    tortoise->next = NULL;
}

template <class T>
void LLOps<T> :: mergeSort(Node<T> **start){
    Node<T> *head = *start;
    if(head == NULL || head->next == NULL)
        return ;

    Node<T> *left, *right;
    // Finding midpoint of the linked list
    findMid(head, &left, &right);
    // Sort the left and right LL
    mergeSort(&left);
    mergeSort(&right);
    // Merge left and right LL
    *start = merge(left, right);
}

template <class T>
Node<T>* LLOps<T> :: merge(Node<T> *left, Node<T> *right){
    if(left == NULL)
        return right;
    if(right == NULL)
        return left;
    Node<T> *head = NULL;
    if((left->row < right->row) || (left->row == right->row && left->column < right->column)){
        head = left;
        head->next = merge(left->next, right);
    }
    else{
        head = right;
        head->next = merge(left, right->next);
    }
    return head;
}

template <class T>
Node<T>* LLOps<T> :: alreadyPresent(Node<T> *head, int row, int column){
    if(head == NULL)
        return NULL;
    while(head != NULL){
        if(head->row == row && head->column == column){
            return head;
        }
        head = head->next;
    }
    return head;
}

template <class T>
Node<T>* LLOps<T> :: addition(LinkedList<T> mat1, LinkedList<T> mat2){
    Node<T> *m1 = mat1.head, *m2 = mat2.head;
    if(m1->row != m2->row || m1->column != m2->column)
        return NULL;

    Node<T> *result = new Node<T>(m1->row, m1->column, 0); 

    int NNZ = 0;

    Node<T> *temp = result;

    m1 = m1->next, m2 = m2->next;

    while(m1 != NULL && m2 != NULL){
        if(m1->row == m2->row && m1->column == m2->column){
            Node<T> *newNode = new Node<T>(m1->row, m1->column, m1->value+m2->value);
            temp->next = newNode;
            m1 = m1->next, m2 = m2->next;
        }
        else if((m1->row > m2->row) || (m1->row == m2->row && m1->column > m2->column)){
            temp->next = m2;
            m2 = m2->next;
        }
        else{
            temp->next = m1;
            m1 = m1->next;
        }
        temp = temp->next;
        NNZ++;
    }
    while(m1 != NULL){
        temp->next = m1;
        temp = temp->next;
        m1 = m1->next;
        NNZ++;
    }
    while(m2 != NULL){
        temp->next = m2;
        temp = temp->next;
        m2 = m2->next; 
        NNZ++; 
    }
    result->value = NNZ;
    return result;
}

template <class T>
Node<T>* LLOps<T> :: transpose(LinkedList<T> mat){
    Node<T> *m = mat.head;
    Node<T> *result = new Node<T>(m->column, m->row, m->value);
    Node<T> *tempM = m->next, *tempResult = result;
    while(tempM != NULL){
        Node<T> *newNode = new Node<T>(tempM->column, tempM->row, tempM->value);
        tempResult->next = newNode;
        tempM = tempM->next;
        tempResult = tempResult->next;
    }
    // First node consists of no.of rows, columns, and NNZ values. Hence sort from the next element
    mergeSort(&result->next);
    return result;
}

template <class T>
Node<T>* LLOps<T> :: multiplication(LinkedList<T> mat1, LinkedList<T> mat2){
    Node<T> *m1 = mat1.head;
    Node<T> *m2 = mat2.head;
    if(m1->column != m2->row){
        cout<<"Multiplication not possible"<<endl;
        return NULL;
    }       
    Node<T> *result = new Node<T>(m1->row, m2->column, 0);
    Node<T> *tempOne = m1->next, *tempTwo = m2->next, *tempResult = result;
    int NNZ = 0;    
    while(tempOne != NULL){
        // Intializing tempTwo to beginning for every iteration
        tempTwo = m2->next;
        while(tempTwo != NULL){
            if(tempOne->column == tempTwo->row){
                Node<T> *temp;
                if((temp = alreadyPresent(result->next, tempOne->row, tempTwo->column)) != NULL){
                    temp->value += (tempOne->value * tempTwo->value);
                }
                else{
                    Node<T> *newNode = new Node<T>(tempOne->row, tempTwo->column, (tempOne->value * tempTwo->value));
                    tempResult->next = newNode;
                    tempResult = tempResult->next;
                    NNZ += 1;
                }
            }
            tempTwo = tempTwo->next;
        }
        tempOne = tempOne->next;
    }
    result->value = NNZ;
    mergeSort(&result->next);
    return result;
}

// ================================================ Class LLOps: End =================================================================================

/// ================================================ Driver Code: main() =============================================================================

template<class T>
void readMatrix(int rows, int columns, int &NNZ, T **matrix){
    for(int i=0; i<rows; i++){
        matrix[i] = new T[columns];
        for(int j=0; j<columns; j++){
            cin>>matrix[i][j];
            if(matrix[i][j] != 0)
                NNZ++;
        }
    }
}

template<class T>
void displayMatrix(Node<T> *head){
    Node<T> *temp = head;
    cout<<"========================================="<<endl;
    cout<<"LL representation of Sparse matrix: "<<endl;
    cout<<"========================================="<<endl;
    cout<<"Row\t | Col\t | Val"<<endl;
    cout<<"-----------------------------------------"<<endl;
    while(temp != NULL){
        cout<<temp->row<<"\t| "<<temp->column<<"\t| "<<temp->value<<endl;
        temp = temp->next;
    }
    cout<<"-----------------------------------------"<<endl;
}

template<class T>
void addition(){
    int rows, columns;
    int NNZ1=0, NNZ2=0;

    cout<<"Enter no.of rows and columns:";
    cin>>rows>>columns;

    cout<<endl<<"Enter First matrix values:"<<endl;

    T **matrix1 = new T*[rows];
    readMatrix(rows, columns, NNZ1, matrix1);

    cout<<endl<<"Enter Second matrix values:"<<endl;

    T **matrix2 = new T*[rows];
    readMatrix(rows, columns, NNZ2, matrix2);
    
    LinkedList<T> m1(rows, columns, NNZ1, matrix1);
    LinkedList<T> m2(rows, columns, NNZ2, matrix2);
    
    m1.toSparse();
    m2.toSparse();

    LLOps<T> ops;
    Node<T> *result = ops.addition(m1, m2);

    cout<<"Addition of two matrices:"<<endl;

    displayMatrix(result);
}

template<class T>
void multiplication(){
    int rows1, columns1, rows2, columns2;
    int NNZ1=0, NNZ2=0;

    cout<<"Enter rows and columns of 1st matrix:";
    cin>>rows1>>columns1;

    cout<<endl<<"Enter First matrix values:"<<endl;

    T **matrix1 = new T*[rows1];
    readMatrix(rows1, columns1, NNZ1, matrix1);

    cout<<endl<<"Enter rows and columns of 2nd matrix:";
    cin>>rows2>>columns2;

    cout<<endl<<"Enter Second matrix values:"<<endl;

    T **matrix2 = new T*[rows2];
    readMatrix(rows2, columns2, NNZ2, matrix2);

    LinkedList<T> m1(rows1, columns1, NNZ1, matrix1);
    LinkedList<T> m2(rows2, columns2, NNZ2, matrix2);
    m1.toSparse();
    m2.toSparse();

    LLOps<T> ops;
    Node<T> *result = ops.multiplication(m1, m2);
    displayMatrix(result);
}

template <class T>
void transpose(){
    int rows, columns;
    int NNZ=0;

    cout<<"Enter no.of rows and columns:";
    cin>>rows>>columns;

    cout<<endl<<"Enter matrix values:"<<endl;

    T **matrix1 = new T* [rows];
    readMatrix(rows, columns, NNZ, matrix1);

    LinkedList<T> m(rows, columns, NNZ, matrix1);
    m.toSparse();

    LLOps<T> ops;
    Node<T> *result = ops.transpose(m);
    displayMatrix(result);
}

int main(){
    cout<<"======================================================================="<<endl;
    cout<<"Available options:"<<endl;
    cout<<"-----------------------------------------------------------------------"<<endl;
    cout<<"1. Addition"<<endl;
    cout<<"2. Multiplication"<<endl;
    cout<<"3. Transpose"<<endl;
    cout<<"======================================================================="<<endl;
    cout<<endl;


    int option;
    cin>>option;

    if(option == 1){
        addition<double>();
    }
    else if(option == 2){
        multiplication<double>();
    }
    else if(option == 3){
        transpose<double>();
    }
    else{
        cout<<"Enter Valid option"<<endl;
    }
    cout<<endl;
   
    return 0;
}

