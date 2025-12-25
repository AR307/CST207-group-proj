#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

using namespace std;



void printArray(const vector<int>& arr, int maxElements = 20);  // Display array contents with truncation

vector<int> copyArray(const vector<int>& arr);  // Create a copy of array

bool isSorted(const vector<int>& arr);  // Check if array is sorted in ascending order

#endif
