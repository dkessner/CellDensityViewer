//
// Model.hpp
//


#include <vector>
#include "ofMain.h"


class Model
{
    public:

    Model();

    struct DataSlice
    {
        int index;
        int max;
        int compartmentCount;
        const vector<float>& prolifPopData;
        const vector<float>& markerETData;
        float markerEPValue;

        DataSlice(int index, int max, 
                  int compartmentCount,
                  const vector<float>& prolifPopData, 
                  const vector<float>& markerETData,
                  float markerEPValue)
        :   index(index), max(max), 
            compartmentCount(compartmentCount), 
            prolifPopData(prolifPopData),
            markerETData(markerETData),
            markerEPValue(markerEPValue)
        {}
    };

    void initializeCompartmentPositions(shared_ptr<DataSlice> dataSlice);

    void drawText();
    void drawCompartments();

    private:

    const float minRadius = 50;
    float maxRadius;

    shared_ptr<DataSlice> dataSlice;

    vector<vector<ofVec2f>> cellPositionsByCompartment;
    vector<vector<ofVec2f>> markerPositionsByCompartment;
    vector<ofVec2f> markerPositionsPlasma;

    void updatePositions(vector<ofVec2f>& positions, int count, 
                         float rMin, float rMax);
};


