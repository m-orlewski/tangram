#pragma once
#include "Shape.h"



class Triangle : public Shape
{
public:
	void Draw(wxPanel *panel) const override;
	void Rotate() override;
	void Move(int dx, int dy) override;
private:
	int start_x[3], start_y[3];
	int x[3], y[3];
};