#pragma once
#include <wx/app.h>
#include "mainFrame.hpp"

class App: public wxApp
{
public:
    virtual bool OnInit();
private:
  wxString m_title="Transpha";
  MainFrame* m_Frame=nullptr;
};