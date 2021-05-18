#pragma once
#include <wx/wx.h>
#include <wx/wxprec.h>

class Shape
{
public:
	virtual void Draw(wxPanel *panel) const;
	virtual void Rotate();
	virtual void Move(int x, int y);
protected:

};