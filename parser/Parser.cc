#include <fstream>
#include <sstream>
#include <iomanip>
#include "Parser.h"

using namespace std;

/*
 * Read in entire file and store bytes on the heap
 */
Parser::Parser(string filename) {
    ifstream ifh(filename, ifstream::binary);

    ifh.seekg(0, ifh.end);
    fileLength = ifh.tellg();
    ifh.seekg(0, ifh.beg);

    rawBytes = new char[fileLength];
    ifh.read(rawBytes, fileLength);
    ifh.close();
}

Parser::~Parser() {
    delete rawBytes;
}

void Parser::populateHexView(int spacing, wxTextCtrl *text) {
    ostringstream hexStream{"- offset -   0 1  2 3  4 5  6 7  8 9  A B  C D  E F", ios::ate};
    hexStream << std::hex;
    for (int i=0; i < fileLength; i++) {
        if (i % spacing == 0)
            hexStream << ' ';
        if (i % 16 == 0) {
            hexStream << '\n';
            hexStream << "0x" << setw(8) << setfill('0') << i << "  ";
        }
        int formatedByte = ((int) rawBytes[i] & 0xFF);
        hexStream << setw(2) << setfill('0') << formatedByte;
    }
    text->AppendText(hexStream.str());
}
