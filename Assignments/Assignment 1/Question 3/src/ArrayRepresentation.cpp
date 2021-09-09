#include"ArrayRepresentation.h"
#include<iostream>
using namespace std;

ArrayRep :: ArrayRep(int rows, int columns, int NNZ, int **matrix){

    this->matrix = matrix;  
    // Creating sparse matrix 
    sparse = new int* [NNZ+1];
    for(int i=0; i<NNZ+1; i++)
        sparse[i] = new int[3];

    // First row of sparse stores #rows, #cols, #NNZ vals
    sparse[0][0] = rows;
    sparse[0][1] = columns;
    sparse[0][2] = NNZ;
    
    // Creating an array of size "columns" to stores no.of elements in each column
    colCount = new int[columns]{0};
}

void ArrayRep :: toSparse(){
    // index of sparse matrix
    int k = 1;
    int rows = sparse[0][0], columns = sparse[0][1];
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(matrix[i][j] == 0)
                continue;
            sparse[k][0] = i;
            sparse[k][1] = j;
            sparse[k][2] = matrix[i][j];
            colCount[j]++;
            k++;
        }
    }
}

void ArrayRep :: display(){
    cout<<"========================================="<<endl;
    cout<<"Triplet representation of Sparse matrix: "<<endl;
    cout<<"========================================="<<endl;
    cout<<"Row\t | Col\t | Val"<<endl;
    cout<<"-----------------------------------------"<<endl;
    for(int i=1; i<=sparse[0][2]; i++){
        cout<<sparse[i][0]<<"\t | "<<sparse[i][1]<<"\t | "<<sparse[i][2]<<endl;
    }
}

