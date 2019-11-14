//
// Model.cpp
//


#include "Model.hpp"


Model::Model()
{
    maxRadius = ofGetWindowWidth() * .3;
}


void Model::initializeCompartmentPositions(shared_ptr<DataSlice> dataSlice)
{
    this->dataSlice = dataSlice;
    
    if (cellPositionsByCompartment.size() != dataSlice->compartmentCount)
    {
        cellPositionsByCompartment.resize(dataSlice->compartmentCount);
        markerPositionsByCompartment.resize(dataSlice->compartmentCount);
    }

    for (int i=0; i<dataSlice->compartmentCount; i++)
    {
        float innerRadius = ofMap(i, 0, dataSlice->compartmentCount, minRadius, maxRadius);
        float outerRadius = ofMap(i+1, 0, dataSlice->compartmentCount, minRadius, maxRadius);

        // proliferative cells

        vector<ofVec2f>& currentCellPositions = cellPositionsByCompartment.at(i);

        int cellCount = (int)dataSlice->prolifPopData.at(i) / 1000;
        if (cellCount < 0) cellCount = 0;

        updatePositions(currentCellPositions, cellCount, innerRadius, outerRadius);

        // marker (ET: extra-cellular, tumor compartments)

        vector<ofVec2f>& currentMarkerPositions = markerPositionsByCompartment.at(i);
        int markerCount = (int)dataSlice->markerETData.at(i);

        updatePositions(currentMarkerPositions, markerCount, innerRadius, outerRadius);
    }

    // marker, extra-cellular, in plasma

    updatePositions(markerPositionsPlasma, dataSlice->markerEPValue, 0, minRadius);
}


void Model::updatePositions(vector<ofVec2f>& positions, int count, 
                            float rMin, float rMax)
{
    // add positions if necessary

    for (int j=positions.size(); j<count; j++)
    {
        ofVec2f position(1, 0);
        position.rotateRad(ofRandomuf() * 2 * PI);
        position.scale(ofRandom(rMin, rMax));
        positions.push_back(position);
    }

    // remove positions if necessary

    positions.resize(count);
}


void Model::drawText()
{
    ofFill();
    ofSetColor(255);

    auto prolifPopData = dataSlice->prolifPopData;
    auto markerETData = dataSlice->markerETData;

    float x = 50;
    float xStep = ofGetWindowWidth()/12;
    float y = ofGetWindowHeight()-100;

    ofSetColor(0, 0, 255);
    ofDrawBitmapString(ofToString(dataSlice->markerEPValue), x, y + 50);

    x += xStep;

    for (int i=0; i<prolifPopData.size(); i++, x+=xStep)
    {
        ofSetColor(255);
        ofDrawBitmapString(ofToString(prolifPopData.at(i)), x, y);

        ofDrawBitmapString(ofToString(cellPositionsByCompartment.at(i).size()), x, y + 25);

        ofSetColor(0, 0, 255);
        ofDrawBitmapString(ofToString(markerETData.at(i)), x, y + 50);
    }

    ofSetColor(0, 255, 0);
    ofDrawBitmapString(ofToString(1 + dataSlice->index) + " / " + ofToString(dataSlice->max), 
                       ofGetWindowWidth()-100, 50);
}


void Model::drawCompartments()
{
    ofPushMatrix();
    ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight()*.4);

    for (float i=dataSlice->compartmentCount-1; i>=0; i--)
    {
        float radius = ofMap(i, 0, dataSlice->compartmentCount, minRadius, maxRadius);
        ofNoFill();
        ofSetColor(255);
        ofDrawCircle(0, 0, radius); 
        ofFill();

        const vector<ofVec2f>& compartmentCellPositions = cellPositionsByCompartment.at(i);

        for (auto position : compartmentCellPositions)
            ofDrawCircle(position.x, position.y, 1);

        const vector<ofVec2f>& compartmentMarkerPositions = markerPositionsByCompartment.at(i);

        ofSetColor(0, 0, 255);
        for (auto position : compartmentMarkerPositions)
            ofDrawCircle(position.x, position.y, 1);
    }

    // plasma

    ofSetColor(0, 0, 255);
    for (auto position : markerPositionsPlasma)
        ofDrawCircle(position.x, position.y, 1);

    ofPopMatrix();
}


