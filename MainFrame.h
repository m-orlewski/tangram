#pragma once

#include <wx/dcclient.h>
#include <wx/dcbuffer.h>

#include <algorithm>
#include <vector>
#include <iostream>

#include "GUI.h"
#include "Triangle.h"
#include "Quadrangle.h"
#include "Level.h"
#include "ShapeCollision.h"

/**
* Klasa reprezentuj¹ca g³ówne okno programu.
*/
class MainFrame : public Frame
{
public:
	/**
	* Konstruktor. Tworzy okno, inicjalizuje atrybuty shapes i level. Dodaje wxMenuBar oraz odpowiednie eventy.
	* @param parent wskaŸnik na obiekt wxWindow bêd¹cy nadrzêdnym oknem
	*/
	MainFrame(wxWindow* parent);

	/**
	* Event uruchamiany po klikniêciu lewego przycisku myszy. Sprawdza czy klikniêto na obiekt z wektora shapes,
	* je¿eli tak, obiekt ten mo¿e byæ przenoszony po ekranie i upuszczony w innym miejscu.
	* @param event obiekt wxMouseEvent
	*/
	void OnClick( wxMouseEvent& event );

	/**
	* Event wxEVT_PAINT. Rysuje na ekranie.
	* @param event obiekt wxPaintEvent
	*/
	void Render( wxPaintEvent& event );

	/**
	* Event uruchamiany po puszczeniu lewego przycisku myszy. Je¿eli obiekt z wektora shapes jest aktualnie przenoszony,
	* ten obiekt jest upuszczany na ekran(je¿eli jest to mo¿liwe), sprawdzane jest tak¿e czy u³o¿ony kszta³t jest poprawny.
	* @param event obiekt wxMouseEvent
	*/
	void OnClickUp(wxMouseEvent& event);

	/**
	* Event uruchamiany w momencie poruszania myszk¹. Je¿eli obiekt z wektora shapes jest aktualnie przenoszony, 
	* aktualizowane s¹ jego wspó³rzêdne.
	* @param event obiekt wxMouseEvent
	*/
	void Mouse_Move(wxMouseEvent& event);

	/**
	* Event uruchamiany po puszczeniu prawego przycisku myszy. Je¿eli obiekt z wektora shapes jest aktualnie przenoszony,
	* zostaje on obrócony o 90 stopni. 
	* @param event obiekt wxMouseEvent
	*/
	void OnRightUp(wxMouseEvent& event);

	/**
	* Event uruchamiany po klikniêciu prawego przycisku myszy. Je¿eli obiekt z wektora shapes jest aktualnie przenoszony,
	* flaga rotating zostaje ustawiona na true co zapobiega przesuwaniu obiektu.
	* @param event obiekt wxMouseEvent
	*/
	void OnRightDown(wxMouseEvent& event);

	/**
	* Event uruchamiany po puszczeniu œrodkowego przyciski myszy. Je¿eli obiekt z wektora shapes jest aktualnie przenoszony,
	* obiekt ten wraca do zasobnika. Je¿eli ¿aden obiekt nie by³ aktualnie przenoszony, do zasobnika wraca obiekt nad którym aktualnie
	* jest ustawiony kursor (je¿eli taki obiekt istnieje).
	* @param event obiekt wxMouseEvent
	*/
	void OnMiddleUp(wxMouseEvent& event);

	/**
	* Destruktor. Zwalnia pamiêæ i od³¹cza eventy.
	*/
	~MainFrame();

protected:
	Level* level; /**< wskaŸnik na aktualny Level */
	std::vector<std::unique_ptr<Shape>> shapes; /**< wektor obiektów Shape bêd¹cych uk³adanymi kszta³tami */
	Shape* moving = nullptr; /**< wskaŸnik na aktualnie przenoszony obiekt klasy Shape */
	wxPoint mouse_pos; /**< aktualna pozycja myszki */
	wxPoint mouse_prev; /**< poprzednia pozycja myszki */
	bool dragging = false; /**< flaga informuj¹ca czy obiekt Shape jest aktualnie przenoszony */
	bool rotating = false; /**< flaga informuj¹ca czy obiekt Shape jest aktualnie obracany */
};
