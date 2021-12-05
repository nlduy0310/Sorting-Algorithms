#ifndef IO_H_
#define IO_H_

#include <string>

using std::string;

class Exporter
{
public:
    static bool Export(string file_path, int array[], int size, int mode);
};

class Reader
{
public:
    static bool Read(string file_path, int *&array, int &size);
};

#endif