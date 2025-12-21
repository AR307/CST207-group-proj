#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <vector>
#include <string>

using namespace std;

// ==============================================
// Sort Result Structure
// ==============================================

struct SortResult {
    string algorithmName;
    long long comparisons;  // Number of comparisons made
    double timeMs;          // Execution time in milliseconds
    
    SortResult(string name, long long comp, double time)
        : algorithmName(name), comparisons(comp), timeMs(time) {}
};

// ==============================================
// Sorting Algorithm Functions
// ==============================================

// Bubble Sort - O(n^2)
// Best for: Very small datasets or educational purposes
SortResult bubbleSort(vector<int>& arr);

// Insertion Sort - O(n^2) average, O(n) best case
// Best for: Small datasets or nearly sorted data
SortResult insertionSort(vector<int>& arr);

// Merge Sort - O(n log n) guaranteed
// Best for: Large datasets, reversed arrays, stability needed
SortResult mergeSort(vector<int>& arr);

// Quick Sort - O(n log n) average, O(n^2) worst case
// Best for: Large random datasets, general purpose
SortResult quickSort(vector<int>& arr);

#endif
