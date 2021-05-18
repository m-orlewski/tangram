#pragma once

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/frame.h>

class Frame: public wxFrame
{
protected:
	wxPanel* display_panel;
public:
	
	Frame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(823, 550), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~Frame();
};

