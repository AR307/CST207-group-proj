#ifndef KNN_PREDICTOR_H
#define KNN_PREDICTOR_H

#include <vector>
#include <string>

using namespace std;




struct Features {  // Dataset characteristics for k-NN classification
    int size;           // Number of elements in this dataset
    double sortedness;  // How sorted the data is (0-100%）
    double uniqueRatio; // Ratio of unique elements (0.0-1.0)
    
    Features(int s, double sort, double unique) 
        : size(s), sortedness(sort), uniqueRatio(unique) {}
};


struct DataPoint {  // Training sample: features + best algorithm label
    Features features;
    string bestAlgorithm;
    
    DataPoint(Features f, string algo) 
        : features(f), bestAlgorithm(algo) {}
};



class KNNPredictor {  // k-NN based sorting algorithm predictor
private:
    vector<DataPoint> trainingData;
    int k;
    
    double euclideanDistance(const Features& f1, const Features& f2);  // Calculate distance between feature vectors
    

    struct Neighbor {  // Store neighbor distance and algorithm for voting
        double distance;
        string algorithm;
        
        Neighbor(double d, string algo) : distance(d), algorithm(algo) {}
    };
    
public:
    KNNPredictor(int kValue = 5);  // Constructor with k neighbors (default 5)
    
    void addTrainingData(Features features, string bestAlgorithm);  // Add a training sample
    
    void loadDefaultTrainingData();  // Load 26 hardcoded training samples
    
    bool loadTrainingDataFromFile(const string& filename);  // Load training data from CSV file
    
    bool saveTrainingDataToFile(const string& filename) const;  // Save training data to CSV file
    
    void clearTrainingData();  // Remove all training samples
    
    string predict(const Features& features);  // Predict best sorting algorithm using k-NN
    
    int getTrainingDataSize() const;  // Get number of training samples
    
    void setK(int kValue);  // Set number of neighbors to consider
};

#endif
