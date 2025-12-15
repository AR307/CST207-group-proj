#ifndef DATASET_H
#define DATASET_H

#include <vector>

using namespace std;

// ==============================================
// Data Generation Functions
// ==============================================

// Generate random array of size n (range: 1-10000)
vector<int> generateRandom(int n);

// Generate nearly sorted array with some random swaps
vector<int> generateNearlySorted(int n, int swaps);

// Generate reversed array [n, n-1, ..., 2, 1]
vector<int> generateReversed(int n);

// Generate array with few unique values (lots of duplicates)
vector<int> generateFewUnique(int n, int uniqueCount);

// Generate large random array (range: 1-100000)
vector<int> generateLargeRandom(int n);

// ==============================================
// Feature Extraction Functions
// ==============================================

// Get array size
int getDatasetSize(vector<int>& arr);

// Calculate how sorted the array is (0-100%)
double calculateSortedness(vector<int>& arr);

// Calculate ratio of unique elements (0.0-1.0)
double calculateUniqueRatio(vector<int>& arr);

#endif

