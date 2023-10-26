#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "192.168.1.72"
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
    
    int bigChoice;
    int smallChoice;

    std::string instructions =
        "1. Select 1 voice (top row)\n\n"
        "2. Select 1 Adjective (bottom row)\n\n"
        "3. Position your face in the middle of the frame of camera,\n   mouth closed, with a neutral expression.\n\n"
        "4. Press the Webcam button (left)\n\n"
        "5. A Generate button should appear on the left. If you are unhappy,\n   press reset and start from stage 1 again.\n\n"
        "6. If you wish to proceed, press Generate button.\n\n"
        "7. Wait 1 minute for generation and then enter the installation\n\n";

};
