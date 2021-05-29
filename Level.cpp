#include "Level.h"

void Level::SetLevel(std::string filename)
{
	polygon.clear();
	int x1, y1, x2, y2;
	std::ifstream in;
	in.open(filename);

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
}

void Level::Draw(wxAutoBufferedPaintDC& panel)
{
	panel.SetPen(wxColor("black"));
	panel.SetBrush(wxColor("black"));
	panel.DrawPolygon(polygon.size(), polygon.data());
}