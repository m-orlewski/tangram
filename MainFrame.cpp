#include "MainFrame.h"

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

	display_panel->Connect(wxEVT_MOTION, wxMouseEventHandler(MainFrame::Mouse_Move), NULL, this);
	display_panel->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MainFrame::OnClickUp), NULL, this);
}

void MainFrame::OnClick(wxMouseEvent& event)
{
	if (dragging)
	{
		dragging = false;
		return;
	}
	 
	wxPoint mouse = wxPoint(event.m_x, event.m_y);
	mouse_pos = mouse;
	mouse_prev = mouse;

	if (mouse.x < 800)
	{
		for (auto& object : display)
		{
			if (isInside(*object, mouse, true))
			{
				moving = object.get();
				dragging = true;
			}
		}
	}
	else if (mouse.y < 320)
	{
		for (auto& object : container)
		{
			if (isInside(*object, mouse, false))
			{
				moving = object.get();
				dragging = true;
			}
		}
	}
	
}

void MainFrame::Mouse_Move(wxMouseEvent& event)
{
	if (moving != nullptr)
	{
		mouse_prev = mouse_pos;
		mouse_pos = wxPoint(event.GetX(), event.GetY());
		moving->Move(mouse_pos.x - mouse_prev.x, mouse_pos.y - mouse_prev.y);
		Refresh();
	}
}

void MainFrame::OnClickUp(wxMouseEvent& event)
{
	if (!dragging && moving)
	{
		int panel_width, panel_height;
		display_panel->GetClientSize(&panel_width, &panel_height);
		int n = (moving->type == Type::TRIANGLE) ? 3 : 4;
		wxPoint* points = moving->GetPoints();
		for (int i = 0; i < n; i++)
		{
			if (points[i].x <= 0 || points[i].x >= panel_width || points[i].y <= 0 || points[i].y >= panel_height)
			{
				moving->Reset();
				break;
			}
		}



		moving = nullptr;
		Refresh();
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


	for (auto& object : container)
	{
		(*object).Draw(dc);
	}
}



bool isInside(const Shape& shape, wxPoint& mouse, bool on_display)
{
	int n;
	if (shape.type == Type::TRIANGLE)
		n = 3;
	else
		n = 4;

	wxPoint border;
	if (on_display)
		border = wxPoint(800, mouse.y);
	else
		border = wxPoint(1280, mouse.y);

	const wxPoint* polygon = shape.GetPoints();

	int count = 0;
	int i = 0;

	do
	{
		int next = (i + 1) % n;

		if (Intersect(polygon[i], polygon[next], mouse, border))
		{
			if (Orientation(polygon[i], mouse, polygon[next]) == 0)
				return Segment(polygon[i], mouse, polygon[next]);

			count++;
		}
		i = next;
	} while (i != 0);

	return (count % 2 == 1);
}

bool Intersect(const wxPoint& p1, const wxPoint& q1, const wxPoint& p2, const wxPoint& q2)
{
	int o1 = Orientation(p1, q1, p2);
	int o2 = Orientation(p1, q1, q2);
	int o3 = Orientation(p2, q2, p1);
	int o4 = Orientation(p2, q2, q1);

	if (o1 != o2 && o3 != o4)
		return true;

	if (o1 == 0 && Segment(p1, p2, q1))
		return true;

	if (o2 == 0 && Segment(p1, q2, q1))
		return true;

	if (o3 == 0 && Segment(p2, p1, q2))
		return true;

	if (o4 == 0 && Segment(p2, q1, q2))
		return true;

	return false;
}

int Orientation(const wxPoint& p, const wxPoint& q, const wxPoint& r)
{
	int a = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	if (a > 0)
		return 1;
	else if (a < 0)
		return 2;
	else
		return 0;
}

bool Segment(const wxPoint& p, const wxPoint& q, const wxPoint& r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) && q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;
	return false;
}

MainFrame::~MainFrame()
{
	display_panel->Disconnect(wxEVT_MOTION, wxMouseEventHandler(MainFrame::Mouse_Move), NULL, this);
	display_panel->Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(MainFrame::OnClickUp), NULL, this);
}
