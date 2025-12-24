#include "knn_predictor.h"
#include <cmath>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

// ==============================================
// Constructor
// ==============================================

KNNPredictor::KNNPredictor(int kValue) : k(kValue) {}

// ==============================================
// Distance Calculation
// ==============================================

double KNNPredictor::euclideanDistance(const Features& f1, const Features& f2) {
    // Normalize features to same scale before calculating distance
    
    // Size: normalize by dividing by 10000 (typical max)
    double sizeNorm1 = f1.size / 10000.0;
    double sizeNorm2 = f2.size / 10000.0;
    
    // Sortedness: already in 0-100 range, normalize to 0-1
    double sortNorm1 = f1.sortedness / 100.0;
    double sortNorm2 = f2.sortedness / 100.0;
    
    // UniqueRatio: already in 0-1 range
    double uniqueNorm1 = f1.uniqueRatio;
    double uniqueNorm2 = f2.uniqueRatio;
    
    // Calculate Euclidean distance
    double sizeDiff = sizeNorm1 - sizeNorm2;
    double sortDiff = sortNorm1 - sortNorm2;
    double uniqueDiff = uniqueNorm1 - uniqueNorm2;
    
    return sqrt(sizeDiff * sizeDiff + sortDiff * sortDiff + uniqueDiff * uniqueDiff);
}

// ==============================================
// Training Data Management
// ==============================================

void KNNPredictor::addTrainingData(Features features, string bestAlgorithm) {
    trainingData.push_back(DataPoint(features, bestAlgorithm));
}

void KNNPredictor::loadDefaultTrainingData() {
    // Clear existing data
    trainingData.clear();
    
    // ===== SMALL DATASETS (n < 100) =====
    
    // Small, highly sorted -> Insertion Sort excels
    addTrainingData(Features(50, 95, 1.0), "Insertion");
    addTrainingData(Features(80, 92, 0.98), "Insertion");
    
    // Small, random -> Quick Sort or Insertion both work
    addTrainingData(Features(50, 50, 0.9), "Quick");
    addTrainingData(Features(70, 45, 0.85), "Quick");
    
    // Small, reversed -> Merge Sort stable
    addTrainingData(Features(50, 10, 1.0), "Merge");
    addTrainingData(Features(80, 5, 0.95), "Merge");
    
    // Small, few unique -> Quick Sort handles duplicates well
    addTrainingData(Features(60, 48, 0.15), "Quick");
    
    // ===== MEDIUM DATASETS (100 <= n < 1000) =====
    
    // Medium, nearly sorted -> Insertion Sort
    addTrainingData(Features(200, 88, 1.0), "Insertion");
    addTrainingData(Features(500, 90, 0.99), "Insertion");
    
    // Medium, random -> Quick Sort typically best
    addTrainingData(Features(300, 50, 0.95), "Quick");
    addTrainingData(Features(500, 48, 0.90), "Quick");
    addTrainingData(Features(800, 52, 0.88), "Quick");
    
    // Medium, reversed -> Merge Sort (Quick Sort worst case)
    addTrainingData(Features(300, 0, 1.0), "Merge");
    addTrainingData(Features(500, 5, 0.98), "Merge");
    
    // Medium, few unique -> Quick Sort
    addTrainingData(Features(400, 45, 0.10), "Quick");
    addTrainingData(Features(600, 50, 0.08), "Quick");
    
    // ===== LARGE DATASETS (n >= 1000) =====
    
    // Large, nearly sorted -> Merge Sort more consistent than Insertion
    addTrainingData(Features(2000, 85, 1.0), "Merge");
    addTrainingData(Features(5000, 88, 0.99), "Merge");
    
    // Large, random -> Quick Sort dominates
    addTrainingData(Features(2000, 50, 0.98), "Quick");
    addTrainingData(Features(5000, 48, 0.95), "Quick");
    addTrainingData(Features(10000, 51, 0.92), "Quick");
    
    // Large, reversed -> Merge Sort
    addTrainingData(Features(2000, 2, 1.0), "Merge");
    addTrainingData(Features(5000, 0, 0.99), "Merge");
    
    // Large, few unique -> Quick Sort
    addTrainingData(Features(3000, 49, 0.20), "Quick");
    addTrainingData(Features(8000, 50, 0.15), "Quick");
    
    // Edge case: very large with low unique ratio
    addTrainingData(Features(10000, 50, 0.05), "Quick");
}

// ==============================================
// Prediction Algorithm
// ==============================================

string KNNPredictor::predict(const Features& features) {
    if (trainingData.empty()) {
        return "Quick";  // Default fallback
    }
    
    // Calculate distances to all training points
    vector<Neighbor> neighbors;
    for (const DataPoint& dp : trainingData) {
        double dist = euclideanDistance(features, dp.features);
        neighbors.push_back(Neighbor(dist, dp.bestAlgorithm));
    }
    
    // Sort neighbors by distance (ascending)
    sort(neighbors.begin(), neighbors.end(), 
         [](const Neighbor& a, const Neighbor& b) {
             return a.distance < b.distance;
         });
    
    // Consider only k nearest neighbors
    int consideredK = min(k, (int)neighbors.size());
    
    // Vote: count algorithm occurrences in k nearest neighbors
    map<string, int> votes;
    for (int i = 0; i < consideredK; i++) {
        votes[neighbors[i].algorithm]++;
    }
    
    // Find algorithm with most votes
    string bestAlgorithm = "Quick";  // Default
    int maxVotes = 0;
    for (const auto& pair : votes) {
        if (pair.second > maxVotes) {
            maxVotes = pair.second;
            bestAlgorithm = pair.first;
        }
    }
    
    return bestAlgorithm;
}

// ==============================================
// Getters and Setters
// ==============================================

int KNNPredictor::getTrainingDataSize() const {
    return trainingData.size();
}

void KNNPredictor::setK(int kValue) {
    k = kValue;
}

// ==============================================
// File I/O Operations
// ==============================================

bool KNNPredictor::loadTrainingDataFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    // Clear existing training data
    trainingData.clear();
    
    string line;
    // Skip header line
    if (!getline(file, line)) {
        file.close();
        return false;
    }
    
    // Read data lines
    int lineCount = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string sizeStr, sortStr, uniqueStr, algorithm, datasetType;
        
        // Parse CSV: size,sortedness,uniqueRatio,bestAlgorithm[,datasetType]
        // Note: datasetType is optional for backward compatibility
        if (getline(ss, sizeStr, ',') &&
            getline(ss, sortStr, ',') &&
            getline(ss, uniqueStr, ',') &&
            getline(ss, algorithm, ',')) {  // Read up to comma
            
            // Optional: read datasetType if present (for new format)
            getline(ss, datasetType);  // Read rest of line
            
            try {
                int size = stoi(sizeStr);
                double sortedness = stod(sortStr);
                double uniqueRatio = stod(uniqueStr);
                
                // Create and add data point
                Features features(size, sortedness, uniqueRatio);
                addTrainingData(features, algorithm);
                lineCount++;
            } catch (...) {
                // Skip invalid lines
                continue;
            }
        }
    }
    
    file.close();
    return lineCount > 0;
}

bool KNNPredictor::saveTrainingDataToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    // Write header
    file << "size,sortedness,uniqueRatio,bestAlgorithm" << endl;
    
    // Write each training data point
    for (const DataPoint& dp : trainingData) {
        file << dp.features.size << ","
             << dp.features.sortedness << ","
             << dp.features.uniqueRatio << ","
             << dp.bestAlgorithm << endl;
    }
    
    file.close();
    return true;
}

void KNNPredictor::clearTrainingData() {
    trainingData.clear();
}

