#ifndef KNN_PREDICTOR_H
#define KNN_PREDICTOR_H

#include <vector>
#include <string>

using namespace std;

// ==============================================
// Data Structures
// ==============================================

// Features extracted from a dataset
struct Features {
    int size;              // Number of elements in dataset
    double sortedness;     // How sorted the data is (0-100%)
    double uniqueRatio;    // Ratio of unique elements (0.0-1.0)
    
    Features(int s, double sort, double unique) 
        : size(s), sortedness(sort), uniqueRatio(unique) {}
};

// Training data point: features + best algorithm label
struct DataPoint {
    Features features;
    string bestAlgorithm;  // "Bubble", "Insertion", "Merge", "Quick"
    
    DataPoint(Features f, string algo) 
        : features(f), bestAlgorithm(algo) {}
};

// ==============================================
// k-NN Predictor Class
// ==============================================

class KNNPredictor {
private:
    vector<DataPoint> trainingData;
    int k;  // Number of nearest neighbors to consider
    
    // Calculate Euclidean distance between two feature vectors
    double euclideanDistance(const Features& f1, const Features& f2);
    
    // Structure to store neighbor distance and algorithm
    struct Neighbor {
        double distance;
        string algorithm;
        
        Neighbor(double d, string algo) : distance(d), algorithm(algo) {}
    };
    
public:
    // Constructor with default k=5
    KNNPredictor(int kValue = 5);
    
    // Add a training data point
    void addTrainingData(Features features, string bestAlgorithm);
    
    // Load default training dataset (26 hardcoded samples)
    void loadDefaultTrainingData();
    
    // Load training data from CSV file
    bool loadTrainingDataFromFile(const string& filename);
    
    // Save current training data to CSV file
    bool saveTrainingDataToFile(const string& filename) const;
    
    // Clear all training data
    void clearTrainingData();
    
    // Predict best algorithm for given features using k-NN
    string predict(const Features& features);
    
    // Get number of training samples
    int getTrainingDataSize() const;
    
    // Set k value
    void setK(int kValue);
};

#endif
