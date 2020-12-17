#include "frame.hpp"


Frame::Frame(const wxString& title,const wxPoint& position,const wxSize& size):
    wxFrame(nullptr,wxID_ANY,title,position,size,wxMINIMIZE_BOX|wxMAXIMIZE_BOX
                                                    |wxRESIZE_BORDER|wxNO_BORDER)
//,wxNO_BORDER|wxCAPTIONwxMINIMIZE_BOX|wxMAXIMIZE_BOX|
//wxRESIZE_BORDER|wxSYSTEM_MENU|
{
  this->SetBackgroundColour(Colour::BACKGROUND);
}

BEGIN_EVENT_TABLE(Frame,wxFrame)
  EVT_MOUSE_EVENTS(Frame::onMouseEvent)
  EVT_MOUSE_CAPTURE_LOST(Frame::onMouseCaptureLost)
END_EVENT_TABLE()



void Frame::onMouseEvent(wxMouseEvent& event)
{
  wxPoint mousePositionXY=event.GetPosition();
  if (event.Moving())
  { 
    m_mouseState=this->getMousePosition(mousePositionXY);
    this->setMouseCursor(m_mouseState);

    
  }
  else if (event.Dragging() && m_mouseState!= MousePosition::MIDDLECENTER)
  {
    this->setMouseCursor(m_mouseState);
    wxPoint mouseCurrentPosition;
    mouseCurrentPosition.x=this->ClientToScreen(event.GetPosition()).x-m_frameInitialSize.x;
    mouseCurrentPosition.y=this->ClientToScreen(event.GetPosition()).y-m_frameInitialSize.y;
    //get the change in position of the mouse wrt the first click position
    wxPoint changeInPosition=mouseCurrentPosition-m_mouseInitialPosition;
    //new rect that will represen the new size and position of the screen
    wxRect newRect;
    //if the mouse is in the middle of the border is 0 else -1 or 1
    // and then add it to the frame's width or height
    newRect.width=(m_mousePositionInTermsOf012.x-1)*changeInPosition.x +m_frameInitialSize.width;
    newRect.height=(m_mousePositionInTermsOf012.y-1)*changeInPosition.y +m_frameInitialSize.height;
    //if the mouse is on the top or left side of the screen adjust the initial 
    //position of the left and top side of the screen to the value of the change
    //in position
    newRect.x=((m_mousePositionInTermsOf012.x==0)?changeInPosition.x:0) + m_frameInitialSize.x;
    newRect.y=((m_mousePositionInTermsOf012.y==0)?changeInPosition.y:0) + m_frameInitialSize.y;
    this->SetSize(newRect);
    this->Update();
  }
  else if (event.LeftIsDown()&&!m_mouseDragHasStarted)
  {
    
    if(m_mouseState!=MousePosition::MIDDLECENTER)
    {
      if (!HasCapture())
      {
        this->CaptureMouse();
      }
      m_frameInitialSize=this->GetRect();
      m_mouseInitialPosition.x=this->ClientToScreen(mousePositionXY).x -m_frameInitialSize.x;
      m_mouseInitialPosition.y=this->ClientToScreen(mousePositionXY).y -m_frameInitialSize.y;
      m_mouseDragHasStarted=true;
      
    }
  }
  else if(event.LeftUp())
  {
    m_mouseDragHasStarted=false;
    m_frameInitialSize=GetRect();
    this->SetCursor(wxCURSOR_DEFAULT);
    if (this->HasCapture())
    this->ReleaseMouse();
    
  }
  else
  {
    this->SetCursor(wxCURSOR_DEFAULT);
    event.Skip();
  }
}

MousePosition Frame::getMousePosition(const wxPoint& position)
{
  //if maximized you can't resize this 
  if (IsMaximized())
  {
    return MousePosition::MIDDLECENTER;
  }
  wxPoint  mousePoint=ClientToScreen(position);
  wxRect frameRect=this->GetRect();
  //make the position of the mouse return 3 values 0,1,2
  int x= (mousePoint.x<=frameRect.x+m_frameBorder)?0:
           (mousePoint.x>=frameRect.x+frameRect.width-m_frameBorder)?2:1;
  int y= (mousePoint.y<=frameRect.y+m_frameBorder)?0: 
           (mousePoint.y>=frameRect.y+frameRect.height-m_frameBorder)?2:1;
           
  MousePosition mousePositionArray[3][3]=
  {
    {MousePosition::TOPLEFT,MousePosition::TOPCENTER,MousePosition::TOPRIGHT},
    {MousePosition::MIDDLELEFT,MousePosition::MIDDLECENTER,MousePosition::MIDDLERIGHT},
    {MousePosition::BOTTOMLEFT,MousePosition::BOTTOMCENTER,MousePosition::BOTTOMRIGHT}
  };
  m_mousePositionInTermsOf012=wxPoint(x,y);
  return(mousePositionArray[y][x]);
}

void Frame::setMouseCursor(const MousePosition& mousePosition)
{
  switch(mousePosition)
  {
    case MousePosition::TOPLEFT:
    case MousePosition::BOTTOMRIGHT:
      this->SetCursor(wxCURSOR_SIZENWSE);
      break;
    case MousePosition::TOPCENTER:
    case MousePosition::BOTTOMCENTER:
      this->SetCursor(wxCURSOR_SIZENS);
      break;
    case MousePosition::TOPRIGHT:
    case MousePosition::BOTTOMLEFT:
      this->SetCursor(wxCURSOR_SIZENESW);
      break;
    case MousePosition::MIDDLELEFT:
    case MousePosition::MIDDLERIGHT:
      this->SetCursor(wxCURSOR_SIZEWE);
      break;
    default:
      this->SetCursor(wxCURSOR_DEFAULT);
      break;
  }
}

void Frame::onMouseCaptureLost(wxMouseCaptureLostEvent& event)
{
  if (HasCapture())
  {
    this->ReleaseMouse();
  }
}

