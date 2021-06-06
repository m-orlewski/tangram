#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/frame.h>


/**
* Klasa Frame u¿ywana przy tworzeniu g³ównego okna programu.
*/
class Frame : public wxFrame 
{
public:
	/**
	* Konstruktor. Ustawia parametry okna, dodaje display_panel, sizery, ³¹czy niektóre eventy.
	* @param parent wskaŸnik na obiekt wxWindow bêd¹cy nadrzêdnym oknem
	* @param id id okna
	* @param title napis wyœwietlany u góry okna
	* @param pos pozycja okna
	* @param size rozmiar okna
	* @param style styl okna
	*/
	Frame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1280, 720), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	
	/**
	* Destruktor.
	*/
	~Frame();

protected:
	wxPanel* display_panel; /**< wskaŸnik na g³ówny panel na oknie */
};
