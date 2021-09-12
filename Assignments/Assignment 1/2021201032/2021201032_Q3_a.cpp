#include<iostream>
using namespace std;

// ================================================ Class ArrayRepresentation: Begin ================================================================================

template <class T>
class ArrayRep{
    public:
    T **matrix;   // Conventional matrix
    T **sparse;   // Sparse matrix 
    int *colCount;  // Stores no.of elements in each column

    // Constructor
    ArrayRep(int rows, int columns, int NNZ, T **matrix);

    void toSparse();
};

template<class T>
ArrayRep<T> :: ArrayRep(int rows, int columns, int NNZ, T **matrix){
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

// ================================================ Class ArrayRepresentation: End ================================================================================

// ================================================ Class ArrayOps: Begin ================================================================================

template<class T>
class ArrayOps{
    public:
    T** addition(ArrayRep<T> m1, ArrayRep<T> m2);

    T** multiplication(ArrayRep<T> m1, ArrayRep<T> m2);

    T** transpose(ArrayRep<T> m);
};

template<class T>
T** ArrayOps<T> :: addition(ArrayRep<T> mat1, ArrayRep<T> mat2){
    T **m1 = mat1.sparse;
    T **m2 = mat2.sparse;

    if((m1[0][0] != m2[0][0]) || (m1[0][1] != m2[0][1])){
        cout<<"Rows and columns are not same. Matrices cannot be added"<<endl;
        exit(0);
    }

    int rows = m1[0][0], columns = m1[0][1];
    int NNZ1 = m1[0][2], NNZ2 = m2[0][2];

    int maxNNZ = NNZ1+NNZ2;
    // Result matrix 
    T **result = new T* [maxNNZ+1];
    for(int i=0; i<maxNNZ+1; i++)
        result[i] = new T[3];

    result[0][0] = rows;
    result[0][1] = columns;

    int i=1, j=1, k=1;

    while(i < NNZ1+1 && j < NNZ2+1){
        // Row and column are same in both matrices
        if((m1[i][0] == m2[j][0]) && (m1[i][1] == m2[j][1])){
            T sum = m1[i][2] + m2[j][2];
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

template<class T>
T** ArrayOps<T> :: multiplication(ArrayRep<T> mat1, ArrayRep<T> mat2){
    
    T **m1 = mat1.sparse;
    T **m2T = transpose(mat2);

    int NNZ1 = m1[0][2], NNZ2 = m2T[0][2];

    T **result = new T*[NNZ1*NNZ2 + 1];
    result[0] = new T[3];

    result[0][0] = m1[0][0];
    result[0][1] = m2T[0][0];

    int i=1, j=1, k=1;
    int temp_i, temp_j;
    while(i <= NNZ1){
        j=1;
        int r = m1[i][0];
        while(j <= NNZ2){
            int c = m2T[j][0];
            temp_i = i, temp_j = j;
            T sum = 0;
            
            while(temp_i <= NNZ1 && m1[temp_i][0] == r && temp_j <= NNZ2 && m2T[temp_j][0] == c){
                if(m1[temp_i][1] == m2T[temp_j][1]){
                    sum += T(m1[temp_i][2] * m2T[temp_j][2]);
                    temp_i++, temp_j++;
                }
                else if(m1[temp_i][1] < m2T[temp_j][1])
                    temp_i++;
                else
                    temp_j++;
            }
            if(sum != 0){
                result[k] = new T[3];
                result[k][0] = r;
                result[k][1] = c;
                result[k][2] = sum;
                k++;
            }
            while(j <= NNZ2 && m2T[j][0] == c)
                j++;
        }
        while(i <= NNZ1 && m1[i][0] == r)
            i++;    
    }
    result[0][2] = k-1;

    return result;
}

template<class T>
T**  ArrayOps<T> :: transpose(ArrayRep<T> mat){
    T **m = mat.sparse;
    int *colCount = mat.colCount;

    int rows = m[0][0], columns = m[0][1], NNZ = m[0][2];
    // Result matrix 
    T **result = new T* [NNZ+1];
    for(int i=0; i<NNZ+1; i++)
        result[i] = new T[3];

    result[0][0] = int(columns);
    result[0][1] = int(rows);
    result[0][2] = int(NNZ);

    // Prefix Count array which is similar to prefix sum which tells no.of non-zero elements in all columns < i
    int *prefixCount = new int[columns]{0};

    for(int i=1; i<columns; i++)
        prefixCount[i] = prefixCount[i-1]+ colCount[i-1];

    for(int i=1; i<=NNZ; i++){
        // The row in which the current value is to be placed
        int row = prefixCount[int(m[i][1])]+1;
        result[row][0] = m[i][1];
        result[row][1] = m[i][0];
        result[row][2] = m[i][2];
        prefixCount[int(m[i][1])]++;
    }
    return result;
}

// ================================================ Class ArrayOps: End ================================================================================

// ================================================ Driver code: main() ================================================================================

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
    m.toSparse();
    m.display();

    ArrayOps<T> ops;
    T **result = ops.transpose(m);
    cout<<"Transpose of matrix:"<<endl;
    displayMatrix(result, result[0][2]);
}

template <class T>
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
    
    // Converting conventional matrices into sparse matrices
    ArrayRep<T> m1(rows, columns, NNZ1, matrix1);
    ArrayRep<T> m2(rows, columns, NNZ2, matrix2);
    m1.toSparse();
    m2.toSparse();
    
    ArrayOps<T> ops;
    T **result = ops.addition(m1, m2);
    cout<<"Addition of two matrices:"<<endl;
    displayMatrix(result, result[0][2]);
}

template <class T>
void multiplication(){
    int rows1, columns1, rows2, columns2;
    int NNZ1=0, NNZ2=0;

    cout<<"Enter rows and columns of 1st matrix:";
    cin>>rows1>>columns1;

    cout<<endl<<"Enter First matrix values:"<<endl;

    T **matrix1 = new T*[rows1];
    readMatrix(rows1, columns1, NNZ1, matrix1);

    cout<<"Enter rows and columns of 2nd matrix:";
    cin>>rows2>>columns2;

    cout<<endl<<"Enter Second matrix values:"<<endl;

    T **matrix2 = new T*[rows2];
    readMatrix(rows2, columns2, NNZ2, matrix2);

    // Converting conventional matrices into sparse matrices
    ArrayRep<T> m1(rows1, columns1, NNZ1, matrix1);
    ArrayRep<T> m2(rows2, columns2, NNZ2, matrix2);
    m1.toSparse();
    m2.toSparse();

    ArrayOps<T> ops;
    T **result = ops.multiplication(m1, m2);
    cout<<"Mulitplication of two matrices:"<<endl;
    displayMatrix(result, result[0][2]);    
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

