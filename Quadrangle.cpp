#include "Quadrangle.h"

Quadrangle::Quadrangle(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4)
{
	start_x[0] = x[0] = x1;
	start_x[1] = x[1] = x2;
	start_x[2] = x[2] = x3;
	start_x[3] = x[3] = x4;
	start_y[0] = y[0] = y1;
	start_y[1] = y[1] = y2;
	start_y[2] = y[2] = y3;
	start_y[3] = y[3] = y4;
}
void Quadrangle::Draw(wxAutoBufferedPaintDC& panel)
{
	panel.SetPen(wxPen(wxColour("red"), 1));
	for (int i = 0; i < 3; i++)
	{
		panel.DrawLine(x[i], y[i], x[i + 1], y[i + 1]);
	}
	panel.DrawLine(x[3], y[3], x[0], y[0]);
}
void Quadrangle::Rotate()
{
	//to do after Przemys³aw
}
void Quadrangle::Move(int dx, int dy)
{
	x[0] += dx;
	x[1] += dx;
	x[2] += dx;
	x[3] += dx;
	y[0] += dy;
	y[1] += dy;
	y[2] += dy;
	y[3] += dy;
}
Quadrangle::~Quadrangle()
{

}