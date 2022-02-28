#include <string>

class File {
private:
    char * rawBytes;
    int fileLength;

public:
    File(std::string filename);
    ~File();
    void printBytes();
};
