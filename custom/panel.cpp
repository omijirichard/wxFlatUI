#include "panel.hpp"

Panel::Panel(wxWindow* parent,const unsigned int& id,const int& radius)
              :wxPanel(parent,id)
{
  m_radius=radius;
}

BEGIN_EVENT_TABLE(Panel,wxPanel)
  EVT_PAINT(Panel::onPaint)
END_EVENT_TABLE()

void Panel::onPaint(wxPaintEvent& event)
{
  wxPaintDC dc(this);
  render(dc);
  event.Skip();
}

void Panel::render(wxDC& dc)
{ 
  //make pen transparent to prevent black borders
  dc.SetPen(*wxTRANSPARENT_PEN);
  dc.SetBrush(wxBrush(m_backgroundColour));
  
  //draw rounded rectangle with given radius
  dc.DrawRoundedRectangle(0,0,this->GetSize().x,this->GetSize().y,m_radius);
}