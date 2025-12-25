#ifndef DATASET_H
#define DATASET_H

#include <vector>

using namespace std;

vector<int> generateRandom(int n);  // Generate random array (range: 1-10000)

vector<int> generateNearlySorted(int n, int swaps);  // Generate sorted array with random swaps

vector<int> generateReversed(int n);  // Generate reversed array [n, n-1, ..., 1]

vector<int> generateFewUnique(int n, int uniqueCount);  // Generate array with limited unique values

vector<int> generateLargeRandom(int n);  // Generate large random array (range: 1-100000)

int getDatasetSize(vector<int>& arr);  // Return array size

double calculateSortedness(vector<int>& arr);  // Calculate sortedness percentage (0-100%)

double calculateUniqueRatio(vector<int>& arr);  // Calculate ratio of unique elements (0.0-1.0)

#endif

