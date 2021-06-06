#pragma once

#include "Shape.h"

class ShapeCollision
{
public:
	static bool isInside(const Shape& shape, wxPoint& mouse, bool on_display);
	static bool ShapeOverlap(Shape& polygon1, Shape& polygon2);
private:
	static bool Intersect(const wxPoint& p1, const wxPoint& q1, const wxPoint& p2, const wxPoint& q2);
	static int Orientation(const wxPoint& p, const wxPoint& q, const wxPoint& r);
	static bool Segment(const wxPoint& p, const wxPoint& q, const wxPoint& r);
};

