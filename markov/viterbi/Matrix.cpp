#include <stdio.h>
#include "Matrix.h"

void Matrix::print()
{
    for(long i = 0; i < this->width; i++)
    {
        for(long j = 0; j < this->height; j++)
        {
            printf("%f ", this->value[i*height + j]);
        }
        printf("\n");
    }
}

Matrix Matrix::dot(Matrix *a)
{
    //assert (this->height == a->width);
    Matrix res(this->width, a->height);

    for (int row = 0; row < this->width; row++) {
        for (int col = 0; col < a->height; col++) {
            double sum = 0;
            for (int inner = 0; inner < this->height; inner++) {
                sum += this->get_element(row, inner) * a->get_element(inner, col);
                //res.set_element(row, col, res.get_element(row, col) + this->get_element(row, inner) * a->get_element(inner, col));
            }
            res.set_element(row, col, sum);
        }
    }

    return res;
}

Matrix Matrix::trans()
{
    Matrix res(this->height, this->width);
    for (int i = 0; i < this->width; i++)
        for(int j = 0; j < this->height; j++)
            res.set_element(j, i, this->get_element(i, j));
    return res;
}

double Matrix::sum()
{
    double res = 0; 
    for(int i = 0; i < this->width*this->height; i++) res += this->value[i];
    return res;
}

Matrix Matrix::normalize()
{
    Matrix res(this->width, this->height, this->value);
    double sum = this->sum();
    for(int i = 0; i < this->width*this->height; i++) res.value[i] /= sum;
    return res;
}

Matrix Matrix::mul(Matrix *m)
{
    Matrix res(this->width, this->height);
    for(int i = 0; i < this->width*this->height; i++) res.value[i] = m->value[i] * this->value[i];
    return res;
}

long Matrix::max_value_index()
{
    long index = -1;
    double max_value = 0.0;
    for(long i = 0; i < this->width*this->height; i++) 
        if (this->value[i] > max_value)
        {
            max_value = this->value[i];
            index = i;
        }
    return index;
}

bool Matrix::set_element(long row, long col, double value)
{
    this->value[row*this->height + col] = value;
    return true;
}

double Matrix::get_element(long row, long col)
{
    return this->value[row*this->height + col];
}

Matrix::~Matrix()
{
    delete this->value;
}
Matrix::Matrix(long width, long height)
{
    this->width = width;
    this->height = height;
    this->value = new double[width*height];
    for(long i = 0; i < width*height; i++)
    {
        this->value[i] = 0.0;
    }
}

Matrix::Matrix(long width, long height, double *value)
{
    this->width = width;
    this->height = height;
    this->value = new double[width*height];
    for(int i = 0; i < width*height; i++) this->value[i] = value[i];
}

Matrix::Matrix(const Matrix &m)
{
    this->width = m.width;
    this->height = m.height;
    this->value = new double[m.width*m.height];
    for(int i = 0; i < m.width*m.height; i++) this->value[i] = m.value[i];
}
