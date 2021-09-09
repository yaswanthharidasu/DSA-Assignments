class ArrayRep{

    public:
    int **matrix;   // Conventional matrix
    int **sparse;   // Sparse matrix 
    int *colCount;  // Stores no.of elements in each column

    // Constructor
    ArrayRep(int rows, int columns, int NNZ, int **matrix);

    void toSparse();

    void display();
};