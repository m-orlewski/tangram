#pragma once
#include <wx/wx.h>
#include <wx/wxprec.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>

#include "vecmat.h"
#include "type.h"

#include <cmath>
/**
* Klasa wirtualna reprezentuj¹ca figurê obiekt w programie.
*/
class Shape
{
public:
	/**
	* Konstruktor. Tworzy figure, trójk¹t lub czworok¹t.
	* @param c kolor figury.
	* @param t typ figury czy trójk¹t b¹dŸ czworok¹t.
	*/
	Shape(wxColour c, Type t) : color(c), type(t), start(nullptr), pos(nullptr) {}
	/**
	* Rysuje figure na ekran.
	* @param panel miejsce gdzie wyrysowywana jest figura.
	*/
	virtual void Draw(wxAutoBufferedPaintDC &panel) = 0;
	/**
	* Obraca figure o zadany k¹t wzglêdem jej œrodka.
	* @param radian k¹t w radianach o jaki obracana jest figura.
	*/
	virtual void Rotate(double radian) = 0;
	/**
	* Przesuwa figurê o dane wspó³rzêdne.
	* @param x przesuniêcie x pikesli w lewo b¹dŸ w prawo.
	* @param y przesuniêcie y pikesli w górê b¹dŸ w dó³.
	*/
	virtual void Move(int x, int y) = 0;
	/**
	* Zwraca punkty w których zawartê s¹ wierzcho³ki figury.
	*/
	virtual wxPoint* GetPoints() const = 0;
	/**
	* Ustawia aktualne po³o¿enie figury na po³o¿enie pocz¹tkowe.
	*/
	virtual void Reset() const = 0;
	/**
	* Destruktor.
	*/
	virtual ~Shape() {}
protected:
	wxPoint* start; /**< wskaŸnik na tablice zawieraj¹c¹ wspó³rzêdne pocz¹tkowe wierzcho³ków figury. */
	wxPoint* pos; /**< wskaŸnik na tablice zawieraj¹c¹ aktualne wspó³rzêdne wierzcho³ków figury. */
public:
	const Type type; /**< Zmienna przechowywuj¹ca informacje jakiego typu jest figura (czy czworok¹t, czy trójk¹t). */
	bool in_container = true; /**< Zmienna okreœlaj¹ca czy figura znajduje siê w kontenerze na figury. */
	wxColour color; /**< Zmienna okreœlaj¹ca kolor figury. */
};
