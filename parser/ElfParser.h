#pragma once

#include <string>
#include "Parser.h"

class ElfParser : public Parser {
public:
    ElfParser(std::string filename): Parser{filename} {}

private:
    void getElfHeader();
    void getElfSection();
};
