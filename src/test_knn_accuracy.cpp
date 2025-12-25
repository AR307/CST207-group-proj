#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <random>
#include "../include/dataset.h"
#include "../include/knn_predictor.h"
#include "../include/sorting_algorithms.h"

using namespace std;

random_device rd;
mt19937 gen(rd());

// Test case structure
struct TestCase {
    vector<int> array;
    Features features = Features(0, 0.0, 0.0);  // Initialize with default values
    string datasetType;
};

// Generate 1000 test arrays (250 per type)
vector<TestCase> generateTestCases() {  // Generate diverse test arrays
    vector<TestCase> testCases;
    
    uniform_int_distribution<> smallSize(10, 500);
    uniform_int_distribution<> mediumSize(100, 2000);
    uniform_int_distribution<> swapsDist(5, 50);
    uniform_int_distribution<> uniqueDist(2, 50);
    
    // Type 1: Random arrays (250)
    for (int i = 0; i < 250; i++) {
        TestCase tc;
        int size = (i < 125) ? smallSize(gen) : mediumSize(gen);
        tc.array = generateRandom(size);
        tc.features = Features(
            getDatasetSize(tc.array),
            calculateSortedness(tc.array),
            calculateUniqueRatio(tc.array)
        );
        tc.datasetType = "Random";
        testCases.push_back(tc);
    }
    
    // Type 2: Nearly Sorted (250)
    for (int i = 0; i < 250; i++) {
        TestCase tc;
        int size = (i < 25) ? smallSize(gen) : mediumSize(gen);
        int swaps = swapsDist(gen);
        tc.array = generateNearlySorted(size, swaps);
        tc.features = Features(
            getDatasetSize(tc.array),
            calculateSortedness(tc.array),
            calculateUniqueRatio(tc.array)
        );
        tc.datasetType = "Nearly Sorted";
        testCases.push_back(tc);
    }
    
    // Type 3: Reversed (250)
    for (int i = 0; i < 250; i++) {
        TestCase tc;
        int size = (i < 25) ? smallSize(gen) : mediumSize(gen);
        tc.array = generateReversed(size);
        tc.features = Features(
            getDatasetSize(tc.array),
            calculateSortedness(tc.array),
            calculateUniqueRatio(tc.array)
        );
        tc.datasetType = "Reversed";
        testCases.push_back(tc);
    }
    
    // Type 4: Few Unique (250)
    for (int i = 0; i < 250; i++) {
        TestCase tc;
        int size = (i < 25) ? smallSize(gen) : mediumSize(gen);
        int uniques = uniqueDist(gen);
        tc.array = generateFewUnique(size, uniques);
        tc.features = Features(
            getDatasetSize(tc.array),
            calculateSortedness(tc.array),
            calculateUniqueRatio(tc.array)
        );
        tc.datasetType = "Few Unique";
        testCases.push_back(tc);
    }
    
    return testCases;
}

// Find actual best algorithm by testing
string findActualBest(vector<int>& arr) {  // Test all algorithms and return fastest
    vector<SortResult> results;
    bool skipSlow = arr.size() > 1000;
    
    // Test algorithms (skip slow ones for large arrays)
    if (!skipSlow) {
        vector<int> arr1 = arr;
        results.push_back(bubbleSort(arr1));
        
        vector<int> arr2 = arr;
        results.push_back(insertionSort(arr2));
    }
    
    vector<int> arr3 = arr;
    results.push_back(mergeSort(arr3));
    
    vector<int> arr4 = arr;
    results.push_back(quickSort(arr4));
    
    // Find fastest
    string fastest = results[0].algorithmName;
    double minTime = results[0].timeMs;
    for (const auto& result : results) {
        if (result.timeMs < minTime) {
            minTime = result.timeMs;
            fastest = result.algorithmName;
        }
    }
    
    // Extract algorithm name without " Sort"
    size_t pos = fastest.find(" Sort");
    if (pos != string::npos) {
        fastest = fastest.substr(0, pos);
    }
    
    return fastest;
}

