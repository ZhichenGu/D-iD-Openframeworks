#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

<<<<<<< HEAD
#define HOST "192.168.1.72"
=======
>>>>>>> f5402d2bbe9beec04d1e7d7511f8383b3aab975a
#define PORT 9999

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
<<<<<<< HEAD

    void video(ofVideoPlayer videoPlayer);
    
    ofVideoPlayer videoPlayer0, videoPlayer1, videoPlayer2, videoPlayer3, videoPlayer4,
                  videoPlayer5, videoPlayer6, videoPlayer7, videoPlayer8, videoPlayer9;

	ofxOscReceiver receiver;
	int number;
=======
        void videoPlaying(ofVideoPlayer videoPlayer);
        void videoStop(ofVideoPlayer videoPlayer1, ofVideoPlayer videoPlayer2, ofVideoPlayer videoPlayer3,
                       ofVideoPlayer videoPlayer4, ofVideoPlayer videoPlayer5, ofVideoPlayer videoPlayer6,
                       ofVideoPlayer videoPlayer7, ofVideoPlayer videoPlayer8, ofVideoPlayer videoPlayer9);
    
    ofVideoPlayer videoPlayer0, videoPlayer1, videoPlayer2, videoPlayer3, videoPlayer4,
                  videoPlayer5, videoPlayer6, videoPlayer7, videoPlayer8, videoPlayer9;
    
    ofxOscReceiver receiver;
    int number;
>>>>>>> f5402d2bbe9beec04d1e7d7511f8383b3aab975a
		
};
