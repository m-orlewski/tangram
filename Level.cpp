#include "Level.h"

void Level::SetLevel(std::string filename1, std::string filename2)
{
	polygon.clear();
	check.clear();
	int x1, y1, x2, y2;
	std::ifstream in;
	in.open(filename1);

	if (in.is_open())
	{
		while (!in.eof())
		{
			in >> x1 >> y1 >> x2 >> y2;
			polygon.push_back(wxPoint(x1, y1));
			polygon.push_back(wxPoint(x2, y2));
		}
	}
	in.close();

	int type = -1;
	in.open(filename2);
	if (in.is_open())
	{
		std::vector<wxPoint> points;
		while (!in.eof())
		{
			int prev = type;
			in >> x1 >> y1 >> type;
			if (prev != type && prev != -1)
			{
				check.push_back(Poly(points, prev));
				points.clear();
			}
			
			points.push_back(wxPoint(x1 + 200, y1 + 100));
		}
		check.push_back(Poly(points, type));
	}
	in.close();
}

void Level::Draw(wxAutoBufferedPaintDC& panel)
{
	panel.SetPen(wxColor("black"));
	panel.SetBrush(wxColor("black"));
	panel.DrawPolygon(polygon.size(), polygon.data());

	wxColor col = wxColor("black");
	for (auto& poly : check)
	{
		if (col == wxColor("black"))
			col = wxColor("red");
		else
			col = wxColor("black");

		panel.SetPen(col);
		panel.SetBrush(col);

		if (poly.type > 3)
			panel.DrawPolygon(4, poly.points.data());
		else
			panel.DrawPolygon(3, poly.points.data());
	}
}