#include"ArrayRepresentation.h"
#include<iostream>
using namespace std;

template<class T>
ArrayRep<T> :: ArrayRep(int rows, int columns, int NNZ, T **matrix){
    // cout<<"NNZ: "<<NNZ<<endl;
    this->matrix = matrix;  
    // Creating sparse matrix 
    sparse = new T* [NNZ+1];
    for(int i=0; i<NNZ+1; i++)
        sparse[i] = new T[3];

    // First row of sparse stores #rows, #cols, #NNZ vals
    sparse[0][0] = (int)rows;
    sparse[0][1] = (int)columns;
    sparse[0][2] = (int)NNZ;
    
    // Creating an array of size "columns" to stores no.of elements in each column
    colCount = new int[columns]{0};
}

template<class T>
void ArrayRep<T> :: toSparse(){
    // cout<<"In to sparse"<<endl;
    // index of sparse matrix
    int k = 1;
    int rows = sparse[0][0], columns = sparse[0][1];
    // cout<<"rows: "<<rows<<" "<<" columns: "<<columns<<endl;
    for(int i=0; i<rows; i++){
        // cout<<"row: "<<i<<endl;
        for(int j=0; j<columns; j++){
            // cout<<"col: "<<j<<endl;
            if(matrix[i][j] == 0)
                continue;
            sparse[k][0] = i;
            sparse[k][1] = j;
            // cout<<"Before matij"<<endl;
            sparse[k][2] = matrix[i][j];
            // cout<<"middle"<<endl;
            colCount[j]++;
            // cout<<"end"<<endl;
            k++;
        }
    }
    // cout<<"End to sparse"<<endl;
}

template<class T>
void ArrayRep<T> :: display(){
    cout<<"========================================="<<endl;
    cout<<"Triplet representation of Sparse matrix: "<<endl;
    cout<<"========================================="<<endl;
    cout<<"Row\t | Col\t | Val"<<endl;
    cout<<"-----------------------------------------"<<endl;
    for(int i=0; i<=sparse[0][2]; i++){
        cout<<sparse[i][0]<<"\t | "<<sparse[i][1]<<"\t | "<<sparse[i][2]<<endl;
    }
    cout<<"-----------------------------------------"<<endl;
}

