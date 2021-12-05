#include <iostream>
#include "parser.h"
#include "io.h"

using namespace std;

int main(int argc, char **argv)
{
    Parser main_parser(argc, argv);
    main_parser.Parse();

    return 0;
}