#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <vector>
#include <string>

using namespace std;



struct SortResult {  // Sorting algorithm performance metrics
    string algorithmName;
    long long comparisons;
    double timeMs;
    
    SortResult(string name, long long comp, double time)
        : algorithmName(name), comparisons(comp), timeMs(time) {}
};



SortResult bubbleSort(vector<int>& arr);  // O(n^2) comparison-based sort

SortResult insertionSort(vector<int>& arr);  // O(n^2) sort, efficient for small/nearly sorted arrays

SortResult mergeSort(vector<int>& arr);  // O(n log n) guaranteed, stable sort

SortResult quickSort(vector<int>& arr);  // O(n log n) average, in-place sort

#endif
