#pragma once
#include "Shape.h"



class Triangle : public Shape
{
public:
	Triangle(int x1, int x2, int x3, int y1, int y2, int y3, wxColour c, Type t);
	void Draw(wxAutoBufferedPaintDC& panel) override;
	void Rotate(double radian) override;
	void Move(int dx, int dy) override;
	wxPoint* GetPoints() const override { return pos; }
	void Reset() const override;
	~Triangle();
};