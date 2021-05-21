#include "Triangle.h"

Triangle::Triangle(int x1, int x2, int x3, int y1, int y2, int y3, wxColour c): Shape(c, triangle)
{
	start = new wxPoint[3];
	pos = new wxPoint[3];

	start[0].x = pos[0].x = x1;
	start[1].x = pos[1].x = x2;
	start[2].x = pos[2].x = x3;

	start[0].y = pos[0].y = y1;
	start[1].y = pos[1].y = y2;
	start[2].y = pos[2].y = y3;
}
void Triangle::Draw(wxAutoBufferedPaintDC& panel)
{
	panel.SetPen(color);
	for (int i = 0; i < 2; i++)
	{
		panel.DrawLine(pos[i].x, pos[i].y, pos[i + 1].x, pos[i + 1].y);
	}
	panel.DrawLine(pos[2].x, pos[2].y, pos[0].x, pos[0].y);
}
void Triangle::Rotate()
{
	//to do after Przemys³aw
}
void Triangle::Move(int dx, int dy)
{
	pos[0].x += dx;
	pos[1].x += dx;
	pos[2].x += dx;
	pos[0].y += dy;
	pos[1].y += dy;
	pos[2].y += dy;
}
Triangle::~Triangle()
{
	delete[] start;
	delete[] pos;
}