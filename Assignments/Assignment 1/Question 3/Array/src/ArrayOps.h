#include"ArrayRepresentation.h"

template<class T>
class ArrayOps{
    public:
    T** addition(ArrayRep<T> m1, ArrayRep<T> m2);

    T** multiplication(ArrayRep<T> m1, ArrayRep<T> m2);

    T** transpose(ArrayRep<T> m);
};