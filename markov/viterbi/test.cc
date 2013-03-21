#include <stdio.h>
#include "Matrix.h"

int main(int argc, char** argv)
{
    double d1[6] = {1, 2, 3, 4, 5, 6};
    double d2[6] = {3, 1, 3, 0, 3, 0};
    Matrix m1(2, 3, d1);
    Matrix m2(2, 1, d2);
    m1.print();
    m2.print();
    m1.dot(&m2).print();
    return 0;
}
