#pragma once

#include <stdio.h>
#include <iostream>

/**
* Klasa Vector reprezentuj¹ca wektor o trzech sk³adowych.
*/
class Vector
{
public:
    double dane[3];/**< Tablica przechowuj¹ca informacje o sk³adowych wektora. */

    /**
    * Konsturktor. Tworzy wektor [0.0, 0.0, 1.0]
    */
    Vector();
};

/**
* Klasa Matrix reprezentuj¹ca macierz o wymiarze 3x3.
*/
class Matrix
{
public:
    double dane[3][3]; /**< Tablica przechowuj¹ca informacje o elementach macierzy. */

    /**
    * Konstruktor. Tworzy macierz { [0.0, 0.0, 0.0], [0.0, 0.0, 0.0], [0.0, 0.0, 1.0]}
    */
    Matrix();

    /**
    * Przeci¹¿ony operator * pozwalaj¹cy na wykonanie operacji mno¿enia Matrix*Vector
    * @param macierz macierz, przez któr¹ mno¿ymy wektor
    * @param wektor wektor, który mno¿ymy przez macierz
    * @return wektor bêd¹cy wynikiem naszego mno¿enia
    */
    friend Vector operator*(const Matrix&, const Vector&);

    /**
    * Przeci¹¿ony operator * pozwalaj¹cy na wykonanie operacji mno¿enia Matrix*Matrix
    * @param macierz macierz, przez który mno¿ymy macierz
    * @return wynik mno¿enia
    */
    Matrix operator*(const Matrix& macierz);
};

