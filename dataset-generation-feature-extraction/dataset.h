#ifndef DATASET_H
#define DATASET_H

#include <vector>

using namespace std;



vector<int> generateRandom(int n);

vector<int> generateNearlySorted(int n, int swaps);

vector<int> generateReversed(int n);

vector<int> generateFewUnique(int n, int uniqueCount);

vector<int> generateLargeRandom(int n);



int getDatasetSize(vector<int>& arr);

double calculateSortedness(vector<int>& arr);

double calculateUniqueRatio(vector<int>& arr);

#endif

