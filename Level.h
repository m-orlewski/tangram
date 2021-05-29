#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <fstream>

#include <wx/wx.h>
#include <wx/wxprec.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>

class Level
{
private:
	std::vector<wxPoint> polygon;
public:
	void SetLevel(std::string filename);
	void Draw(wxAutoBufferedPaintDC& panel);
};