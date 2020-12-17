#include "sidebar.hpp"
#include <iostream>

Sidebar::Sidebar(wxWindow* parent,const int& shrunkWidth,const int& enlargedWidth)
                                          :wxPanel(parent)
{
  m_shrunkWidth=shrunkWidth;
  m_enlargedWidth=enlargedWidth;
  m_slideTimer.SetOwner(this,static_cast<int>(SidebarID::TIMER_ID));
  wxBoxSizer* baseSizer=new wxBoxSizer(wxVERTICAL);
  baseSizer->AddSpacer(40);
  this->SetBackgroundColour(Colour::SIDEBAR_BACKGROUND);
  this->SetSizeHints(wxSize(m_shrunkWidth,-1),wxSize(m_shrunkWidth,-1));
  SidebarButton* homeButton=new SidebarButton(this,1000,"HOME",IconPath::HOME);
  homeButton->setPressed(true);
  homeButton->paint();
  SidebarButton* userButton=new SidebarButton(this,1001,"USER",IconPath::USER);
  

  m_buttonCollection.push_back(homeButton);
  m_buttonCollection.push_back(userButton);
  for (SidebarButton* button: m_buttonCollection)
  {
    button->Bind(wxEVT_COMMAND_BUTTON_CLICKED,&Sidebar::buttonClicked,this);
    baseSizer->Add(button,wxSizerFlags(1).Expand());
  }
 
  baseSizer->AddStretchSpacer();
  this->SetSizer(baseSizer);
}

BEGIN_EVENT_TABLE(Sidebar,wxPanel)
  EVT_TIMER(static_cast<int>(SidebarID::TIMER_ID),Sidebar::adjustWidth)
END_EVENT_TABLE()
void Sidebar::enlarge(const bool& isEnlarged)
{
  m_slideTimer.Start(50,wxTIMER_CONTINUOUS);
  for (SidebarButton* button:m_buttonCollection)
  {
    button->hasText=isEnlarged;
  }
  if (isEnlarged)
  {
    m_destinationWidth=m_enlargedWidth;
  }
  else
  {
    m_destinationWidth=m_shrunkWidth;
  }

}

void Sidebar::adjustWidth(wxTimerEvent& event)
{
  int currentWidth= this->GetMaxWidth();
  if (currentWidth==m_destinationWidth)
  {
    m_slideTimer.Stop();
    return;
  }
  int step =((m_destinationWidth-currentWidth)/abs(m_destinationWidth-currentWidth))*20;
  currentWidth+=step;
  currentWidth=std::clamp(currentWidth,m_shrunkWidth,m_enlargedWidth);
  this->SetMinSize(wxSize(currentWidth,-1));
  this->SetMaxSize(wxSize(currentWidth,-1));

  this->GetParent()->Update();
  this->GetParent()->Layout();
}
void Sidebar::buttonClicked(wxCommandEvent& event)
{
  //get the index and set to background colour if button is selected else
  //set it to it's normal colour
  unsigned int index=event.GetId()-1000;
  for (unsigned int i=0;i<m_buttonCollection.size();i++)
  {
    if(i==index)
    {
      m_buttonCollection[i]->setPressed(true);
    }
    else 
    {
      m_buttonCollection[i]->setPressed(false);
    }
    m_buttonCollection[i]->paint();
  }
  
}

