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

	display_panel->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(MainFrame::OnClick), NULL, this);
	display_panel->Connect(wxEVT_PAINT, wxPaintEventHandler(MainFrame::Render), NULL, this);
	display_panel->Connect(wxEVT_MOTION, wxMouseEventHandler(MainFrame::Mouse_Move), NULL, this);
	display_panel->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(MainFrame::OnClickUp), NULL, this);
	display_panel->Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(MainFrame::OnRightUp), NULL, this);
	display_panel->Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(MainFrame::OnRightDown), NULL, this);
	display_panel->Connect(wxEVT_MIDDLE_UP, wxMouseEventHandler(MainFrame::OnMiddleUp), NULL, this);

	wxMenuBar* menuBar = new wxMenuBar();
	wxMenu* fileMenu = new wxMenu();
	menuBar->Append(fileMenu, _("&Shapes"));
	SetMenuBar(menuBar);

	fileMenu->AppendRadioItem(1, _("Stó³"));
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
			if (!object.get()->in_container && ShapeCollision::isInside(*object, mouse, true))
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
			if (object.get()->in_container && ShapeCollision::isInside(*object, mouse, false))
			{
				moving = object.get();
				dragging = true;
			}
		}
	}
	if (moving)
		moving->color = wxColor("red");
	Refresh();
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
		bool overlap = false;

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
					if (ShapeCollision::ShapeOverlap(*moving, *shape_uptr))
					{
						reset = true;
						overlap = true;
						break;
					}
				}
			}
		}

		if (reset || (on_display && in_container))
		{
			if (!overlap)
			{
				moving->Reset();
				moving->in_container = true;
			}
			else
			{
				dragging = true;
				return;
			}
		}
		else if (on_display)
		{
			moving->in_container = false;
		}
		else if (in_container)
		{
			moving->in_container = true;
		}
		moving->color = wxColor("grey");
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
				int answer = wxMessageBox("Zwyciêstwo!", "Czy chcesz zagraæ ponownie?", wxYES_NO, this);
				if (answer == wxYES)
				{
					for (auto& shape : shapes)
					{
						shape->Reset();
						shape->in_container = true;
					}
				}
				else if (answer == wxNO)
				{
					Close();
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

void MainFrame::OnMiddleUp(wxMouseEvent& event)
{
	if (!moving)
	{
		wxPoint mouse = wxPoint(event.GetX(), event.GetY());
		for (auto& shape : shapes)
		{
			if (ShapeCollision::isInside(*shape, mouse, true))
			{
				shape->Reset();
				shape->in_container = true;
				Refresh();
			}
		}
	}
	else
	{
		moving->Reset();
		moving->color = wxColor("grey");
		moving->in_container = true;
		moving = nullptr;
		dragging = false;
		Refresh();
	}
}

void MainFrame::Render(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(display_panel);
	dc.SetBackground(wxBrush(wxColour("white")));
	dc.Clear();

	dc.SetPen(wxPen(wxColour("black"), 3));
	dc.DrawLine(800, 0, 800, 720);
	dc.DrawLine(800, 320, 1280, 320);

	level->Draw(dc);

	for (auto& object : shapes)
	{
		if (object.get() != moving)
			(*object).Draw(dc);
	}

	if (moving)
		moving->Draw(dc);
}

MainFrame::~MainFrame()
{
	display_panel->Disconnect(wxEVT_LEFT_DOWN, wxMouseEventHandler(MainFrame::OnClick), NULL, this);
	display_panel->Disconnect(wxEVT_PAINT, wxPaintEventHandler(MainFrame::Render), NULL, this);
	display_panel->Disconnect(wxEVT_MOTION, wxMouseEventHandler(MainFrame::Mouse_Move), NULL, this);
	display_panel->Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(MainFrame::OnClickUp), NULL, this);
	display_panel->Disconnect(wxEVT_RIGHT_UP, wxMouseEventHandler(MainFrame::OnRightUp), NULL, this);
	display_panel->Disconnect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(MainFrame::OnRightDown), NULL, this);

	delete level;
}

