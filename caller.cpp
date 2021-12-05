#include "caller.h"
#include <algorithm>
#include <vector>

using namespace std;

bool FunctionCaller::Find(string algo_name) 
{
    if (find(kAlgorithmNames.begin(), kAlgorithmNames.end(), algo_name) != kAlgorithmNames.end())
        return true;

    return false;
}

bool FunctionCaller::Run(string algo_name, int array[], int size, unsigned long long &comparisions_count)
{
    vector<string>::const_iterator cit = find(kAlgorithmNames.begin(), kAlgorithmNames.end(), algo_name);

    if (cit != kAlgorithmNames.end())
    {
        int index = (int)(cit - kAlgorithmNames.begin());
        (*kAlgorithmList[index])(array, size, comparisions_count);
    }
    else
        return false;

    return true;
}