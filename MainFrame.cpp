#include "MainFrame.h"

MainFrame::MainFrame(wxWindow* parent)
	:
	Frame(parent)
{
	display_panel->SetBackgroundStyle(wxBG_STYLE_PAINT);

	shapes.push_back(std::make_unique<Triangle>(920, 1160, 1040, 20, 20, 140, wxColour("grey"), Type::TRIANGLE1));
	shapes.push_back(std::make_unique<Triangle>(920, 920, 1040, 20, 260, 140, wxColour("grey"), Type::TRIANGLE1));
	shapes.push_back(std::make_unique<Triangle>(920, 980, 1040, 260, 200, 260, wxColour("grey"), Type::TRIANGLE2));
	shapes.push_back(std::make_unique<Triangle>(1040, 1100, 1100, 140, 200, 80, wxColour("grey"), Type::TRIANGLE2));
	shapes.push_back(std::make_unique<Triangle>(1040, 1160, 1160, 260, 140, 260, wxColour("grey"), Type::TRIANGLE3));
	shapes.push_back(std::make_unique<Quadrangle>(1040, 1100, 1040, 980, 140, 200, 260, 200, wxColour("grey"), Type::QUADRANGLE4));
	shapes.push_back(std::make_unique<Quadrangle>(1100, 1100, 1160, 1160, 80, 200, 140, 20, wxColour("grey"), Type::QUADRANGLE5));

	display_panel->Connect(wxEVT_MOTION, wxMouseEventHandler(MainFrame::Mouse_Move), NULL, this);
	display_panel->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MainFrame::OnClickUp), NULL, this);
	display_panel->Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(MainFrame::OnRightUp), NULL, this);
	display_panel->Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(MainFrame::OnRightDown), NULL, this);

	wxMenuBar* menuBar = new wxMenuBar();
	wxMenu* fileMenu = new wxMenu();
	menuBar->Append(fileMenu, _("&Shapes"));
	SetMenuBar(menuBar);

	fileMenu->AppendRadioItem(1, _("St�"));
	fileMenu->AppendRadioItem(2, _("Buda"));
	fileMenu->AppendRadioItem(3, _("Kot"));
	fileMenu->AppendRadioItem(4, _("Statek"));
	fileMenu->AppendRadioItem(5, _("Murek"));
	fileMenu->AppendRadioItem(6, _("Dom"));

	level = new Level();
	level->SetLevel("assets/stol_r.geo", "assets/stol_s.geo");

	this->Bind(wxEVT_MENU, [&, this](wxCommandEvent&) { level->SetLevel("assets/stol_r.geo", "assets/stol_s.geo"); Refresh(); }, 1);
	this->Bind(wxEVT_MENU, [&, this](wxCommandEvent&) { level->SetLevel("assets/buda_r.geo", "assets/buda_s.geo"); Refresh(); }, 2);
	this->Bind(wxEVT_MENU, [&, this](wxCommandEvent&) { level->SetLevel("assets/kot_r.geo", "assets/kot_s.geo"); Refresh(); }, 3);
	this->Bind(wxEVT_MENU, [&, this](wxCommandEvent&) { level->SetLevel("assets/statek_r.geo", "assets/statek_s.geo"); Refresh(); }, 4);
	this->Bind(wxEVT_MENU, [&, this](wxCommandEvent&) { level->SetLevel("assets/murek_r.geo", "assets/murek_s.geo"); Refresh(); }, 5);
	this->Bind(wxEVT_MENU, [&, this](wxCommandEvent&) { level->SetLevel("assets/domek_r.geo", "assets/domek_s.geo"); Refresh(); }, 6);
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
		for (auto& object : shapes)
		{
			if (!object.get()->in_container && isInside(*object, mouse, true))
			{
				moving = object.get();
				dragging = true;
			}
		}
	}
	else if (mouse.y < 320)
	{
		for (auto& object : shapes)
		{
			if (object.get()->in_container && isInside(*object, mouse, false))
			{
				moving = object.get();
				dragging = true;
			}
		}
	}
	
}

