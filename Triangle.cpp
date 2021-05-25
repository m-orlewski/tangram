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
	//wyliczyæ œrodek masy
	Matrix translate1, translate2;
	translate1.dane[0][0] = 1.;
	translate1.dane[0][1] = 0.;
	translate1.dane[0][2] = -(pos[0].x + pos[1].x + pos[2].x) / 3; //dx

	translate1.dane[1][0] = 0.;
	translate1.dane[1][1] = 1.;
	translate1.dane[1][2] = -(pos[0].y + pos[1].y + pos[2].y) / 3; //dy

	translate1.dane[2][0] = 0.;
	translate1.dane[2][1] = 0.;
	translate1.dane[2][2] = 1.;

	translate2.dane[0][0] = 1.;
	translate2.dane[0][1] = 0.;
	translate2.dane[0][2] = (pos[0].x + pos[1].x + pos[2].x) / 3; //dx

	translate2.dane[1][0] = 0.;
	translate2.dane[1][1] = 1.;
	translate2.dane[1][2] = (pos[0].y + pos[1].y + pos[2].y) / 3; //dy

	translate2.dane[2][0] = 0.;
	translate2.dane[2][1] = 0.;
	translate2.dane[2][2] = 1.;

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

	Matrix transform = translate1 * rotate * translate2;
	Vector P;
	for (int i = 0; i < 3; i++)
	{
		P.dane[0] = pos[i].x;
		P.dane[1] = pos[i].y;

		P = transform * P;

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