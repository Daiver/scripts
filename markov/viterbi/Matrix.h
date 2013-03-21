#ifndef __MATRIX_H__
#define __MATRIX_H__

class Matrix
{
public: 
    Matrix(long width, long height, double *value);
    Matrix(long width, long height); //ZEROS
    ~Matrix();

    bool set_element(long row, long col, double value);
    double get_element(long row, long col); //!
    void print();
    Matrix dot(Matrix *a);
protected:
    long width;//with values are mixed =(
    long height;
    double* value;
};

#endif

