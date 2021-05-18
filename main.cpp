#include <wx/wx.h>
#include <wx/wxprec.h>
#include "MainFrame.h"

class App : public wxApp
{
public:
	virtual bool OnInit();
	virtual int OnExit();
};

IMPLEMENT_APP(App);

bool App::OnInit()
{
	MainFrame* main_frame = new MainFrame(nullptr);

	main_frame->Show(true);
	SetTopWindow(main_frame);

	return true;
}

int App::OnExit()
{
	return 0;
}