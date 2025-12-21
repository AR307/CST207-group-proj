#include "utils.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

// ==============================================
// Print Array
// ==============================================

void printArray(const vector<int>& arr, int maxElements) {
    if (arr.empty()) {
        cout << "(empty array)" << endl;
        return;
    }
    
    int displayCount = min(maxElements, (int)arr.size());
    
    cout << "[";
    for (int i = 0; i < displayCount; i++) {
        cout << arr[i];
        if (i < displayCount - 1) cout << ", ";
    }
    
    if ((int)arr.size() > maxElements) {
        cout << ", ... (" << arr.size() - maxElements << " more)";
    }
    cout << "]" << endl;
}

// ==============================================
// Copy Array
// ==============================================

vector<int> copyArray(const vector<int>& arr) {
    return vector<int>(arr);
}

// ==============================================
// Check if Sorted
// ==============================================

bool isSorted(const vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}
