#pragma once

#include <stdio.h>
#include <iostream>

class Vector
{
public:
    double dane[3];
    Vector();
};

class Matrix
{
public:
    double dane[3][3];
    Matrix();
    friend Vector operator*(const Matrix&, const Vector&);
    Matrix operator*(const Matrix& macierz);
};

