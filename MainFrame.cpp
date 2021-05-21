#include "MainFrame.h"

MainFrame::MainFrame(wxWindow* parent)
	:
	Frame(parent)
{
	display_panel->SetBackgroundStyle(wxBG_STYLE_PAINT);

	container.push_back(std::make_unique<Triangle>(920, 1160, 1040, 20, 20, 140));
	container.push_back(std::make_unique<Triangle>(920, 920, 1040, 20, 260, 140));
	container.push_back(std::make_unique<Triangle>(920, 860, 1040, 260, 320, 260));
	container.push_back(std::make_unique<Triangle>(1040, 1100, 1100, 140, 200, 140));
	container.push_back(std::make_unique<Triangle>(1040, 1160, 1160, 260, 20, 140));
	container.push_back(std::make_unique<Quadrangle>(1140, 1140, 980, 1200, 140, 260, 200, 200));
	container.push_back(std::make_unique<Quadrangle>(1100, 1100, 1160, 1160, 80, 200, 140, 20));
}

void MainFrame::OnClick(wxMouseEvent& event)
{
	// TODO: Implement OnClick
}

void MainFrame::Render(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(display_panel);
	dc.SetBackground(wxBrush(wxColour("white")));
	dc.Clear();

	dc.SetPen(wxPen(wxColour("black"), 1));
	dc.DrawLine(800, 0, 800, 720);
	dc.DrawLine(800, 320, 1280, 320);
	for (auto &object : container)
	{
		(*object).Draw(dc);
	}
}
