#ifndef __MATRIX_H__
#define __MATRIX_H__

class Matrix
{
public: 
    Matrix(long width, long height, double *value);
    Matrix(long width, long height); //ZEROS

    bool set_element(long row, long col, double value);
    double get_element(long row, long col); //!
    void print();
protected:
    long width;
    long height;
    double* value;
};

#endif

