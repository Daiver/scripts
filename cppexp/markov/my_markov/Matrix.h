#ifndef __MATRIX_H__
#define __MATRIX_H__

//Простой класс "матрица", для алгоритмов viterbi и forward-backward
//Лучшим вариантом было бы использовать какую-нибудь готовую библиотеку для работы с линейной алгеброй
class Matrix
{
public: 
    Matrix(const Matrix &m);
    Matrix(long width, long height, double *value);
    Matrix(long width, long height); //ZEROS
    ~Matrix();

    bool set_element(long row, long col, double value);
    double get_element(long row, long col); //!
    void print();
    Matrix mul(Matrix *m);
    Matrix dot(Matrix *a);
    Matrix trans();
    Matrix normalize();
    long max_value_index();
    double sum();
protected:
    long width;//Небольшая путаница - width это число строк, height - число столбцов
    long height;
    double* value;//значения элементов матрицы. Такое представление мне показалось удобней чем представление ввиде double**
};

#endif

