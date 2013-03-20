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
