#include<iostream>
#include"ArrayRepresentation.h"
#include"ArrayOps.h"
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

void displayMatrix(int **matrix, int NNZ){
    cout<<"========================================="<<endl;
    cout<<"Triplet representation of Sparse matrix: "<<endl;
    cout<<"========================================="<<endl;
    cout<<"Row\t | Col\t | Val"<<endl;
    cout<<"-----------------------------------------"<<endl;
    for(int i=0; i<NNZ+1; i++){
        cout<<matrix[i][0]<<"\t | "<<matrix[i][1]<<"\t | "<<matrix[i][2]<<endl;
    }
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
    
    // Converting conventional matrices into sparse matrices
    ArrayRep m1(rows, columns, NNZ1, matrix1);
    ArrayRep m2(rows, columns, NNZ2, matrix2);
    m1.toSparse();
    m2.toSparse();
    
    ArrayOps ops;
    int **result = ops.addition(m1.sparse, m2.sparse);
    cout<<"Addition of two matrices:"<<endl;
    displayMatrix(result, result[0][2]);
}

void multiplication(){
    int rows1, columns1, rows2, columns2;
    int NNZ1=0, NNZ2=0;

    cout<<"Enter rows and columns of 1st matrix:";
    cin>>rows1>>columns1;

    cout<<endl<<"Enter First matrix values:"<<endl;

    int **matrix1 = new int*[rows1];
    readMatrix(rows1, columns1, NNZ1, matrix1);

    cout<<"Enter rows and columns of 1st matrix:";
    cin>>rows2>>columns2;

    cout<<endl<<"Enter Second matrix values:"<<endl;

    int **matrix2 = new int*[rows2];
    readMatrix(rows2, columns2, NNZ2, matrix2);

    // Converting conventional matrices into sparse matrices
    ArrayRep m1(rows1, columns2, NNZ1, matrix1);
    ArrayRep m2(rows2, columns2, NNZ2, matrix2);
    m1.toSparse();
    m2.toSparse();
}

void transpose(){
    int rows, columns;
    int NNZ=0;

    cout<<"Enter no.of rows and columns:";
    cin>>rows>>columns;

    cout<<endl<<"Enter matrix values:"<<endl;

    int **matrix = new int*[rows];
    readMatrix(rows, columns, NNZ, matrix);

    ArrayRep m1(rows, columns, NNZ, matrix);
    m1.toSparse();
    m1.display();
    ArrayOps op;
    int **result = op.transpose(m1.sparse, m1.colCount);
    cout<<"Transpose of matrix:"<<endl;
    displayMatrix(result, NNZ);
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