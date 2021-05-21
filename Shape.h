#pragma once
#include <wx/wx.h>
#include <wx/wxprec.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
class Shape
{
public:
	virtual void Draw(wxAutoBufferedPaintDC &panel) = 0;
	virtual void Rotate() = 0;
	virtual void Move(int x, int y) = 0;
	//virtual ~Shape() = 0;
protected:

};