#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 9999

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void videoPlaying(ofVideoPlayer videoPlayer);
    void videoStop(ofVideoPlayer videoPlayer1, ofVideoPlayer videoPlayer2, ofVideoPlayer videoPlayer3,
        ofVideoPlayer videoPlayer4, ofVideoPlayer videoPlayer5, ofVideoPlayer videoPlayer6,
        ofVideoPlayer videoPlayer7, ofVideoPlayer videoPlayer8, ofVideoPlayer videoPlayer9);

    ofVideoPlayer videoPlayer0, videoPlayer1, videoPlayer2, videoPlayer3, videoPlayer4,
                  videoPlayer5, videoPlayer6, videoPlayer7, videoPlayer8, videoPlayer9;

    ofxOscReceiver receiver;
    int number;

};
