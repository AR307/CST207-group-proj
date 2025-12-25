#include "dataset.h"
#include <algorithm>
#include <random>
#include <set>

using namespace std;



vector<int> generateRandom(int n) {
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);
    
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

vector<int> generateNearlySorted(int n, int swaps) {
    vector<int> arr(n);
    
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    

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

vector<int> generateReversed(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    return arr;
}

vector<int> generateFewUnique(int n, int uniqueCount) {
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, uniqueCount);
    
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}

vector<int> generateLargeRandom(int n) {
    vector<int> arr(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100000);
    
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
    return arr;
}



int getDatasetSize(vector<int>& arr) {
    return arr.size();
}

double calculateSortedness(vector<int>& arr) {
    if (arr.size() <= 1) {
        return 100.0;
    }
    
    int orderedPairs = 0;
    for (size_t i = 0; i < arr.size() - 1; i++) {
        if (arr[i] <= arr[i + 1]) {
            orderedPairs++;
        }
    }
    
    return (orderedPairs * 100.0) / (arr.size() - 1);
}

double calculateUniqueRatio(vector<int>& arr) {
    if (arr.empty()) {
        return 0.0;
    }
    
    set<int> uniqueElements(arr.begin(), arr.end());
    return (double)uniqueElements.size() / arr.size();
}

