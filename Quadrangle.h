#pragma once
#include "Shape.h"

/**
* Klasa czworok¹ta reprezentuj¹ca figurê obiekt w programie. Dziedziczy po Shape.
*/
class Quadrangle : public Shape
{
public:
	/**
	* Konstruktor. Tworzy czworok¹t.
	* @param x1 wspó³rzêdna x pierwszego wierzcho³ka.
	* @param x2 wspó³rzêdna x drugiego wierzcho³ka.
	* @param x3 wspó³rzêdna x trzeciego wierzcho³ka.
	* @param x4 wspó³rzêdna x czwartego wierzcho³ka.
	* @param y1 wspó³rzêdna y pierwszego wierzcho³ka.
	* @param y2 wspó³rzêdna y drugiego wierzcho³ka.
	* @param y3 wspó³rzêdna y trzeciego wierzcho³ka.
	* @param y4 wspó³rzêdna y czwartego wierzcho³ka.
	* @param c kolor figury.
	* @param t typ figury czy trójk¹t b¹dŸ czworok¹t.
	*/
	Quadrangle(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4, wxColour c, Type t);
	/**
	* Rysuje figure na ekran.
	* @param panel miejsce gdzie wyrysowywana jest figura.
	*/
	void Draw(wxAutoBufferedPaintDC& panel) override;
	/**
	* Obraca figure o zadany k¹t wzglêdem jej œrodka.
	* @param radian k¹t w radianach o jaki obracana jest figura.
	*/
	void Rotate(double radian) override;
	/**
	* Przesuwa figurê o dane wspó³rzêdne.
	* @param x przesuniêcie x pikesli w lewo b¹dŸ w prawo.
	* @param y przesuniêcie y pikesli w górê b¹dŸ w dó³.
	*/
	void Move(int dx, int dy) override;
	/**
	* Zwraca punkty w których zawartê s¹ wierzcho³ki figury.
	*/
	wxPoint* GetPoints() const override { return pos; }
	/**
	* Ustawia aktualne po³o¿enie figury na po³o¿enie pocz¹tkowe.
	*/
	void Reset() const override;
	/**
	* Destruktor.
	*/
	~Quadrangle();
};