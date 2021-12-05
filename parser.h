#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include "caller.h"

using std::string;
using std::vector;

class Parser
{
private:
    vector<string> arguments_;
public:
    void Init(int argc, char **argv);
    Parser(int argc, char **argv);
    void Parse();
};

#endif