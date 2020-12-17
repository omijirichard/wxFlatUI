#pragma once

#include <wx/stattext.h>
#include <wx/timer.h>
#include <wx/event.h>
#include <wx/sizer.h>
#include <vector>
#include "custom/constants.hpp"
#include "custom/button.hpp"


namespace Custom
{


class MainBodySizer:public wxBoxSizer
{
public:
  MainBodySizer(wxWindow*);
  ~MainBodySizer();

};
}


