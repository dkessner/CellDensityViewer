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

        DataSlice(int index, int max, 
                  int compartmentCount,
                  const vector<float>& prolifPopData, 
                  const vector<float>& markerETData)
        :   index(index), max(max), 
            compartmentCount(compartmentCount), 
            prolifPopData(prolifPopData),
            markerETData(markerETData)
        {}
    };

    void initializeCompartmentPositions(shared_ptr<DataSlice> dataSlice);

    void drawText();
    void drawCompartments();

    private:

    const float minRadius = 50;
    float maxRadius;

    shared_ptr<DataSlice> dataSlice;

    vector<vector<ofVec2f>> cellPositions;
    vector<vector<ofVec2f>> markerPositions;

    void updatePositions(vector<ofVec2f>& positions, int count, 
                         float rMin, float rMax);
};


