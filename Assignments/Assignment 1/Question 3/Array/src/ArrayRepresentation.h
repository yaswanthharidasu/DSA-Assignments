template <class T>
class ArrayRep{

    public:
    T **matrix;   // Conventional matrix
    T **sparse;   // Sparse matrix 
    int *colCount;  // Stores no.of elements in each column

    // Constructor
    ArrayRep(int rows, int columns, int NNZ, T **matrix);

    void toSparse();

    void display();
};