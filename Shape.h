#pragma once
#include <wx/wx.h>
#include <wx/wxprec.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>

#include "vecmat.h"
#include "type.h"

#include <cmath>

class Shape
{
public:
	Shape(wxColour c, Type t) : color(c), type(t), start(nullptr), pos(nullptr) {}
	virtual void Draw(wxAutoBufferedPaintDC &panel) = 0;
	virtual void Rotate(double radian) = 0;
	virtual void Move(int x, int y) = 0;
	virtual wxPoint* GetPoints() const = 0;
	virtual void Reset() const = 0;
	virtual ~Shape() {}
protected:
	wxColour color;
	wxPoint* start;
	wxPoint* pos;
public:
	const Type type;
	bool in_container = true;
};