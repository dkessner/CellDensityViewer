//
// ofApp.cpp
//


#include "ofApp.h"
#include <cmath>


void ofApp::setup()
{
    data = make_unique<Data>();
    model = make_unique<Model>();

    timeIndex = 0;
    reinitializeModel();

    timeIndexSlider.setup("time index", timeIndex+1, 1, data->size());
    timeIndexSlider.setShape(100, ofGetWindowHeight()-150, ofGetWindowWidth()-200, 25);
    timeIndexSlider.setBorderColor(ofColor(0, 0, 255));
    timeIndexSlider.setBackgroundColor(ofColor(50));
}


void ofApp::reinitializeModel()
{
    shared_ptr<Model::DataSlice> dataSlice(
            new Model::DataSlice(timeIndex,
                                 data->size(),
                                 Data::compartmentCount,
                                 data->getProlifPopData(timeIndex),
                                 data->getMarkerETData(timeIndex),
                                 data->getMarkerEPValue(timeIndex)));

    model->initializeCompartmentPositions(dataSlice);
}


void ofApp::update()
{
    if (mouseDownRightSide || mouseDownLeftSide)
    {
        int rate = 10*(int)(ofGetElapsedTimeMillis() - mouseDownStartTime)/500;
        rate *= mouseDownRightSide ? 1 : -1;
        timeStep(rate);
    }

    if (timeIndex != timeIndexSlider-1)
    {
        timeIndex = timeIndexSlider-1;
        reinitializeModel();
    }
}


void ofApp::draw()
{
    ofBackground(0);

    model->drawText();
    model->drawCompartments();

    timeIndexSlider = (int)timeIndexSlider;
    timeIndexSlider.draw();
}


void ofApp::timeStep(int step)
{
    timeIndex += step;

    if (timeIndex >= (int)data->size())
        timeIndex = data->size()-1;

    if (timeIndex < 0)
        timeIndex = 0;

    reinitializeModel();
}


void ofApp::keyPressed(int key)
{
    if (!mouseDownRightSide && !mouseDownLeftSide) // because of keyboard repeat
        mouseDownStartTime = ofGetElapsedTimeMillis();

    mouseStartPosition.y = ofGetWindowHeight()/2;

    if (key == OF_KEY_RIGHT)
    {
        mouseDownRightSide = true;
        mouseStartPosition.x = ofGetWindowWidth();
        timeStep(1);
    }
    else if (key == OF_KEY_LEFT)
    {
        mouseDownLeftSide = true;
        mouseStartPosition.x = 0;
        timeStep(-1);
    }
}


void ofApp::keyReleased(int key)
{
    mouseDownLeftSide = mouseDownRightSide = false;
}


void ofApp::mousePressed(int x, int y, int button)
{
    mouseDownStartTime = ofGetElapsedTimeMillis();

    mouseStartPosition.x = x;
    mouseStartPosition.y = y;

    if (x < ofGetWindowWidth()/2)
    {
        mouseDownLeftSide = true;
        timeStep(-1);
    }
    else
    {
        mouseDownRightSide = true;
        timeStep(1);
    }
}


void ofApp::mouseDragged(int x, int y, int button)
{
    int d = (x - mouseStartPosition.x)/10;
    timeStep(d);
}


void ofApp::mouseReleased(int x, int y, int button)
{
    mouseDownLeftSide = mouseDownRightSide = false;
}


void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}


