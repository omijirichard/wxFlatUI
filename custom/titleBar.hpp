#pragma once
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/event.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/font.h>
#include "constants.hpp"
#include "button.hpp"
class TitleBar: public wxPanel
{
private:
  wxPoint m_deltaPosition;
  wxTopLevelWindow* parent;
  bool m_mouseDragHasStarted;
  wxStaticText* m_titleText;
public:
  TitleBar(wxTopLevelWindow*  parent,const wxString& title,
               const int& minHeight=20,const int& maxHeight=24);
  ~TitleBar();
private:
  void onMouseEvent(wxMouseEvent& );
  template<typename eventType>
  void maximize(eventType& );
  void minimize(wxCommandEvent& );
  void close(wxCommandEvent& );
  Button* m_minimizeButton;
  Button* m_maximizeButton;
  Button* m_closeButton;
  DECLARE_EVENT_TABLE();
public:
  wxString title;
  wxString minimizedTitle;
};