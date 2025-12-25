#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
#include <ctime>
#include "dataset-generation-feature-extraction/dataset.h"
#include "sorting_algorithms.h"

using namespace std;


random_device rd;
mt19937 gen(rd());



enum DatasetType {
    TYPE_RANDOM,
    TYPE_NEARLY_SORTED,
    TYPE_REVERSED,
    TYPE_FEW_UNIQUE,
    TYPE_LARGE_RANDOM
};

const char* getTypeName(DatasetType type) {
    switch(type) {
        case TYPE_RANDOM: return "Random";
        case TYPE_NEARLY_SORTED: return "NearlySorted";
        case TYPE_REVERSED: return "Reversed";
        case TYPE_FEW_UNIQUE: return "FewUnique";
        case TYPE_LARGE_RANDOM: return "LargeRandom";
        default: return "Unknown";
    }
}



vector<int> generateByType(DatasetType type, int sampleIndex, int totalSamplesPerType) {
    vector<int> dataset;
    

    uniform_int_distribution<> smallSize(10, 500);
    uniform_int_distribution<> mediumSize(100, 2000);
    uniform_int_distribution<> largeSize(500, 5000);
    uniform_int_distribution<> swapsSmall(1, 10);
    uniform_int_distribution<> swapsMedium(5, 50);
    uniform_int_distribution<> uniqueCount(2, 50);
    
        case TYPE_RANDOM: {
            int size;
            if (sampleIndex < totalSamplesPerType / 3) {
                size = smallSize(gen);
            } else if (sampleIndex < 2 * totalSamplesPerType / 3) {
                size = mediumSize(gen);
            } else {
                size = largeSize(gen);
            }
            dataset = generateRandom(size);
            break;
        }
        case TYPE_NEARLY_SORTED: {
            int size;
            int swaps;
            if (sampleIndex < totalSamplesPerType / 3) {
                size = smallSize(gen);
                swaps = swapsSmall(gen);
            } else if (sampleIndex < 2 * totalSamplesPerType / 3) {
                size = mediumSize(gen);
                swaps = swapsMedium(gen);
            } else {
                size = largeSize(gen);
                swaps = swapsMedium(gen) * 2;
            }
            dataset = generateNearlySorted(size, swaps);
            break;
        }
        case TYPE_REVERSED: {
            int size;
            if (sampleIndex < totalSamplesPerType / 3) {
                size = smallSize(gen);
            } else if (sampleIndex < 2 * totalSamplesPerType / 3) {
                size = mediumSize(gen);
            } else {
                size = largeSize(gen);
            }
            dataset = generateReversed(size);
            break;
        }
        case TYPE_FEW_UNIQUE: {
            int size;
            int uniques;
            if (sampleIndex < totalSamplesPerType / 3) {
                size = smallSize(gen);
                uniques = uniqueCount(gen) / 5 + 2;
            } else if (sampleIndex < 2 * totalSamplesPerType / 3) {
                size = mediumSize(gen);
                uniques = uniqueCount(gen);
            } else {
                size = largeSize(gen);
                uniques = uniqueCount(gen) * 2;
            }
            uniques = max(2, min(uniques, size));
            dataset = generateFewUnique(size, uniques);
            break;
        }
        case TYPE_LARGE_RANDOM: {
            uniform_int_distribution<> veryLargeSize(1000, 10000);
            int size = veryLargeSize(gen);
            dataset = generateLargeRandom(size);
            break;
        }
    }
    
    return dataset;
}



struct TestResult {
    string algorithm;
    double timeMs;
};

string findBestAlgorithm(vector<int>& dataset, bool verbose = false) {
    vector<TestResult> results;
    bool skipSlow = dataset.size() > 1000;
    

    if (!skipSlow) {
        vector<int> arr1 = dataset;
        SortResult result1 = bubbleSort(arr1);
        results.push_back({"Bubble", result1.timeMs});
        
        vector<int> arr2 = dataset;
        SortResult result2 = insertionSort(arr2);
        results.push_back({"Insertion", result2.timeMs});
    }
    
    vector<int> arr3 = dataset;
    SortResult result3 = mergeSort(arr3);
    results.push_back({"Merge", result3.timeMs});
    
    vector<int> arr4 = dataset;
    SortResult result4 = quickSort(arr4);
    results.push_back({"Quick", result4.timeMs});
    

    string fastest = results[0].algorithm;
    double minTime = results[0].timeMs;
    
    for (const auto& result : results) {
        if (result.timeMs < minTime) {
            minTime = result.timeMs;
            fastest = result.algorithm;
        }
    }
    
    if (verbose) {
        cout << "  Results: ";
        for (const auto& r : results) {
            cout << r.algorithm << "=" << fixed << setprecision(3) << r.timeMs << "ms ";
        }
        cout << " -> " << fastest << endl;
    }
    
    return fastest;
}



