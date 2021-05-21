#include "MainFrame.h"

bool isInside(const Shape& shape, wxPoint& mouse, bool on_display=true);

MainFrame::MainFrame(wxWindow* parent)
	:
	Frame(parent)
{
	display_panel->SetBackgroundStyle(wxBG_STYLE_PAINT);

	container.push_back(std::make_unique<Triangle>(920, 1160, 1040, 20, 20, 140, wxColour("red")));
	container.push_back(std::make_unique<Triangle>(920, 920, 1040, 20, 260, 140, wxColour("yellow")));
	container.push_back(std::make_unique<Triangle>(920, 980, 1040, 260, 200, 260, wxColour("blue")));
	container.push_back(std::make_unique<Triangle>(1040, 1100, 1100, 140, 200, 80, wxColour("black")));
	container.push_back(std::make_unique<Triangle>(1040, 1160, 1160, 260, 140, 260, wxColour("green")));
	container.push_back(std::make_unique<Quadrangle>(1040, 1100, 1040, 980, 140, 200, 260, 200, wxColour("grey")));
	container.push_back(std::make_unique<Quadrangle>(1100, 1100, 1160, 1160, 80, 200, 140, 20, wxColour("cyan")));
}

void MainFrame::OnClick(wxMouseEvent& event)
{
	wxPoint mouse = wxPoint(event.m_x, event.m_y);

	if (mouse.x < 800)
	{
		for (auto& object : display)
		{
			
		}
	}
	else if (mouse.y < 320)
	{
		for (auto& object : container)
		{
			if (isInside(*object, mouse, false))
			{

			}
		}
	}
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

bool isInside(const Shape& shape, wxPoint& mouse, bool on_display)
{
	int n;
	if (shape.type == triangle)
		n = 3;
	else
		n = 4;

	wxPoint border;
	if (on_display)
		border = wxPoint(800, mouse.y);
	else
		border = wxPoint(1280, mouse.y);

	return true;
}
