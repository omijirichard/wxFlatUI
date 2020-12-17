
#include "app.hpp"

IMPLEMENT_APP(App)
bool App::OnInit()
{
  wxImage::AddHandler(new wxPNGHandler);
    m_Frame=new MainFrame
    (m_title,wxPoint(100,100),wxSize(-1,-1));
    m_Frame->SetMinSize(wxSize(400,300));
    m_Frame->Center();
    m_Frame->Maximize(true);
    m_Frame->Show(true);
    return true;

}

