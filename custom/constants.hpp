#pragma once
#include <wx/colour.h>
#include <wx/string.h>

namespace Colour
{
  const wxColour LIGHT_PURPLE      =wxColour(49, 46, 75);
  const wxColour PURPLE            =wxColour(39, 36, 65);
  const wxColour DARK_PURPLE       =wxColour(29, 25, 50);
  const wxColour BACKGROUND        =wxColour(38,86,114);
  const wxColour TITLEBAR          =wxColour(13,48,68);
  const wxColour SIDEBAR_BACKGROUND=wxColour(13,48,68);
  const wxColour BUTTON_IDLE       =TITLEBAR;
  const wxColour BUTTON_PRESSED    =wxColour(43,78,98);
  const wxColour BUTTON_HOVER      =wxColour(23,58,78);
  const wxColour TEXT_COLOUR       =wxColour(200,200,200);
  const wxColour ICON_IDLE         =wxColour(250,250,250);
  const wxColour ICON_PRESSSED     =wxColour(49, 46, 75);
  const wxColour PANEL_COLOUR      =wxColour(23,58,78);
}
namespace IconPath
{
  const wxString WINDOW_MINIMIZE="resources/icons/window-minimize.png";
  const wxString WINDOW_MAXIMIZE="resources/icons/window-maximize.png";
  const wxString WINDOW_RESTORE ="resources/icons/window-restore.png";
  const wxString WINDOW_CLOSE   ="resources/icons/x.png";
  const wxString MENU           ="resources/icons/menu.png";
  const wxString HOME           ="resources/icons/home.png";
  const wxString USER           ="resources/icons/user.png";
}
