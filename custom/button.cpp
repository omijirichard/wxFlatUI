#include "button.hpp"

Button::Button(wxWindow* parent,const unsigned int& id,const wxString& text,const wxString& iconPath,const int& radius)
                                    :wxWindow(parent,id)
{
  this->m_parent=parent;
  this->m_id=id;
  this->text=text;
  this->radius=radius;
  this->SetForegroundColour(Colour::TEXT_COLOUR);
  this->SetFont(wxFont(wxFontInfo(10).FaceName("Helvetica").Bold()));
  m_pressed=false;
  m_hover=false;
  //create set the custom button's event type and id
  m_buttonEvent.SetEventType(wxEVT_BUTTON);
  m_buttonEvent.SetId(m_id);

  //check if icon path is empty and do some stuffs if so
  if (iconPath != "")
  {
     m_hasIcon=true;
     m_iconImage=wxImage(iconPath);
     if (!m_iconImage.IsOk()) wxMessageBox("icon button error");
  }
  else
  {
    m_hasIcon=false;
  }
  //check if has text
  hasText = (text != "")?true:false;
}
BEGIN_EVENT_TABLE(Button,wxWindow)
  EVT_PAINT(Button::onPaint)
  EVT_LEFT_DOWN(Button::onPress)
  EVT_LEFT_UP(Button::onRelease)
  EVT_ENTER_WINDOW(Button::onEnter)
  EVT_LEAVE_WINDOW(Button::onLeave)
END_EVENT_TABLE()


void Button::onPaint(wxPaintEvent& event)
{
  wxPaintDC dc(this);
  render(dc);
}
void Button::paintNow()
{
  wxClientDC dc(this);
  render(dc);
}
void Button::onPress(wxMouseEvent& event)
{
  m_pressed=true;
  paintNow();
  event.Skip();
}
void Button::onRelease(wxMouseEvent& event)
{
  wxPostEvent(this,m_buttonEvent);
  m_pressed=false;
  paintNow();
  event.Skip();
}
void Button::onEnter(wxMouseEvent& event)
{
  m_hover=true;
  paintNow();
  event.Skip();
}
void Button::onLeave(wxMouseEvent& event)
{
  m_hover=false;
  paintNow();
  event.Skip();
}
void Button::render(wxDC& dc)
{ 
  //make pen transparent to prevent black borders
  dc.SetPen(*wxTRANSPARENT_PEN);

  //set brush colour if pressed or not
  if(m_pressed)
  {
    dc.SetBrush(wxBrush(pressedColour));
  }
  else  if (m_hover)
  {
    dc.SetBrush(wxBrush(hoverColour));
  }
  else
  { 
    dc.SetBrush(wxBrush(idleColour));
  }
  
  //draw rounded rectangle with given radius
  dc.DrawRoundedRectangle(0,0,this->GetSize().x,this->GetSize().y,radius);

  //if the button has an icon change icon colour when pressed position icon
  if(m_hasIcon)
  {
    if(m_pressed)
      {
        m_iconImage.SetRGB(m_iconImage.GetSize(),iconPressedColour.Red(),iconPressedColour.Green(),iconPressedColour.Blue());
      }
    else
      {
        m_iconImage.SetRGB(m_iconImage.GetSize(),iconIdleColour.Red(),iconIdleColour.Green(),iconIdleColour.Blue());
      }
    //if the button has text draw the icon in the left side and draw text
    if(hasText)
    {
      dc.DrawBitmap(wxBitmap(m_iconImage),m_iconImage.GetSize().x/2,this->GetSize().y/2-m_iconImage.GetSize().y/2,true);
      dc.DrawText(text,this->GetSize().x/2-20,this->GetSize().y/2-5);
    }
    //else draw the icon in the center and don't draw text
    else 
    {
      dc.DrawBitmap(wxBitmap(m_iconImage),this->GetSize().x/2-m_iconImage.GetSize().x/2,this->GetSize().y/2-m_iconImage.GetSize().y/2,true);
    }
  }
}
void Button::setIconPath(const wxString& iconPath)
{
  if (iconPath != "")
  {
     m_hasIcon=true;
     m_iconImage=wxImage(iconPath);
     if (!m_iconImage.IsOk()) wxMessageBox("icon button error");
     paintNow();
  }
  else
  {
    m_hasIcon=false;
  }
}
void Button::setText(const wxString& text)
{
  this->text=text;
  hasText = (text != "")?true:false;
}
Button::~Button()
{
  
}
