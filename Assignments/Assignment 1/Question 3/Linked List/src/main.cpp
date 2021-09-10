#include<iostream>
#include"LLOps.h"
using namespace std;

void readMatrix(int rows, int columns, int &NNZ, int **matrix){
    for(int i=0; i<rows; i++){
        matrix[i] = new int[columns];
        for(int j=0; j<columns; j++){
            cin>>matrix[i][j];
            if(matrix[i][j] != 0)
                NNZ++;
        }
    }
}

void displayMatrix(Node *head){
    Node *temp = head;
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

void addition(){
    int rows, columns;
    int NNZ1=0, NNZ2=0;

    cout<<"Enter no.of rows and columns:";
    cin>>rows>>columns;

    cout<<endl<<"Enter First matrix values:"<<endl;

    int **matrix1 = new int*[rows];
    readMatrix(rows, columns, NNZ1, matrix1);

    cout<<endl<<"Enter Second matrix values:"<<endl;

    int **matrix2 = new int*[rows];
    readMatrix(rows, columns, NNZ2, matrix2);
    
    LinkedList m1(rows, columns, NNZ1, matrix1);
    LinkedList m2(rows, columns, NNZ2, matrix2);
    
    m1.toSparse();
    m2.toSparse();

    LLOps ops;
    Node *result = ops.addition(m1, m2);

    cout<<"Addition of two matrices:"<<endl;

    displayMatrix(result);

}

void multiplication(){
    int rows1, columns1, rows2, columns2;
    int NNZ1=0, NNZ2=0;

    cout<<"Enter rows and columns of 1st matrix:";
    cin>>rows1>>columns1;

    cout<<endl<<"Enter First matrix values:"<<endl;

    int **matrix1 = new int*[rows1];
    readMatrix(rows1, columns1, NNZ1, matrix1);

    cout<<"Enter rows and columns of 2nd matrix:";
    cin>>rows2>>columns2;

    cout<<endl<<"Enter Second matrix values:"<<endl;

    int **matrix2 = new int*[rows2];
    readMatrix(rows2, columns2, NNZ2, matrix2);
 
}

void transpose(){
    int rows, columns;
    int NNZ=0;

    cout<<"Enter no.of rows and columns:";
    cin>>rows>>columns;

    cout<<endl<<"Enter matrix values:"<<endl;

    int **matrix = new int*[rows];
    readMatrix(rows, columns, NNZ, matrix);

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
        addition();
    }
    else if(option == 2){
        multiplication();
    }
    else if(option == 3){
        transpose();
    }
    else{
        cout<<"Enter Valid option"<<endl;
    }
    cout<<endl;
   
    return 0;
}





// if(m1[i][1] == m2T[j][1]){
//                 // cout<<i<<" "<<j<<endl;
//                 int temp=1;
//                 int flag=1;
//                 while(temp < k){
//                     // // cout<<"Enterd: "<<temp<<endl;
//                     // if(result[temp][0] > m1[i][0] || ((result[temp][0] == m1[i][0]) && (result[temp][1] > m2T[j][0]))){
//                     //     cout<<"temp "<<temp<<" "<<m2T[j][0]<<endl;         
//                     //     break;
//                     // }
//                     if((result[temp][0] == m1[i][0]) && (result[temp][1] == m2T[j][0])){
//                         // cout<<"Already existing"<<endl;
//                         result[temp][2] += (m1[i][2] * m2T[j][2]);
//                         flag=0;
//                         break;
//                     }
//                     displayMatrix1(result, k-1);
//                     if((result[temp][0] == m1[i][0]) && result[temp][1] > m2T[j][0]){
//                         cout<<"Break at"<<temp<<m2T[j][0]<<endl;
//                         break;
//                     }
//                     temp++;
//                 }
//                 if(flag == 1){
//                     // cout<<"Nope"<<endl;
//                     result[k] = new int[3];
//                     result[k][0] = m1[i][0];
//                     result[k][1] = m2T[j][0];
//                     result[k][2] = m1[i][2] * m2T[j][2];
//                     int *t = result[temp];
//                     result[temp] = result[k];
//                     result[k] = t;
//                     k++;    
//                 }
         