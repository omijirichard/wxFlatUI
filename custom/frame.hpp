#pragma once
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include "custom/constants.hpp"

enum class MousePosition
{
  TOPLEFT,
  TOPCENTER,
  TOPRIGHT,
  MIDDLELEFT,
  MIDDLECENTER,
  MIDDLERIGHT,
  BOTTOMLEFT,
  BOTTOMCENTER,
  BOTTOMRIGHT
};

class Frame:public wxFrame
{
public:
 Frame(const wxString& title,const wxPoint& position,const wxSize& size);
private:
  void onMouseEvent(wxMouseEvent&);
  const int m_frameBorder=5;
  bool m_mouseDragHasStarted=false;
  MousePosition getMousePosition(const wxPoint&);
  void setMouseCursor(const MousePosition&);
  void onMouseDown(wxMouseEvent&);
  void onMouseRelease(wxMouseEvent& );
  void onMouseCaptureLost(wxMouseCaptureLostEvent&);
  DECLARE_EVENT_TABLE();
private:
  wxPoint m_mousePositionInTermsOf012;
  wxPoint m_mouseInitialPosition;
  wxRect m_frameInitialSize;
  MousePosition m_mouseState;
};
