#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "File.h"

using namespace std;

/*
 * Read in entire file and store bytes on the heap
 */
File::File(std::string filename) {
    std::ifstream ifh(filename, std::ifstream::binary);

    ifh.seekg(0, ifh.end);
    File::fileLength = ifh.tellg();
    ifh.seekg(0, ifh.beg);

    File::rawBytes = new char[fileLength];
    ifh.read(rawBytes, fileLength);
    ifh.close();
}

File::~File() {
    delete File::rawBytes;
}

void File::printBytes() {
    return;
}


