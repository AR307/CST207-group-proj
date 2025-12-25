#include "sorting_algorithms.h"
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;



void merge(vector<int>& arr, int left, int mid, int right, long long& comparisons) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    

    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortHelper(vector<int>& arr, int left, int right, long long& comparisons) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSortHelper(arr, left, mid, comparisons);
        mergeSortHelper(arr, mid + 1, right, comparisons);
        merge(arr, left, mid, right, comparisons);
    }
}



int partition(vector<int>& arr, int low, int high, long long& comparisons) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int low, int high, long long& comparisons) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisons);
        quickSortHelper(arr, low, pi - 1, comparisons);
        quickSortHelper(arr, pi + 1, high, comparisons);
    }
}



SortResult bubbleSort(vector<int>& arr) {
    auto start = high_resolution_clock::now();
    long long comparisons = 0;
    
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    
    auto end = high_resolution_clock::now();
    double timeMs = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    return SortResult("Bubble Sort", comparisons, timeMs);
}



SortResult insertionSort(vector<int>& arr) {
    auto start = high_resolution_clock::now();
    long long comparisons = 0;
    
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0) {
            comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
    
    auto end = high_resolution_clock::now();
    double timeMs = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    return SortResult("Insertion Sort", comparisons, timeMs);
}



SortResult mergeSort(vector<int>& arr) {
    auto start = high_resolution_clock::now();
    long long comparisons = 0;
    
    if (arr.size() > 1) {
        mergeSortHelper(arr, 0, arr.size() - 1, comparisons);
    }
    
    auto end = high_resolution_clock::now();
    double timeMs = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    return SortResult("Merge Sort", comparisons, timeMs);
}



SortResult quickSort(vector<int>& arr) {
    auto start = high_resolution_clock::now();
    long long comparisons = 0;
    
    if (arr.size() > 1) {
        quickSortHelper(arr, 0, arr.size() - 1, comparisons);
    }
    
    auto end = high_resolution_clock::now();
    double timeMs = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    return SortResult("Quick Sort", comparisons, timeMs);
}
