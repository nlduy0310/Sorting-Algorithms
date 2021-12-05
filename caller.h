#ifndef CALLER_H_
#define CALLER_H_

#include <string>
#include "sort.h"
#include "constant.h"

using std::string;

typedef void (*FunctionPointer)(int[], int, unsigned long long &);

const FunctionPointer kAlgorithmList[] = {
    &SelectionSort,
    &InsertionSort,
    &BubbleSort,
    &ShakerSort,
    &ShellSort,
    &HeapSort,
    &MergeSort,
    &QuickSort,
    &CountingSort,
    &RadixSort,
    &FlashSort
};

class FunctionCaller
{
public:
    static bool Find(string algo_name);
    static bool Run(string algo_name, int array[], int size, unsigned long long &);
};

#endif