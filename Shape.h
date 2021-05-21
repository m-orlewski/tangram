#pragma once
#include <wx/wx.h>
#include <wx/wxprec.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>

enum Type {triangle, quadrangle};

class Shape
{
public:
	Shape(wxColour c, Type t) : color(c), type(t) {}
	virtual void Draw(wxAutoBufferedPaintDC &panel) = 0;
	virtual void Rotate() = 0;
	virtual void Move(int x, int y) = 0;
	virtual wxPoint* GetPoints() const = 0;
	virtual ~Shape() {};
protected:
	wxColour color;
	wxPoint* start;
	wxPoint* pos;
public:
	const Type type;
};