#include<iostream>
#include"ArrayOps.h"
#include"ArrayRepresentation.h"
using namespace std;

template <class T>
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

template <class T>
void displayMatrix(T **matrix, int NNZ){
    cout<<"========================================="<<endl;
    cout<<"Triplet representation of Sparse matrix: "<<endl;
    cout<<"========================================="<<endl;
    cout<<"Row\t | Col\t | Val"<<endl;
    cout<<"-----------------------------------------"<<endl;
    for(int i=0; i<NNZ+1; i++){
        cout<<matrix[i][0]<<"\t | "<<matrix[i][1]<<"\t | "<<matrix[i][2]<<endl;
    }
    cout<<"-----------------------------------------"<<endl;
}

template <class T>
void transpose(){
    int rows, columns;
    int NNZ=0;

    cout<<"Enter no.of rows and columns:";
    cin>>rows>>columns;

    cout<<endl<<"Enter matrix values:"<<endl;

    T **matrix = new T*[rows];
    readMatrix(rows, columns, NNZ, matrix);

    ArrayRep<T> m(rows, columns, NNZ, matrix);
    // m.toSparse();
    // m.display();

    // ArrayOps<T> ops;
    // T **result = ops.transpose(m);
    // cout<<"Transpose of matrix:"<<endl;
    displayMatrix(matrix, NNZ);
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
        // addition<double>();
    }
    else if(option == 2){
        // multiplication<double>();
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
         