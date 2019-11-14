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

    private:

    vector<vector<float>> prolifPopData;
    vector<vector<float>> markerETData; // extra-cellular, tumor

    void readDataMatrix(const string& filename, vector<vector<float>>& destination);
    void printDataMatrix(const vector<vector<float>>& data);
};

