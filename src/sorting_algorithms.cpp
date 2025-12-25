#include "../include/sorting_algorithms.h"
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;



void merge(vector<int>& arr, int left, int mid, int right, long long& comparisons) {  // Merge two sorted subarrays
    // Calculate sizes of two subarrays to be merged
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays for left and right subarrays
    vector<int> L(n1), R(n2);
    
    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    
    // Compare elements from both arrays and place smaller one in result
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
    
    // Copy any remaining elements from left array
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy any remaining elements from right array
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortHelper(vector<int>& arr, int left, int right, long long& comparisons) {  // Recursive merge sort implementation
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSortHelper(arr, left, mid, comparisons);
        mergeSortHelper(arr, mid + 1, right, comparisons);
        merge(arr, left, mid, right, comparisons);
    }
}



int partition(vector<int>& arr, int low, int high, long long& comparisons) {  // Partition array for quicksort
    int pivot = arr[high];  // Choose rightmost element as pivot
    int i = low - 1;  // Index of smaller element
    
    // Move elements smaller than pivot to left side
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    // Place pivot in correct position
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int low, int high, long long& comparisons) {  // Recursive quicksort implementation
    if (low < high) {
        int pi = partition(arr, low, high, comparisons);
        quickSortHelper(arr, low, pi - 1, comparisons);
        quickSortHelper(arr, pi + 1, high, comparisons);
    }
}



SortResult bubbleSort(vector<int>& arr) {  // Bubble sort with optimization
    auto start = high_resolution_clock::now();
    long long comparisons = 0;
    
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;  // Track if any swaps occurred
        // Compare adjacent elements and swap if needed
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // Early termination: if no swaps, array is sorted
        if (!swapped) break;
    }
    
    auto end = high_resolution_clock::now();
    double timeMs = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    return SortResult("Bubble Sort", comparisons, timeMs);
}



SortResult insertionSort(vector<int>& arr) {  // Insertion sort implementation
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



SortResult mergeSort(vector<int>& arr) {  // Merge sort driver function
    auto start = high_resolution_clock::now();
    long long comparisons = 0;
    
    if (arr.size() > 1) {
        mergeSortHelper(arr, 0, arr.size() - 1, comparisons);
    }
    
    auto end = high_resolution_clock::now();
    double timeMs = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    return SortResult("Merge Sort", comparisons, timeMs);
}



SortResult quickSort(vector<int>& arr) {  // Quicksort driver function
    auto start = high_resolution_clock::now();
    long long comparisons = 0;
    
    if (arr.size() > 1) {
        quickSortHelper(arr, 0, arr.size() - 1, comparisons);
    }
    
    auto end = high_resolution_clock::now();
    double timeMs = duration_cast<microseconds>(end - start).count() / 1000.0;
    
    return SortResult("Quick Sort", comparisons, timeMs);
}
