#pragma once

#include "wx/wx.h"

class Frame : public wxFrame {
public:
    Frame(const wxString& title);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
    DECLARE_EVENT_TABLE();
};
