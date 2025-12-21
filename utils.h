#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

using namespace std;

// ==============================================
// Utility Functions
// ==============================================

// Print array contents (limit to first 20 elements for large arrays)
void printArray(const vector<int>& arr, int maxElements = 20);

// Create a copy of an array
vector<int> copyArray(const vector<int>& arr);

// Check if array is sorted
bool isSorted(const vector<int>& arr);

#endif
