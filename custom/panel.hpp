#pragma once
#include <wx/panel.h>
#include <wx/window.h>
#include <wx/event.h>
#include <wx/dcclient.h>
#include <wx/dc.h>

#include "constants.hpp"

class Panel:public wxPanel
{
public:
  Panel(wxWindow* ,const unsigned int& ,const int& );

private:
  wxColour m_backgroundColour=Colour::PANEL_COLOUR;
  int m_radius=0;
  DECLARE_EVENT_TABLE();
private:
  void onPaint(wxPaintEvent&);
  void render(wxDC&);
};

