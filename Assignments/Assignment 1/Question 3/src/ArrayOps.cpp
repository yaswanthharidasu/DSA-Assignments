#include"ArrayOps.h"
#include<iostream>
using namespace std;

int** ArrayOps :: addition(int **m1, int **m2){
    if((m1[0][0] != m2[0][0]) || (m1[0][1] != m2[0][1])){
        cout<<"Rows and columns are not same. Matrices cannot be added"<<endl;
        exit(0);
    }

    int rows = m1[0][0], columns = m1[0][1];
    int NNZ1 = m1[0][2], NNZ2 = m2[0][2];

    int maxNNZ = NNZ1+NNZ2;
    // Result matrix 
    int **result = new int* [maxNNZ+1];
    for(int i=0; i<maxNNZ+1; i++)
        result[i] = new int[3];

    result[0][0] = rows;
    result[0][1] = columns;

    int i=1, j=1, k=1;

    while(i < NNZ1+1 && j < NNZ2+1){
        // Row and column are same in both matrices
        if((m1[i][0] == m2[j][0]) && (m1[i][1] == m2[j][1])){
            int sum = m1[i][2] + m2[j][2];
            if(sum != 0){
                result[k][0] = m1[i][0];
                result[k][1] = m1[i][1];
                result[k][2] = sum;
                i++, j++, k++;
            }
        }
        else if((m1[i][0] < m2[j][0]) || (m1[i][0] == m2[j][0] && m1[i][1] < m2[j][1])){
            result[k][0] = m1[i][0];
            result[k][1] = m1[i][1];
            result[k][2] = m1[i][2];
            i++, k++;
        }
        else{
            result[k][0] = m2[j][0];
            result[k][1] = m2[j][1];
            result[k][2] = m2[j][2];
            j++, k++;
        }
    }

    while(i < NNZ1+1){
        result[k][0] = m1[i][0];
        result[k][1] = m1[i][1];
        result[k][2] = m1[i][2];
        i++, k++;
    }
    while(j < NNZ2+1){
        result[k][0] = m2[j][0];
        result[k][1] = m2[j][1];
        result[k][2] = m2[j][2];
        j++, k++;
    }
    result[0][2] = k-1;

    return result;
}

void ArrayOps :: multiplication(int **m1, int **m2){

}

int**  ArrayOps :: transpose(int **m, int *colCount){
    int rows = m[0][0], columns = m[0][1], NNZ = m[0][2];
    // Result matrix 
    int **result = new int* [NNZ];
    for(int i=0; i<NNZ; i++)
        result[i] = new int[3];

    // Prefix Count array which is similar to prefix sum which tells no.of non-zero elements in all columns < i
    int *prefixCount = new int[columns]{0};
    for(int i=1; i<columns; i++)
        prefixCount[i] = prefixCount[i-1]+ colCount[i-1];
    
    for(int i=1; i<=NNZ; i++){
        // The row in which the current value is to be placed
        int row = prefixCount[m[i][1]];
        result[row][0] = m[i][1];
        result[row][1] = m[i][0];
        result[row][2] = m[i][2];
        prefixCount[m[i][1]]++;
    }
    return result;
}
