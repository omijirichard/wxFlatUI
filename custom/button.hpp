#pragma once
#include <wx/window.h>
#include <wx/image.h>
#include <wx/colour.h>
#include <wx/dcclient.h>
#include <wx/event.h>
#include <wx/msgdlg.h>

#include "constants.hpp"

class Button: public wxWindow
{
public:
  Button(wxWindow* ,const unsigned int& id,const wxString& text="",const wxString& iconPath="",const int& radius=0);
  ~Button();
  void setIconPath(const wxString&);
  void setText(const wxString&);
private:
  int m_id; 
  wxString text;
  wxImage m_iconImage;
  
  bool m_hasIcon;
  bool m_hasText;
  
  wxWindow* m_parent;
  
protected:
  wxCommandEvent m_buttonEvent;
  bool m_pressed;
  bool m_hover;
protected:
  virtual void onPaint(wxPaintEvent&);
  virtual void paintNow();
  virtual void onPress(wxMouseEvent&);
  virtual void onRelease(wxMouseEvent&);
  virtual void render(wxDC&);
  virtual void onEnter(wxMouseEvent&);
  virtual void onLeave(wxMouseEvent&);
private:
  DECLARE_EVENT_TABLE();
public:
  bool hasText;
  bool isRounded;
  unsigned int radius;
  wxColour pressedColour=Colour::BUTTON_PRESSED;
  wxColour idleColour=Colour::BUTTON_IDLE;
  wxColour hoverColour=Colour::BUTTON_HOVER;
  wxColour iconIdleColour=Colour::ICON_IDLE;
  wxColour iconPressedColour=Colour::ICON_PRESSSED;
};

class SidebarButton:public Button
{
public:
  SidebarButton(wxWindow* parent,const unsigned int& id,const wxString& text="",const wxString& iconPath="",const int& minHeight=20,const int& maxHeight=40,const int& radius=0):
    Button(parent,id,text,iconPath,radius)
  {
    iconPressedColour=Colour::ICON_IDLE;
    this->SetSizeHints(wxSize(-1,minHeight),wxSize(-1,maxHeight));
    this->hasText=false;
  }
  
public:
  bool isSelected=false;
  void paint()
  {
    this->paintNow();
  }
  void setPressed(bool pressed)
  {
    m_pressed=pressed;
  }
  
private:
  void onRelease(wxMouseEvent& event)
  { 
    wxPostEvent(this,m_buttonEvent);
    paintNow();
    event.Skip();
  }

};