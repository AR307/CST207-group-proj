#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "dataset-generation-feature-extraction/dataset.h"
#include "knn_predictor.h"
#include "sorting_algorithms.h"
#include "utils.h"

using namespace std;

// ==============================================
// Display Functions
// ==============================================

void displayHeader() {
    cout << "\n========================================" << endl;
    cout << "  AI-Driven Sorting Algorithm Optimizer" << endl;
    cout << "  Using k-NN Algorithm for Prediction" << endl;
    cout << "========================================\n" << endl;
}

void displayMenu() {
    cout << "\n--- Dataset Generation Options ---" << endl;
    cout << "1. Random Array" << endl;
    cout << "2. Nearly Sorted Array" << endl;
    cout << "3. Reversed Array" << endl;
    cout << "4. Few Unique Elements Array" << endl;
    cout << "5. Large Random Array" << endl;
    cout << "0. Exit" << endl;
    cout << "\nEnter your choice: ";
}

void displayFeatures(const Features& features) {
    cout << "\n--- Dataset Features ---" << endl;
    cout << "  Size:          " << features.size << " elements" << endl;
    cout << "  Sortedness:    " << fixed << setprecision(2) << features.sortedness << "%" << endl;
    cout << "  Unique Ratio:  " << fixed << setprecision(4) << features.uniqueRatio << endl;
}

void displayPrediction(const string& prediction) {
    cout << "\n--- k-NN Prediction ---" << endl;
    cout << "  Predicted Best Algorithm: " << prediction << " Sort" << endl;
}

void displayResults(const vector<SortResult>& results, const string& prediction) {
    cout << "\n--- Sorting Performance Results ---" << endl;
    cout << left << setw(18) << "Algorithm" 
         << right << setw(15) << "Comparisons" 
         << setw(15) << "Time (ms)" 
         << setw(12) << "Predicted" << endl;
    cout << string(60, '-') << endl;
    
    // Find the fastest algorithm
    double minTime = results[0].timeMs;
    string fastestAlgo = results[0].algorithmName;
    for (const auto& result : results) {
        if (result.timeMs < minTime) {
            minTime = result.timeMs;
            fastestAlgo = result.algorithmName;
        }
    }
    
    for (const auto& result : results) {
        cout << left << setw(18) << result.algorithmName
             << right << setw(15) << result.comparisons
             << setw(15) << fixed << setprecision(3) << result.timeMs;
        
        // Mark predicted and fastest
        string predicted = (prediction + " Sort" == result.algorithmName) ? "[YES]" : "";
        string fastest = (result.algorithmName == fastestAlgo) ? " [FASTEST]" : "";
        cout << setw(12) << predicted << fastest << endl;
    }
    
    // Validation
    cout << "\n--- Prediction Validation ---" << endl;
    if (prediction + " Sort" == fastestAlgo) {
        cout << "  [OK] k-NN prediction is CORRECT! Predicted the fastest algorithm." << endl;
    } else {
        cout << "  [WARN] k-NN predicted: " << prediction << " Sort" << endl;
        cout << "  [WARN] Actual fastest: " << fastestAlgo << endl;
    }
}

// ==============================================
// Main Program
// ==============================================

int main() {
    displayHeader();
    
    // Initialize k-NN predictor
    KNNPredictor predictor(5);  // k = 5
    
    // Ask user which training data to use
    cout << "--- Training Data Options ---" << endl;
    cout << "1. Use default training data (26 hardcoded samples)" << endl;
    cout << "2. Load training data from file (recommended: ~1000 samples)" << endl;
    cout << "\nEnter your choice: ";
    
    int trainingChoice;
    cin >> trainingChoice;
    
    if (trainingChoice == 2) {
        cout << "Enter training data filename (default: training_data.csv): ";
        string filename;
        cin.ignore(); // Clear newline from previous input
        getline(cin, filename);
        
        if (filename.empty()) {
            filename = "training_data.csv";
        }
        
        cout << "Loading training data from " << filename << "..." << endl;
        if (predictor.loadTrainingDataFromFile(filename)) {
            cout << "Successfully loaded " << predictor.getTrainingDataSize() 
                 << " training samples." << endl;
        } else {
            cout << "[WARN] Failed to load file. Using default training data." << endl;
            predictor.loadDefaultTrainingData();
        }
    } else {
        predictor.loadDefaultTrainingData();
        cout << "Loaded " << predictor.getTrainingDataSize() 
             << " default training samples." << endl;
    }
    
    cout << endl;
    
    while (true) {
        displayMenu();
        
        int choice;
        cin >> choice;
        
        if (choice == 0) {
            cout << "\nThank you for using AI-Driven Sorting Optimizer!" << endl;
            break;
        }
        
        vector<int> dataset;
        int size, swaps, uniqueCount;
        
        // Generate dataset based on user choice
        switch (choice) {
            case 1:
                cout << "Enter array size: ";
                cin >> size;
                dataset = generateRandom(size);
                cout << "\nGenerated random array with " << size << " elements." << endl;
                break;
                
            case 2:
                cout << "Enter array size: ";
                cin >> size;
                cout << "Enter number of random swaps: ";
                cin >> swaps;
                dataset = generateNearlySorted(size, swaps);
                cout << "\nGenerated nearly sorted array with " << size 
                     << " elements and " << swaps << " swaps." << endl;
                break;
                
            case 3:
                cout << "Enter array size: ";
                cin >> size;
                dataset = generateReversed(size);
                cout << "\nGenerated reversed array with " << size << " elements." << endl;
                break;
                
            case 4:
                cout << "Enter array size: ";
                cin >> size;
                cout << "Enter number of unique values: ";
                cin >> uniqueCount;
                dataset = generateFewUnique(size, uniqueCount);
                cout << "\nGenerated array with " << size 
                     << " elements and " << uniqueCount << " unique values." << endl;
                break;
                
            case 5:
                cout << "Enter array size (>1000 recommended): ";
                cin >> size;
                dataset = generateLargeRandom(size);
                cout << "\nGenerated large random array with " << size << " elements." << endl;
                break;
                
            default:
                cout << "Invalid choice. Please try again." << endl;
                continue;
        }
        
        // Display sample of array (for small datasets)
        if (dataset.size() <= 100) {
            cout << "\nArray contents: ";
            printArray(dataset, 20);
        }
        
        // Extract features
        Features features(
            getDatasetSize(dataset),
            calculateSortedness(dataset),
            calculateUniqueRatio(dataset)
        );
        
        displayFeatures(features);
        
        // Use k-NN to predict best algorithm
        string prediction = predictor.predict(features);
        displayPrediction(prediction);
        
        // Test all sorting algorithms
        vector<SortResult> results;
        
        // Skip bubble and insertion for very large arrays
        bool skipSlow = dataset.size() > 1000;
        
        if (!skipSlow) {
            cout << "\nRunning Bubble Sort..." << endl;
            vector<int> arr1 = copyArray(dataset);
            results.push_back(bubbleSort(arr1));
            
            cout << "Running Insertion Sort..." << endl;
            vector<int> arr2 = copyArray(dataset);
            results.push_back(insertionSort(arr2));
        } else {
            cout << "\n[WARN] Skipping Bubble and Insertion Sort (array too large)" << endl;
        }
        
        cout << "Running Merge Sort..." << endl;
        vector<int> arr3 = copyArray(dataset);
        results.push_back(mergeSort(arr3));
        
        cout << "Running Quick Sort..." << endl;
        vector<int> arr4 = copyArray(dataset);
        results.push_back(quickSort(arr4));
        
        // Display results
        displayResults(results, prediction);
    }
    
    return 0;
}
