#pragma once

#include <stdio.h>
#include <iostream>

/**
* Klasa Vector reprezentująca wektor o trzech składowych.
*/
class Vector
{
public:
    double dane[3];/**< Tablica przechowująca informacje o składowych wektora. */

    /**
    * Konsturktor. Tworzy wektor [0.0, 0.0, 1.0]
    */
    Vector();
};

/**
* Klasa Matrix reprezentująca macierz o wymiarze 3x3.
*/
class Matrix
{
public:
    double dane[3][3]; /**< Tablica przechowująca informacje o elementach macierzy. */

    /**
    * Konstruktor. Tworzy macierz { [0.0, 0.0, 0.0], [0.0, 0.0, 0.0], [0.0, 0.0, 1.0]}
    */
    Matrix();

    /**
    * Przeciążony operator * pozwalający na wykonanie operacji mnożenia Matrix*Vector
    * @param macierz macierz, przez którą mnożymy wektor
    * @param wektor wektor, który mnożymy przez macierz
    * @return wektor będący wynikiem naszego mnożenia
    */
    friend Vector operator*(const Matrix&, const Vector&);

    /**
    * Przeciążony operator * pozwalający na wykonanie operacji mnożenia Matrix*Matrix
    * @param macierz macierz, przez który mnożymy macierz
    * @return wynik mnożenia
    */
    Matrix operator*(const Matrix& macierz);
};

