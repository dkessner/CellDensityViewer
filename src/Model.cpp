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
    
    if (cellPositions.size() != dataSlice->compartmentCount)
    {
        cellPositions.resize(dataSlice->compartmentCount);
        markerPositions.resize(dataSlice->compartmentCount);
    }

    for (int i=0; i<dataSlice->compartmentCount; i++)
    {
        float innerRadius = ofMap(i, 0, dataSlice->compartmentCount, minRadius, maxRadius);
        float outerRadius = ofMap(i+1, 0, dataSlice->compartmentCount, minRadius, maxRadius);

        // proliferative cells

        vector<ofVec2f>& currentCellPositions = cellPositions.at(i);

        int cellCount = (int)dataSlice->prolifPopData.at(i) / 1000;
        if (cellCount < 0) cellCount = 0;

        // add cell positions if necessary

        for (int j=currentCellPositions.size(); j<cellCount; j++)
        {
            ofVec2f position(1, 0);
            position.rotateRad(ofRandomuf() * 2 * PI);
            position.scale(ofRandom(innerRadius, outerRadius));
            currentCellPositions.push_back(position);
        }

        // remove cell positions if necessary

        currentCellPositions.resize(cellCount);

        // extracelluluar tumor marker

        vector<ofVec2f>& currentMarkerPositions = markerPositions.at(i);
        int markerCount = (int)dataSlice->markerETData.at(i);

        // add marker positions if necessary

        for (int j=currentMarkerPositions.size(); j<markerCount; j++)
        {
            ofVec2f position(1, 0);
            position.rotateRad(ofRandomuf() * 2 * PI);
            position.scale(ofRandom(innerRadius, outerRadius));
            currentMarkerPositions.push_back(position);
        }

        // remove marker particles if necessary

        currentMarkerPositions.resize(markerCount);
    }
}


void Model::drawText()
{
    ofFill();
    ofSetColor(255);

    auto prolifPopData = dataSlice->prolifPopData;
    auto markerETData = dataSlice->markerETData;

    float x = 50;
    float y = ofGetWindowHeight()-100;

    for (int i=0; i<prolifPopData.size(); i++, x+=100)
    {
        ofSetColor(255);
        ofDrawBitmapString(ofToString(prolifPopData.at(i)), x, y);

        ofDrawBitmapString(ofToString(cellPositions.at(i).size()), x, y + 25);

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

        const vector<ofVec2f>& compartmentCellPositions = cellPositions.at(i);

        for (auto position : compartmentCellPositions)
            ofDrawCircle(position.x, position.y, 1);

        const vector<ofVec2f>& compartmentMarkerPositions = markerPositions.at(i);

        ofSetColor(0, 0, 255);
        for (auto position : compartmentMarkerPositions)
            ofDrawCircle(position.x, position.y, 1);
    }

    ofPopMatrix();
}


