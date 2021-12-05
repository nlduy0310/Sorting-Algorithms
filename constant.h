#ifndef CONSTANT_H_
#define CONSTANT_H_

#include <vector>
#include <string>

using std::string;
using std::vector;

const vector<string> kAlgorithmNames = {
    "selection-sort",
    "insertion-sort",
    "bubble-sort",
    "shaker-sort",
    "shell-sort",
    "heap-sort",
    "merge-sort",
    "quick-sort",
    "counting-sort",
    "radix-sort",
    "flash-sort"
};

const vector<string> kInputOrders = {
    "-rand",
    "-sorted",
    "-rev",
    "-nsorted"
};

const vector<string> kOutputParams = {
    "-time",
    "-comp",
    "-both"
};

#endif