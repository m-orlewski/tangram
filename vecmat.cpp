#include "vecmat.h"


Vector operator* (const Matrix macierz, const Vector wektor)
{
    Vector TMP_result;
    unsigned int i = 0;
    unsigned int j = 0;
    while (i < 3)
    {
        TMP_result.dane[i] = 0.0;
        while (j < 3)
        {
            TMP_result.dane[i] = TMP_result.dane[i] + (macierz.dane[i][j] * wektor.dane[j]);
            j++;
        }
        i++;
    }
    return TMP_result;
}



Matrix Matrix::operator*(const Matrix macierz)
{
    Matrix TMP_result;
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < 3)
    {
        while (j < 3)
        {
            TMP_result.dane[i][j] = 0.0;
            while (k < 3)
            {
                TMP_result.dane[i][j] = TMP_result.dane[i][j] + (dane[i][k] * macierz.dane[k][j]);
                k++;
            }
            j++;
        }
        i++;
    }
    return TMP_result;
}
Matrix::Matrix()
{
    int i = 0;
    int j = 0;
    while (i < 3)
    {
        while (j < 3)
        {
            dane[i][j] = 0.0;
            j++;
        }
        i++;
    }
    dane[2][2] = 1.0;
}
Vector::Vector()
{
    dane[0] = 0.0;
    dane[1] = 0.0;
    dane[2] = 1.0;
}