#include "Quadrangle.h"

Quadrangle::Quadrangle(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4, wxColour c): Shape(c, quadrangle)
{
	start = new wxPoint[4];
	pos = new wxPoint[4];

	start[0].x = pos[0].x = x1;
	start[1].x = pos[1].x = x2;
	start[2].x = pos[2].x = x3;
	start[3].x = pos[3].x = x4;

	start[0].y = pos[0].y = y1;
	start[1].y = pos[1].y = y2;
	start[2].y = pos[2].y = y3;
	start[3].y = pos[3].y = y4;
}
void Quadrangle::Draw(wxAutoBufferedPaintDC& panel)
{
	panel.SetPen(color);
	for (int i = 0; i < 3; i++)
	{
		panel.DrawLine(pos[i].x, pos[i].y, pos[i + 1].x, pos[i + 1].y);
	}
	panel.DrawLine(pos[3].x, pos[3].y, pos[0].x, pos[0].y);
}
void Quadrangle::Rotate(double radian)
{
	//to do after Przemys³aw
}
bool Quadrangle::Move(int dx, int dy)
{
	pos[0].x += dx;
	pos[1].x += dx;
	pos[2].x += dx;
	pos[3].x += dx;
	pos[0].y += dy;
	pos[1].y += dy;
	pos[2].y += dy;
	pos[3].y += dy;
	if (0 >= pos[0].x || pos[0].x >= 1280 || 0 >= pos[1].x || pos[1].x >= 1280 || 0 >= pos[2].x || pos[2].x >= 1280 || 0 >= pos[3].x || pos[3].x >= 1280 ||
		0 >= pos[0].y || pos[0].y >= 720 || 0 >= pos[1].y || pos[1].y >= 720 || 0 >= pos[2].y || pos[2].y >= 720 || 0 >= pos[3].y || pos[3].y >= 720)
	{
		pos[0].x = start[0].x;
		pos[1].x = start[1].x;
		pos[2].x = start[2].x;
		pos[3].x = start[3].x;

		pos[0].y = start[0].y;
		pos[1].y = start[1].y;
		pos[2].y = start[2].y;
		pos[3].y = start[3].y;
		return false;
	}
	return true;
}
Quadrangle::~Quadrangle()
{
	delete[] start;
	delete[] pos;
}