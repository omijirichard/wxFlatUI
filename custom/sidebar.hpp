#pragma once

#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/timer.h>
#include <wx/event.h>
#include <wx/sizer.h>
#include <vector>
#include "button.hpp"

enum class SidebarID
{
  TIMER_ID=10000,
};

class Sidebar : public wxPanel
{

public:
  Sidebar(wxWindow*,const int& shrunkWidth=100, const int& enlargedWidth=200);
private:
  std::vector<SidebarButton*> m_buttonCollection;
  wxTimer m_slideTimer;
  int m_enlargedWidth;
  int m_shrunkWidth;
  int m_destinationWidth;
private:
  void buttonClicked(wxCommandEvent& event);
  void adjustWidth(wxTimerEvent& event);
  DECLARE_EVENT_TABLE();
public:
  void enlarge(const bool& );
};