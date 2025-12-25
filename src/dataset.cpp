#include "../include/dataset.h"
#include <algorithm>
#include <random>
#include <set>

using namespace std;

vector<int> generateRandom(int n) {  // Generate random integers in range [1, 10000]
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);
    
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

vector<int> generateNearlySorted(int n, int swaps) {  // Create sorted array then perform random swaps
    vector<int> arr(n);
    
    // Start with perfectly sorted array [1, 2, 3, ..., n]
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    
    // Perform random swaps to introduce disorder
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, n - 1);
    
    for (int i = 0; i < swaps; i++) {
        int idx1 = dis(gen);
        int idx2 = dis(gen);
        swap(arr[idx1], arr[idx2]);
    }
    
    return arr;
}

vector<int> generateReversed(int n) {  // Generate descending sequence
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    return arr;
}

vector<int> generateFewUnique(int n, int uniqueCount) {  // Generate array with limited unique values
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, uniqueCount);
    
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

vector<int> generateLargeRandom(int n) {  // Generate large random integers in range [1, 100000]
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000);
    
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

int getDatasetSize(vector<int>& arr) {  // Return number of elements
    return arr.size();
}

double calculateSortedness(vector<int>& arr) {  // Calculate percentage of ordered adjacent pairs
    if (arr.size() <= 1) {
        return 100.0;  // Single element or empty is perfectly sorted
    }
    
    // Count adjacent pairs that are in correct order
    int orderedPairs = 0;
    for (size_t i = 0; i < arr.size() - 1; i++) {
        if (arr[i] <= arr[i + 1]) {
            orderedPairs++;
        }
    }
    
    // Return percentage: (ordered pairs / total pairs) * 100
    return (orderedPairs * 100.0) / (arr.size() - 1);
}

double calculateUniqueRatio(vector<int>& arr) {  // Calculate ratio of unique to total elements
    if (arr.empty()) {
        return 0.0;
    }
    
    // Use set to automatically count unique elements
    set<int> uniqueElements(arr.begin(), arr.end());
    return (double)uniqueElements.size() / arr.size();
}

