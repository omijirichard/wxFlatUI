#include <wx/image.h>

#include "custom/titleBar.hpp"
#include "custom/button.hpp"
#include "custom/constants.hpp"
#include "custom/frame.hpp"
#include "custom/panel.hpp"
#include "custom/sidebar.hpp"

class MainFrame:public Frame
{
public:
  MainFrame(const wxString& title,const wxPoint& position,const wxSize& size);
  ~MainFrame();
private:
    void resizeSidebar(wxCommandEvent&);
    DECLARE_EVENT_TABLE();
private:
  Sidebar* m_sidebar;
  bool m_isSideBarExtended;
  int m_barDefaultLength;
};
