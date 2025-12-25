#include "../include/knn_predictor.h"
#include <cmath>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;



KNNPredictor::KNNPredictor(int kValue) : k(kValue) {}  // Initialize with k neighbors



double KNNPredictor::euclideanDistance(const Features& f1, const Features& f2) {  // Calculate normalized Euclidean distance
    // Normalize all features to [0, 1] range for fair comparison
    // Size: divide by 10000 (typical max dataset size)
    double sizeNorm1 = f1.size / 10000.0;
    double sizeNorm2 = f2.size / 10000.0;
    // Sortedness: already in 0-100%, convert to 0-1
    double sortNorm1 = f1.sortedness / 100.0;
    double sortNorm2 = f2.sortedness / 100.0;
    // UniqueRatio: already in 0-1 range
    double uniqueNorm1 = f1.uniqueRatio;
    double uniqueNorm2 = f2.uniqueRatio;
    
    // Calculate Euclidean distance: sqrt(sum of squared differences)
    double sizeDiff = sizeNorm1 - sizeNorm2;
    double sortDiff = sortNorm1 - sortNorm2;
    double uniqueDiff = uniqueNorm1 - uniqueNorm2;
    
    return sqrt(sizeDiff * sizeDiff + sortDiff * sortDiff + uniqueDiff * uniqueDiff);
}



void KNNPredictor::addTrainingData(Features features, string bestAlgorithm) {  // Add sample to training set
    trainingData.push_back(DataPoint(features, bestAlgorithm));
}

void KNNPredictor::loadDefaultTrainingData() {  // Load 26 pre-defined training samples
    trainingData.clear();
    

    
    addTrainingData(Features(50, 95, 1.0), "Insertion");
    addTrainingData(Features(80, 92, 0.98), "Insertion");
    
    addTrainingData(Features(50, 50, 0.9), "Quick");
    addTrainingData(Features(70, 45, 0.85), "Quick");
    
    addTrainingData(Features(50, 10, 1.0), "Merge");
    addTrainingData(Features(80, 5, 0.95), "Merge");
    
    addTrainingData(Features(60, 48, 0.15), "Quick");
    

    
    addTrainingData(Features(200, 88, 1.0), "Insertion");
    addTrainingData(Features(500, 90, 0.99), "Insertion");
    
    addTrainingData(Features(300, 50, 0.95), "Quick");
    addTrainingData(Features(500, 48, 0.90), "Quick");
    addTrainingData(Features(800, 52, 0.88), "Quick");
    
    addTrainingData(Features(300, 0, 1.0), "Merge");
    addTrainingData(Features(500, 5, 0.98), "Merge");
    
    addTrainingData(Features(400, 45, 0.10), "Quick");
    addTrainingData(Features(600, 50, 0.08), "Quick");
    

    
    addTrainingData(Features(2000, 85, 1.0), "Merge");
    addTrainingData(Features(5000, 88, 0.99), "Merge");
    
    addTrainingData(Features(2000, 50, 0.98), "Quick");
    addTrainingData(Features(5000, 48, 0.95), "Quick");
    addTrainingData(Features(10000, 51, 0.92), "Quick");
    
    addTrainingData(Features(2000, 2, 1.0), "Merge");
    addTrainingData(Features(5000, 0, 0.99), "Merge");
    
    addTrainingData(Features(3000, 49, 0.20), "Quick");
    addTrainingData(Features(8000, 50, 0.15), "Quick");
    
    addTrainingData(Features(10000, 50, 0.05), "Quick");
}



string KNNPredictor::predict(const Features& features) {  // Predict using k nearest neighbors voting
    if (trainingData.empty()) {
        return "Quick";  // Default fallback if no training data
    }
    
    // Step 1: Calculate distance to all training points
    vector<Neighbor> neighbors;
    for (const DataPoint& dp : trainingData) {
        double dist = euclideanDistance(features, dp.features);
        neighbors.push_back(Neighbor(dist, dp.bestAlgorithm));
    }
    
    // Step 2: Sort by distance (ascending) to find nearest neighbors
    sort(neighbors.begin(), neighbors.end(), 
         [](const Neighbor& a, const Neighbor& b) {
             return a.distance < b.distance;
         });
    
    // Step 3: Consider only k nearest neighbors
    int consideredK = min(k, (int)neighbors.size());
    
    // Step 4: Vote - count algorithm occurrences in k nearest neighbors
    map<string, int> votes;
    for (int i = 0; i < consideredK; i++) {
        votes[neighbors[i].algorithm]++;
    }
    
    // Step 5: Return algorithm with most votes (majority voting)
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



int KNNPredictor::getTrainingDataSize() const {  // Return number of training samples
    return trainingData.size();
}

void KNNPredictor::setK(int kValue) {  // Update k value
    k = kValue;
}



bool KNNPredictor::loadTrainingDataFromFile(const string& filename) {  // Load training data from CSV file
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    trainingData.clear();
    
    string line;

    if (!getline(file, line)) {
        file.close();
        return false;
    }
    

    int lineCount = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string sizeStr, sortStr, uniqueStr, algorithm, datasetType;
        
        if (getline(ss, sizeStr, ',') &&
            getline(ss, sortStr, ',') &&
            getline(ss, uniqueStr, ',') &&
            getline(ss, algorithm, ',')) {
            
            getline(ss, datasetType);
            
            try {
                int size = stoi(sizeStr);
                double sortedness = stod(sortStr);
                double uniqueRatio = stod(uniqueStr);
                

                Features features(size, sortedness, uniqueRatio);
                addTrainingData(features, algorithm);
                lineCount++;
            } catch (...) {
                continue;
            }
        }
    }
    
    file.close();
    return lineCount > 0;
}

bool KNNPredictor::saveTrainingDataToFile(const string& filename) const {  // Save training data to CSV file
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << "size,sortedness,uniqueRatio,bestAlgorithm" << endl;
    
    for (const DataPoint& dp : trainingData) {
        file << dp.features.size << ","
             << dp.features.sortedness << ","
             << dp.features.uniqueRatio << ","
             << dp.bestAlgorithm << endl;
    }
    
    file.close();
    return true;
}

void KNNPredictor::clearTrainingData() {  // Remove all training samples
    trainingData.clear();
}

