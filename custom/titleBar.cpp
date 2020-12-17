
#include "titleBar.hpp"

TitleBar::TitleBar(wxTopLevelWindow* parent,const wxString& title,
                          const int& minHeight,const int& maxHeight)
    :wxPanel(parent)
{
  this->SetBackgroundColour(Colour::TITLEBAR);
  this->parent=parent;
  this->title=title;
  this->minimizedTitle=title;
  this->SetSizeHints(wxSize(-1,minHeight),wxSize(-1,maxHeight));
  m_minimizeButton=new Button(this,1001,"",IconPath::WINDOW_MINIMIZE);
  m_maximizeButton=new Button(this,1002,"",IconPath::WINDOW_MAXIMIZE);
  m_closeButton   =new Button(this,1003,"",IconPath::WINDOW_CLOSE);

  m_minimizeButton->SetSizeHints(wxSize(minHeight-10,-1),wxSize(maxHeight-5,-1));
  m_maximizeButton->SetSizeHints(wxSize(minHeight-10,-1),wxSize(maxHeight-5,-1));
  m_closeButton   ->SetSizeHints(wxSize(minHeight-10,-1),wxSize(maxHeight-5,-1));
  wxBoxSizer* boxSizer=new wxBoxSizer(wxHORIZONTAL);
  m_titleText=new wxStaticText(this,this->GetId(),title,wxDefaultPosition,wxDefaultSize,wxALIGN_CENTER_VERTICAL);
  m_titleText->SetFont(wxFont(wxFontInfo(15).FaceName("Helvetica").Bold()));
  m_titleText->SetForegroundColour(wxColour(Colour::TEXT_COLOUR));
  m_titleText->SetMinSize(wxSize(-1,minHeight));
  m_titleText->SetMaxSize(wxSize(-1,maxHeight));
  boxSizer->Add(m_titleText,wxSizerFlags(0).Bottom().Border(wxALL,2));
  boxSizer->AddStretchSpacer();
  boxSizer->Add(m_minimizeButton,wxSizerFlags(1).Expand().Align(wxTOP));
  boxSizer->Add(m_maximizeButton,wxSizerFlags(1).Expand().Align(wxTOP));
  boxSizer->Add(m_closeButton,wxSizerFlags(1).Expand().Align(wxTOP));

  this->SetSizerAndFit(boxSizer);
  this->Layout();
}

//event table for title bar
BEGIN_EVENT_TABLE(TitleBar,wxPanel)
  EVT_MOUSE_EVENTS(TitleBar::onMouseEvent)
  EVT_BUTTON(1001,TitleBar::minimize)
  EVT_BUTTON(1002,TitleBar::maximize<wxCommandEvent>)
  EVT_BUTTON(1003,TitleBar::close)
END_EVENT_TABLE()
void TitleBar::minimize(wxCommandEvent& event)
{
  parent->Iconize(true);
  event.Skip();
}

template<typename eventType>
void TitleBar::maximize(eventType& event)
{
  if (parent->IsMaximized())
  {
    parent->Maximize(false);
    m_titleText->SetLabel(minimizedTitle);
    m_maximizeButton->setIconPath(IconPath::WINDOW_MAXIMIZE);
  }
  else
  {

    m_maximizeButton->setIconPath(IconPath::WINDOW_RESTORE);
    parent->Maximize();
    m_titleText->SetLabel(title);
  }
  parent->Update();
  event.Skip();
}


void TitleBar::close(wxCommandEvent& event)
{
  parent->Close();
  event.Skip();
}

void TitleBar::onMouseEvent(wxMouseEvent& event)
{

  //if mouse is being dragged and the left mouse button is clicked
  //move the app window
  if (event.Moving())
  {
    parent->SetCursor(wxCURSOR_DEFAULT);
  }
  else if (event.Dragging() )
  {
    parent->SetCursor(wxCURSOR_HAND);
    //move the parent window
    wxPoint mousePosition=ClientToScreen(event.GetPosition());
    wxPoint destinationPosition=wxPoint(mousePosition.x-m_deltaPosition.x
                                        ,mousePosition.y-m_deltaPosition.y);
    parent->Move(destinationPosition);
  }
  else if(event.LeftDClick())
  {
    maximize<wxMouseEvent>(event);
  }
  else if (event.LeftIsDown()&&!m_mouseDragHasStarted)
  {

    m_mouseDragHasStarted=false;
    wxPoint mousePosition=ClientToScreen(event.GetPosition());
    wxPoint windowOrigin=parent->GetPosition();
    int dx=mousePosition.x-windowOrigin.x;
    int dy=mousePosition.y-windowOrigin.y;
    m_deltaPosition=wxPoint(dx,dy);
    
  }
  else if(event.LeftUp())
  {
    m_mouseDragHasStarted=false;
    parent->SetCursor(wxCURSOR_DEFAULT);
  }

  else
  {
    event.Skip();
  }
}


TitleBar::~TitleBar()
{

}