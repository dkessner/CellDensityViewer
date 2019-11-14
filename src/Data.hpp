//
// Data.hpp
//


#pragma once
#include "ofMain.h"


class Data
{
    public:

    static const int compartmentCount = 10;

    Data();

    int size() const;

    const vector<float>& getProlifPopData(int timeIndex) const;
    const vector<float>& getMarkerETData(int timeIndex) const;
    float getMarkerEPValue(int timeIndex) const;

    private:

    vector<vector<float>> prolifPopData;
    vector<vector<float>> markerETData; // extra-cellular, tumor
    vector<float> markerEPData;         // extra-cellular, plasma

    void readDataVector(const string& filename, vector<float>& destination);
    void readDataMatrix(const string& filename, vector<vector<float>>& destination);

    void print(const vector<float>& data);
    void print(const vector<vector<float>>& data);
};

