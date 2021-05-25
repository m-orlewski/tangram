#include "Triangle.h"

Triangle::Triangle(int x1, int x2, int x3, int y1, int y2, int y3, wxColour c): Shape(c, Type::TRIANGLE)
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
	panel.DrawPolygon(3, pos);
}
void Triangle::Rotate(double radian)
{
	Matrix rotate;
	rotate.dane[0][0] = cos(radian);
	rotate.dane[0][1] = -sin(radian);
	rotate.dane[0][2] = 0.;

	rotate.dane[1][0] = sin(radian);
	rotate.dane[1][1] = cos(radian);
	rotate.dane[1][2] = 0.;

	rotate.dane[2][0] = 0.;
	rotate.dane[2][1] = 0.;
	rotate.dane[2][2] = 1.;

	Vector P;
	for (int i = 0; i < 3; i++)
	{
		P.dane[0] = pos[i].x;
		P.dane[1] = pos[i].y;

		P = rotate * P;

		pos[i].x = P.dane[0];
		pos[i].y = P.dane[1];
	}
}
void Triangle::Move(int dx, int dy)
{
	for (int i = 0; i < 3; i++)
	{
		pos[i].x += dx;
		pos[i].y += dy;
	}
}

void Triangle::Reset() const
{
	for (int i = 0; i < 3; i++)
	{
		pos[i].x = start[i].x;
		pos[i].y = start[i].y;
	}
}

Triangle::~Triangle()
{
	delete[] start;
	delete[] pos;
}