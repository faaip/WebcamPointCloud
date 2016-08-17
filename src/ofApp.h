#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
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
    
    // Video stuff
    ofVideoGrabber vidGrabber;
    ofPixels videoPixels;
    ofTexture videoTexture;
    int camWidth;
    int camHeight;
    int drawWidth, drawHeight;
    ofEasyCam cam;
    ofVboMesh mainMesh;
    float extrusionAmount;
    
    
    // GUI Stuff
    bool hideGui;
    ofxPanel gui;
    ofParameter<float> ampFactor;
    ofParameter<bool> flip;
    ofParameter<bool> camEnabled;
    ofParameter<bool> drawFace;
    ofParameter<bool> drawWireframe;
    ofParameter<bool> drawPointcloud;
    
    
};
