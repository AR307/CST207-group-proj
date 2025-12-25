#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

using namespace std;



void printArray(const vector<int>& arr, int maxElements = 20);

vector<int> copyArray(const vector<int>& arr);

bool isSorted(const vector<int>& arr);

#endif
