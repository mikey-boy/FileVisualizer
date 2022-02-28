#pragma once

#include "wx/wx.h"
#include "Frame.h"

class Application : public wxApp {
public:
    // Called on Application startup
    virtual bool OnInit();
};
