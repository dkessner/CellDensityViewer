//
// ofApp.h
//


#pragma once
#include "ofMain.h"
#include "Data.hpp"
#include "Model.hpp"


class ofApp : public ofBaseApp
{
    public:

    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
            
    private:

    unique_ptr<Data> data;
    unique_ptr<Model> model;

    int timeIndex = 0;
    void timeStep(int step);

    int mouseDownStartTime = 0;
    ofVec2f mouseStartPosition;
    bool mouseDownRightSide = false;
    bool mouseDownLeftSide = false;

    void reinitializeModel();
};
