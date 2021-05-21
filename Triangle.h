#pragma once
#include "Shape.h"



class Triangle : public Shape
{
public:
	Triangle(int x1, int x2, int x3, int y1, int y2, int y3, wxColour c);
	void Draw(wxAutoBufferedPaintDC& panel) override;
	void Rotate() override;
	void Move(int dx, int dy) override;
	~Triangle();
private:
	wxPoint start[3];
	wxPoint pos[3];
};