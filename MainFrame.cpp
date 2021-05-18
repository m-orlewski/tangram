#include "MainFrame.h"

MainFrame::MainFrame( wxWindow* parent )
:
Frame( parent )
{
	display_panel->SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void MainFrame::OnClick( wxMouseEvent& event )
{
// TODO: Implement OnClick
}

void MainFrame::Render( wxPaintEvent& event )
{
int w, h;
display_panel->GetClientSize(&w, &h);

wxAutoBufferedPaintDC dc(display_panel);
dc.SetBackground(wxBrush(wxColour("white")));
dc.Clear();

dc.SetPen(wxPen(wxColour("black"), 5));
dc.DrawLine(w - 480, 0, w - 480, h);
dc.DrawLine(w - 480, 320, w, 320);

dc.DrawLine(w - 480 + 120, 20, w - 120, 20);
dc.DrawLine(w - 480 + 120, 20, w - 480 + 120, 260);
dc.DrawLine(w - 480 + 120, 260, w - 120, 260);
dc.DrawLine(w - 120, 20, w - 120, 260);
}
