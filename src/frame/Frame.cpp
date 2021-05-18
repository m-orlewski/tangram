#include "../../include/frame/Frame.h"

Frame::Frame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	display_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	bSizer1->Add(display_panel, 1, wxEXPAND | wxALL, 5);

	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);
}

Frame::~Frame()
{
}
