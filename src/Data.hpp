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

    const vector<float>& getProlifPopData(int i) const;
    const vector<float>& getMarkerETData(int i) const;

    private:

    vector<vector<float>> prolifPopData;
    vector<vector<float>> markerETData; // extra-cellular, tumor

    void readData(const string& filename, vector<vector<float>>& destination);
    void printData(const vector<vector<float>>& data);

};

