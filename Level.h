#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <fstream>

#include <wx/wx.h>
#include <wx/wxprec.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>

struct Poly
{
	std::vector<wxPoint> points;
	int type;
	Poly(std::vector<wxPoint> Points, int T) : points(Points), type(T) {}
};

class Level
{
private:
	std::vector<wxPoint> polygon;
	std::vector<Poly> check;
public:
	void SetLevel(std::string filename1, std::string filename2);
	void Draw(wxAutoBufferedPaintDC& panel);
};