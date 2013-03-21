#include <stdio.h>
#include "Matrix.h"

void Matrix::print()
{
    for(long i = 0; i < this->width; i++)
    {
        for(long j = 0; j < this->height; j++)
        {
            printf("%f ", this->value[i*width + j]);
        }
        printf("\n");
    }
}

Matrix Matrix::dot(Matrix *a)
{
    //assert (this->width == a->height);
    Matrix res(this->height, a->width);

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            for (int inner = 0; inner < 2; inner++) {
                res.set_element(row, col, res.get_element(row, col) + this->get_element(row, inner) * a->get_element(inner, col));
            }
        }
    }

    return res;
}

bool Matrix::set_element(long row, long col, double value)
{
    if ((row >= this->width) || (col >= this->height)) return false;
    this->value[row*this->height + col] = value;
    return true;
}

double Matrix::get_element(long row, long col)
{
    return this->value[row*this->height + col];
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
    this->value = value;
}
