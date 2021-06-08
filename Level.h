#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <fstream>
#include <cmath>

#include "Shape.h"

#include <wx/wx.h>
#include <wx/wxprec.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>

/**
* Struktura reprezentuj¹ca wielok¹t.
*/
struct Poly
{
	std::vector<wxPoint> points; /**<Wektor zawieraj¹cy punkty bêd¹ce wierzcho³kami wielok¹ta. */
	Type type; /**<Zmienna przechowuj¹ca informacje jakiego typu jest wielok¹t. */

	/**
	* Konstruktor tworz¹cy wielok¹t.
	* @param Points wektor punktów bêd¹cych wierzcho³kami wielok¹ta
	* @param T typ wielok¹ta
	*/
	Poly(std::vector<wxPoint> Points, Type T) : points(Points), type(T) {}
};

/**
* Klasa reprezentuj¹ca wybrany poziom gry.
*/
class Level
{
private:
	std::vector<wxPoint> polygon; /**<Wektor zawieraj¹y punkty bie¿¹ce wierzcho³kami kszta³tu do u³o¿enia */
	std::vector<Poly> check; /**<Wektor punktów u¿ywany przy sprawdzaniu kszta³tu u³o¿onego */
	std::vector<Poly> check_copy; /**< Kopia wektora check */
public:
	/**
	* Metoda, która odpowiada za tworzenie poziomu.
	* @param filename1 œcie¿ka do pliku zawieraj¹cego wspó³rzêdne wierzcho³ków wielok¹ta do u³o¿enia
	* @param filename2 œcie¿ka do pliku zawieraj¹cego wspó³rzêdne wierzcho³ków wielok¹ta u¿ywane do sprawdzenie poprawnoœci u³o¿enia kszta³tu.
	*/
	void SetLevel(std::string filename1, std::string filename2);

	/**
	* Metoda, wyrysowuj¹ca kszta³t do u³o¿enia na ekran.
	* @param panel obiekt u¿ywany do rysowania
	*/
	void Draw(wxAutoBufferedPaintDC& panel);

	/**
	* Metoda sprawdzaj¹ca czy kszta³t jest u³o¿ony poprawnie.
	* @param shapes wektor obiektów Shape uk³adanych przez u¿ytkownika
	* @return true je¿eli u³o¿enie jest poprawne, w przeciwnym razie false
	*/
	bool CheckLevel(const std::vector<std::unique_ptr<Shape>>& shapes);
};