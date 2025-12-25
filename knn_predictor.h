#ifndef KNN_PREDICTOR_H
#define KNN_PREDICTOR_H

#include <vector>
#include <string>

using namespace std;




struct Features {
    int size;
    double sortedness;
    double uniqueRatio;
    
    Features(int s, double sort, double unique) 
        : size(s), sortedness(sort), uniqueRatio(unique) {}
};


struct DataPoint {
    Features features;
    string bestAlgorithm;
    
    DataPoint(Features f, string algo) 
        : features(f), bestAlgorithm(algo) {}
};



class KNNPredictor {
private:
    vector<DataPoint> trainingData;
    int k;
    
    double euclideanDistance(const Features& f1, const Features& f2);
    

    struct Neighbor {
        double distance;
        string algorithm;
        
        Neighbor(double d, string algo) : distance(d), algorithm(algo) {}
    };
    
public:
    KNNPredictor(int kValue = 5);
    
    void addTrainingData(Features features, string bestAlgorithm);
    
    void loadDefaultTrainingData();
    
    bool loadTrainingDataFromFile(const string& filename);
    
    bool saveTrainingDataToFile(const string& filename) const;
    
    void clearTrainingData();
    
    string predict(const Features& features);
    
    int getTrainingDataSize() const;
    
    void setK(int kValue);
};

#endif
