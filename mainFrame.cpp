#include "mainFrame.hpp"



MainFrame::MainFrame(const wxString& title,const wxPoint& position,const wxSize& size): Frame(title,position,size)
{
  int titleBarHeight=40;
  m_barDefaultLength=titleBarHeight+10;
  //top bar sizer
  wxBoxSizer* topBarSizer=new wxBoxSizer(wxHORIZONTAL);
  Button* menuButton=new Button(this,100,"",IconPath::MENU);
  menuButton->SetSizeHints(wxSize(m_barDefaultLength,titleBarHeight),wxSize(m_barDefaultLength,titleBarHeight));
  TitleBar* titleBar=new TitleBar(this,"Transpha",titleBarHeight-10,titleBarHeight);
  titleBar->minimizedTitle="Transpha";
  topBarSizer->Add(menuButton,wxSizerFlags(1).Expand().Align(wxALIGN_TOP));
  topBarSizer->Add(titleBar,wxSizerFlags(1).Expand().Align(wxALIGN_TOP));
  
  //body sizer
  wxBoxSizer* bodySizer=new wxBoxSizer(wxHORIZONTAL);
  m_sidebar=new Sidebar(this,m_barDefaultLength);
  m_sidebar->SetSizeHints(wxSize(m_barDefaultLength,-1),wxSize(m_barDefaultLength,-1));
  bodySizer->Add(m_sidebar,wxSizerFlags().Expand());
  Panel* mainPanel=new Panel(this,wxID_ANY,20);
  mainPanel->SetSizeHints(-1,-1);
  bodySizer->Add(mainPanel,wxSizerFlags(1).Expand().Border(wxALL,5));
  
  //main sizer that holds the topBar sizer and body sizer
  wxBoxSizer* mainBoxSizer=new wxBoxSizer(wxVERTICAL);
  mainBoxSizer->Add(topBarSizer,wxSizerFlags().Expand().Align(wxALIGN_TOP));
  mainBoxSizer->Add(bodySizer,wxSizerFlags(1).Expand());
  //wrapping sizer holds the main sizer and gives it a border in the mainframe
  wxBoxSizer* wrappingSizer=new wxBoxSizer(wxHORIZONTAL);
  wrappingSizer->Add(mainBoxSizer,wxSizerFlags(1).Expand().Border(wxALL, 1));
  this->SetSizer(wrappingSizer);
  
  this->Layout();  
}

BEGIN_EVENT_TABLE(MainFrame,Frame)
  EVT_BUTTON(100,MainFrame::resizeSidebar)
END_EVENT_TABLE()
void MainFrame::resizeSidebar(wxCommandEvent& event)
{
  if (!m_isSideBarExtended)
  {
    m_isSideBarExtended=true;
    m_sidebar->enlarge(true);
  }
  else
  {
    m_isSideBarExtended=false;
    m_sidebar->enlarge(false);
  }
  this->Layout();
}

MainFrame::~MainFrame()
{
  
}