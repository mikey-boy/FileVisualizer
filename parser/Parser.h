#pragma once

#include <string>
#include "wx/textctrl.h"

class Parser {
private:
    char * rawBytes;
    int fileLength;

public:
    Parser(std::string filename);
    virtual ~Parser();
    void populateHexView(int spacing, wxTextCtrl *text);
};
