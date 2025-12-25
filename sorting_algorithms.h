#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <vector>
#include <string>

using namespace std;



struct SortResult {
    string algorithmName;
    long long comparisons;
    double timeMs;
    
    SortResult(string name, long long comp, double time)
        : algorithmName(name), comparisons(comp), timeMs(time) {}
};



SortResult bubbleSort(vector<int>& arr);

SortResult insertionSort(vector<int>& arr);

SortResult mergeSort(vector<int>& arr);

SortResult quickSort(vector<int>& arr);

#endif
