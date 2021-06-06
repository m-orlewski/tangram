#pragma once

#include "Shape.h"

/**
* Statyczna klasa Zawieraj¹ca funkcje sprawdzaj¹ce czy punkt le¿y wewn¹trz wielok¹ta i czy dwa wielok¹ty na siebie nachodz¹.
*/
class ShapeCollision
{
public:
	/**
	* Funkcja sprawdzaj¹ca czy punkt le¿y wewn¹trz wielok¹ta.
	* @param shape obiekt klasy Shape reprezentuj¹cy wielok¹t
	* @param mouse obiekt klasy wxPoint reprezentuj¹cy punkt na ekranie
	* @param on_display flaga informuj¹ca czy punkt mouse znajduje siê w zasobniku(false) czy w obszarze roboczym(true)
	* @return true je¿eli punkt mouse le¿y wewn¹trz wielok¹ta shape, w przeciwnym razie false
	*/
	static bool isInside(const Shape& shape, wxPoint& mouse, bool on_display);


	static bool ShapeOverlap(Shape& polygon1, Shape& polygon2);
private:
	/**
	* Funkcja pomocnicza wywo³ywana przez isInside. Zwraca true je¿eli odcinki [p1, q1] i [p2, q2] siê przecinaj¹.
	* @param p1 obiekt wxPoint reprezentuj¹cy punkt pocz¹tkowy pierwszego odcinka
	* @param q1 obiekt wxPoint reprezentuj¹cy punkt koñcowy pierwszego odcinka
	* @param p2 obiekt wxPoint reprezentuj¹cy punkt pocz¹tkowy drugiego odcinka
	* @param q2 obiekt wxPoint reprezentuj¹cy punkt koñcowy drugiego odcinka
	* @return true je¿eli odcinki siê przecinaj¹, w przeciwnym razie false
	* @see isInside()
	*/
	static bool Intersect(const wxPoint& p1, const wxPoint& q1, const wxPoint& p2, const wxPoint& q2);

	/**
	* Funkcja pomocnicza wywo³ywana przez isInside. Zwraca orientacje ci¹gu 3 punktów p, q, r
	* @param p pierwszy punkt ci¹gu
	* @param q drugi punkt ci¹gu
	* @param r trzeci punkt ci¹gu
	* @see isInside()
	* @return 0 - punkty p, q, r s¹ wspó³liniowe, 1 - punkty p, q, r s¹ ustawione zgodnie z ruchem wskazówek zegara, 2 - przeciwnie do ruchu wskazówek zegara
	*/
	static int Orientation(const wxPoint& p, const wxPoint& q, const wxPoint& r);

	/**
	* Funkcja pomocnicza wywo³ywana przez isInside. Sprawdza czy punkt q le¿y na odcinku [p, r]
	* @param p punkt pocz¹tkowy odcinka
	* @param q sprawdzany punkt
	* @param r punkt koñcowy odcinka
	* @see isInside()
	* @return true je¿eli punkt q le¿y na odcinku [p, r], w przeciwnym razie false
	*/
	static bool Segment(const wxPoint& p, const wxPoint& q, const wxPoint& r);
};