void MainFrame::Mouse_Move(wxMouseEvent& event)
{
	if (moving != nullptr && !rotating)
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
		int n = (moving->type < Type::QUADRANGLE4) ? 3 : 4;
		wxPoint* points = moving->GetPoints();
		bool reset = false;
		bool on_display = false;
		bool in_container = false;

		for (int i = 0; i < n; i++)
		{
			if (points[i].x <= 0 || points[i].x >= panel_width || points[i].y <= 0 || points[i].y >= panel_height)
			{
				reset = true;
				break;
			}
			else if (points[i].x > 800)
			{
				if (points[i].y > 320)
				{
					reset = true;
					break;
				}
				else
				{
					in_container = true;
				}
			}
			else
			{
				on_display = true;
			}
		}
		if (!reset)
		{
			for (std::unique_ptr<Shape>& shape_uptr : shapes)
			{
				if (shape_uptr.get() != moving)
				{
					if (ShapeOverlap(*moving, *shape_uptr))
					{
						reset = true;
						break;
					}
				}
			}
		}

		if (reset || (on_display && in_container))
		{
			//moving->Reset();
			//moving->in_container = true;
			moving->color = wxColor("red");
			Refresh();
			moving->color = wxColor("grey");
			Refresh();
			return;
		}
		else if (on_display)
		{
			moving->in_container = false;
		}
		else if (in_container)
		{
			moving->in_container = true;
		}
		moving = nullptr;
		Refresh();

		bool all_on_display = true;
		for (auto& shape : shapes)
		{
			if ((*shape).in_container)
			{
				all_on_display = false;
				break;
			}
		}

		if (all_on_display)
		{
			if (level->CheckLevel(shapes))
			{
				for (auto& shape : shapes)
				{
					shape->Reset();
				}
			}
			Refresh();
		}
	}
}

void MainFrame::OnRightUp(wxMouseEvent& event)
{
	if (moving)
	{	
		if (event.GetWheelRotation() < 0)
		{
			moving->Rotate(-45);
		}
		else
		{
			moving->Rotate(45);
		}
		Refresh();
		rotating = false;
	}
}

void MainFrame::OnRightDown(wxMouseEvent& event)
{
	if (moving)
		rotating = true;
}

void MainFrame::Render(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(display_panel);
	dc.SetBackground(wxBrush(wxColour("white")));
	dc.Clear();


	dc.SetPen(wxPen(wxColour("black"), 1));
	dc.DrawLine(800, 0, 800, 720);
	dc.DrawLine(800, 320, 1280, 320);

	level->Draw(dc);

	for (auto& object : shapes)
	{
		(*object).Draw(dc);
	}

}



bool isInside(const Shape& shape, wxPoint& mouse, bool on_display)
{
	int n;
	if (shape.type < Type::QUADRANGLE4)
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

bool ShapeOverlap(Shape& shape1, Shape& shape2)
{
	Shape* poly1 = &shape1;
	Shape* poly2 = &shape2;

	for (int shape = 0; shape < 2; shape++)
	{
		if (shape == 1)
		{
			poly1 = &shape2;
			poly2 = &shape1;
		}

		int n1 = (poly1->type < Type::QUADRANGLE4) ? 3 : 4;
		int n2 = (poly2->type < Type::QUADRANGLE4) ? 3 : 4;

		auto points1 = poly1->GetPoints();
		auto points2 = poly2->GetPoints();

		for (int a = 0; a < n1; a++)
		{
			int b = (a + 1) % n1;
			wxPoint axisProjection = wxPoint(-(points1[b].y - points1[a].y), points1[b].x - points1[a].x);

			double min1, max1;
			for (int i = 0; i < n1; i++)
			{
				double q = points1[i].x * static_cast<double>(axisProjection.x) + points1[i].y * static_cast<double>(axisProjection.y);
				
				if (i)
				{
					min1 = std::min(min1, q);
					max1 = std::max(max1, q);
				}
				else
				{
					min1 = q;
					max1 = q;
				}
			}

			double min2, max2;
			for (int i = 0; i < n2; i++)
			{
				double q = points2[i].x * static_cast<double>(axisProjection.x) + points2[i].y * static_cast<double>(axisProjection.y);

				if (i)
				{
					min2 = std::min(min2, q);
					max2 = std::max(max2, q);
				}
				else
				{
					min2 = q;
					max2 = q;
				}
			}

			if (!(max2 >= min1 && max1 >= min2))
				return false;
		}

	}

	return true;
}

MainFrame::~MainFrame()
{
	display_panel->Disconnect(wxEVT_MOTION, wxMouseEventHandler(MainFrame::Mouse_Move), NULL, this);
	display_panel->Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(MainFrame::OnClickUp), NULL, this);
	display_panel->Disconnect(wxEVT_RIGHT_UP, wxMouseEventHandler(MainFrame::OnRightUp), NULL, this);
	display_panel->Disconnect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(MainFrame::OnRightDown), NULL, this);

	delete level;
}