// Test k-NN accuracy with given predictor
void testAccuracy(KNNPredictor& predictor, const string& testName, const vector<TestCase>& testCases) {
    cout << "\n========================================" << endl;
    cout << "Test: " << testName << endl;
    cout << "========================================" << endl;
    
    int correct = 0;
    map<string, map<string, int>> confusionMatrix;
    map<string, int> correctByType;
    map<string, int> totalByType;
    
    // Initialize confusion matrix
    vector<string> algorithms = {"Bubble", "Insertion", "Merge", "Quick"};
    for (const auto& actual : algorithms) {
        for (const auto& pred : algorithms) {
            confusionMatrix[actual][pred] = 0;
        }
    }
    
    // Test each case
    cout << "\nTesting " << testCases.size() << " arrays..." << endl;
    int processed = 0;
    
    for (const auto& tc : testCases) {
        string predicted = predictor.predict(tc.features);
        string actual = findActualBest(const_cast<vector<int>&>(tc.array));
        
        // Update counters
        if (predicted == actual) {
            correct++;
            correctByType[tc.datasetType]++;
        }
        totalByType[tc.datasetType]++;
        
        confusionMatrix[actual][predicted]++;
        
        // Progress indicator
        processed++;
        if (processed % 100 == 0) {
            cout << "  Processed: " << processed << "/" << testCases.size() << endl;
        }
    }
    
    // Display results
    cout << "\n----------------------------------------" << endl;
    cout << "Overall Results" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Correct predictions: " << correct << "/" << testCases.size() << endl;
    cout << "Accuracy: " << fixed << setprecision(1) 
         << (100.0 * correct / testCases.size()) << "%" << endl;
    
    // Accuracy by dataset type
    cout << "\n----------------------------------------" << endl;
    cout << "Accuracy by Dataset Type" << endl;
    cout << "----------------------------------------" << endl;
    for (const auto& pair : totalByType) {
        string type = pair.first;
        int total = pair.second;
        int corr = correctByType[type];
        cout << left << setw(15) << type << ": " 
             << corr << "/" << total << " = "
             << fixed << setprecision(1) << (100.0 * corr / total) << "%" << endl;
    }
    
    // Confusion Matrix
    cout << "\n----------------------------------------" << endl;
    cout << "Confusion Matrix" << endl;
    cout << "----------------------------------------" << endl;
    cout << "              Predicted Algorithm" << endl;
    cout << "         ";
    for (const auto& algo : algorithms) {
        cout << setw(10) << algo;
    }
    cout << endl;
    
    for (const auto& actual : algorithms) {
        cout << "Actual " << setw(10) << left << actual;
        for (const auto& pred : algorithms) {
            cout << setw(10) << right << confusionMatrix[actual][pred];
        }
        cout << endl;
    }
}

int main() {  // Test k-NN accuracy with built-in and external data
    cout << "========================================" << endl;
    cout << "  k-NN Prediction Accuracy Test" << endl;
    cout << "========================================" << endl;
    
    // Generate test cases
    cout << "\nGenerating 1000 test arrays..." << endl;
    cout << "  - Random: 250" << endl;
    cout << "  - Nearly Sorted: 250" << endl;
    cout << "  - Reversed: 250" << endl;
    cout << "  - Few Unique: 250" << endl;
    
    vector<TestCase> testCases = generateTestCases();
    cout << "\nGenerated " << testCases.size() << " test arrays successfully." << endl;
    
    // Test 1: Built-in training data (26 samples)
    KNNPredictor knn1(5);
    knn1.loadDefaultTrainingData();
    cout << "\nLoaded built-in training data: " << knn1.getTrainingDataSize() << " samples" << endl;
    testAccuracy(knn1, "Built-in Training Data (26 samples)", testCases);
    
    // Test 2: External training data from CSV
    KNNPredictor knn2(5);
    if (knn2.loadTrainingDataFromFile("training_data.csv")) {
        cout << "\n\nLoaded external training data: " << knn2.getTrainingDataSize() << " samples" << endl;
        testAccuracy(knn2, "External Training Data (from CSV)", testCases);
    } else {
        cout << "\n[ERROR] Failed to load training_data.csv" << endl;
        cout << "Skipping external data test." << endl;
    }
    
    cout << "\n========================================" << endl;
    cout << "Test Complete" << endl;
    cout << "========================================" << endl;
    
    return 0;
}