int main(int argc, char* argv[]) {
    int samplesPerType = 500;  // 500 samples per dataset type
    string outputFile = "training_data.csv";
    

    if (argc > 1) {
        samplesPerType = atoi(argv[1]);
    }
    if (argc > 2) {
        outputFile = argv[2];
    }
    

    int totalDatasetTypes = 5;
    int totalSamples = samplesPerType * totalDatasetTypes;
    
    cout << "========================================" << endl;
    cout << "  k-NN Training Data Generator v2.0" << endl;
    cout << "========================================" << endl;
    cout << "Strategy: Generate " << samplesPerType << " samples per dataset type" << endl;
    cout << "Dataset types: Random, NearlySorted, Reversed, FewUnique, LargeRandom" << endl;
    cout << "Total samples: " << totalSamples << endl;
    cout << "Output file: " << outputFile << endl;
    cout << endl;
    
    // Open output file
    ofstream file(outputFile);
    if (!file.is_open()) {
        cerr << "Error: Cannot create output file: " << outputFile << endl;
        return 1;
    }
    
    file << "size,sortedness,uniqueRatio,bestAlgorithm,datasetType" << endl;
    
    time_t startTime = time(nullptr);
    int totalGenerated = 0;
    

    DatasetType types[] = {TYPE_RANDOM, TYPE_NEARLY_SORTED, TYPE_REVERSED, 
                           TYPE_FEW_UNIQUE, TYPE_LARGE_RANDOM};
    
    for (int typeIdx = 0; typeIdx < totalDatasetTypes; typeIdx++) {
        DatasetType currentType = types[typeIdx];
        const char* typeName = getTypeName(currentType);
        
        cout << "\n[" << (typeIdx + 1) << "/" << totalDatasetTypes << "] ";
        cout << "Generating " << samplesPerType << " samples for: " << typeName << endl;
        
        for (int i = 0; i < samplesPerType; i++) {
            vector<int> dataset = generateByType(currentType, i, samplesPerType);
            

            int actualSize = getDatasetSize(dataset);
            double actualSortedness = calculateSortedness(dataset);
            double actualUniqueRatio = calculateUniqueRatio(dataset);
            

            string bestAlgorithm = findBestAlgorithm(dataset);
            

            file << actualSize << ","
                 << fixed << setprecision(2) << actualSortedness << ","
                 << fixed << setprecision(4) << actualUniqueRatio << ","
                 << bestAlgorithm << ","
                 << typeName << endl;
            
            totalGenerated++;
            

            if ((i + 1) % 50 == 0 || i == samplesPerType - 1) {
                int percent = (int)((i + 1) * 100.0 / samplesPerType);
                cout << "\r  Progress: [";
                int barWidth = 30;
                int pos = barWidth * (i + 1) / samplesPerType;
                for (int p = 0; p < barWidth; p++) {
                    if (p < pos) cout << "=";
                    else if (p == pos) cout << ">";
                    else cout << " ";
                }
                cout << "] " << percent << "% (" << (i + 1) << "/" << samplesPerType << ")";
                cout.flush();
            }
        }
        cout << " ✓" << endl;
    }
    
    file.close();
    
    time_t endTime = time(nullptr);
    int elapsedSeconds = (int)difftime(endTime, startTime);
    
    cout << endl;
    cout << "========================================" << endl;
    cout << "Training data generation completed!" << endl;
    cout << "  Total samples: " << totalGenerated << endl;
    cout << "  Dataset types: " << totalDatasetTypes << endl;
    cout << "  Samples per type: " << samplesPerType << endl;
    cout << "  Output file: " << outputFile << endl;
    cout << "  Time elapsed: " << elapsedSeconds << " seconds" << endl;
    cout << "========================================" << endl;
    
    return 0;
}
