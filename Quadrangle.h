#pragma once
#include "Shape.h"



class Quadrangle : public Shape
{
public:
	Quadrangle(int x1, int x2, int x3, int x4, int y1, int y2, int y3, int y4, wxColour c);
	void Draw(wxAutoBufferedPaintDC& panel) override;
	void Rotate() override;
	void Move(int dx, int dy) override;
	wxPoint* GetPoints() const override { return pos; }
	~Quadrangle();
};