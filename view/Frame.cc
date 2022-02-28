#include "wx/dataview.h"
#include "wx/splitter.h"
#include "wx/textctrl.h"

#include "Frame.h"
#include "../model/FileModel.h"
#include "../parser/Parser.h"

Frame::Frame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(900, 400)) {
    // Create menu bar
    wxMenu *fileMenu = new wxMenu;

    // The "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT, wxT("&About....\tF1"),
                     wxT("Show about dialog"));
    fileMenu->Append(wxID_EXIT, wxT("&Exit\tAlt-X"),
                     wxT("Quit this program"));

    // Attach menus to menu bar
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(helpMenu, wxT("&Help"));

    // Attach menu bar to the frame
    SetMenuBar(menuBar);

    // Main UI views
    wxSplitterWindow *splitWindow = new wxSplitterWindow(this, wxID_ANY, wxPoint(0, 0), wxSize(900, 400), wxSP_3D);
    wxTextCtrl *hexView = new wxTextCtrl(splitWindow, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(400,400), wxTE_MULTILINE | wxTE_READONLY);
    wxDataViewCtrl *infoView = new wxDataViewCtrl(splitWindow, wxID_ANY, wxDefaultPosition, wxSize(400,400), wxDV_NO_HEADER);

    // Hex View Properties
    wxFont font(wxFontInfo(10).FaceName("Monospace"));
    hexView->SetDefaultStyle(wxTextAttr(wxNullColour, wxNullColour, font));
    Parser parser("/bin/ls");
    parser.populateHexView(2, hexView);

    // Info View Properties
    FileModel *fileModel = new FileModel();
    infoView->AssociateModel(fileModel);
    // column 0
    wxDataViewTextRenderer *tr = new wxDataViewTextRenderer("string", wxDATAVIEW_CELL_INERT);
    wxDataViewColumn *column0 = new wxDataViewColumn("title", tr, 0, 160, wxALIGN_LEFT);
    infoView->AppendColumn(column0);
    // column 1
    wxDataViewTextRenderer *tr2 = new wxDataViewTextRenderer( "string", wxDATAVIEW_CELL_INERT);
    wxDataViewColumn *column1 = new wxDataViewColumn("value", tr2, 1, 160, wxALIGN_LEFT);
    infoView->AppendColumn(column1);

    splitWindow->SplitVertically(hexView, infoView);
}

void Frame::OnAbout(wxCommandEvent& event) {
    wxString msg;
    msg.Printf(wxT("Hello and welcome to %s"), wxVERSION_STRING);
    wxMessageBox(msg, wxT("About Minimal"), wxOK | wxICON_INFORMATION, this);
}

void Frame::OnQuit(wxCommandEvent& event) {
    Close();
}

// Event table for Frame
BEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_MENU(wxID_ABOUT, Frame::OnAbout)
    EVT_MENU(wxID_EXIT, Frame::OnQuit)
END_EVENT_TABLE()
