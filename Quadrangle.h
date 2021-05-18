#pragma once
#include "Shape.h"



class Quadrangle : public Shape
{
public:
	void Draw(wxPanel* panel) const override;
	void Rotate() override;
	void Move(int dx, int dy) override;
private:
	int start_x[4], start_y[4];
	int x[4], y[4];
};