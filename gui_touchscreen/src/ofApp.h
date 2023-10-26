#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "192.168.1.100"
#define PORT 8888

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);

    std::vector<ofRectangle> buttons;  
    std::vector<bool> buttonClicked;
    
    std::vector<ofRectangle> smallButtons;
    std::vector<bool> smallButtonClicked;
    
    std::vector<std::string> buttonNames;
    std::vector<std::string> smallButtonNames;
    
    ofRectangle resetButton;
    bool resetButtonClicked;
    
    ofVideoGrabber videoGrabber;
    int camWidth = 320;
    int camHeight = 240;
    
    ofImage capturedFrame;  // To store the captured frame
    bool captureFrame = false;
    void captureWebcamFrame();
    
    ofRectangle webcamButton;
    bool webcamButtonEnabled;
    
    ofRectangle geneButton;
    bool geneButtonEnabled;
    bool geneDataSend = false;

    void keyPressed(int key);
    
    ofxOscSender sender;
    
    int bigChoice, smallChoice;
};
