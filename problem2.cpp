#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

float computeMean(const vector<float> &data) {
    return accumulate(data.begin(), data.end(), 0.0f) / data.size();
}

float computeStdDev(const vector<float> &data, float mean) {
    float variance = 0.0;
    for (float val : data) {
        variance += (val - mean) * (val - mean);
    }
    return sqrt(variance / data.size());
}

vector<float> applyZScore(const vector<float> &data) {
    float mean = computeMean(data);
    float stddev = computeStdDev(data, mean);
    vector<float> normalizedData;
    for (float val : data) {
        normalizedData.push_back((val - mean) / stddev);
    }
    return normalizedData;
}

int main() {
    ifstream inputFile("lsun.txt");
    ofstream outputFile("zscore1.txt");

    if (!inputFile) {
        cerr << "Failed to open input file!" << endl;
        return 1;
    }
    if (!outputFile) {
        cerr << "Failed to open output file!" << endl;
        return 1;
    }

    string header;
    for (int i = 0; i < 6; i++) inputFile >> header;

    vector<float> feature1, feature2, labels;
    float val1, val2, val3;
    while (inputFile >> val1 >> val2 >> val3) {
        feature1.push_back(val1);
        feature2.push_back(val2);
        labels.push_back(val3);
    }

    vector<float> normFeature1 = applyZScore(feature1);
    vector<float> normFeature2 = applyZScore(feature2);
    vector<float> normLabels = applyZScore(labels);

    outputFile << "Feature1\tFeature2\tLabel\n";
    for (size_t i = 0; i < normFeature1.size(); i++) {
        outputFile << normFeature1[i] << "\t" << normFeature2[i] << "\t" << normLabels[i] << "\n";
    }

    inputFile.close();
    outputFile.close();
    cout << "Normalization complete. Output saved to zscore.txt." << endl;

    return 0;
}
