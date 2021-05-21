#pragma once
#include "Shape.h"



class Quadrangle : public Shape
{
public:
	Quadrangle(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4);
	void Draw(wxAutoBufferedPaintDC& panel) override;
	void Rotate() override;
	void Move(int dx, int dy) override;
	~Quadrangle();
private:
	int start_x[4], start_y[4];
	int x[4], y[4];
};