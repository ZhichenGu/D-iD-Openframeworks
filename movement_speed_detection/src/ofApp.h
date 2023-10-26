#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"

#include "ofxOsc.h"


class ofApp : public ofBaseApp {



public:
	void setup();
	void update();
	void draw();

	ofVideoGrabber video;		//Declare the video player object
	ofxCvColorImage image;		//The current video frame

	//The current and the previous video frames as grayscale images
	ofxCvGrayscaleImage grayImage, grayImagePrev;
	ofxCvGrayscaleImage diff;		//Absolute difference of the frames
	ofxCvFloatImage diffFloat;		//Amplified difference images
	ofxCvFloatImage bufferFloat;	//Buffer image

	float sumVal;
	int frameCount, index;

	ofxOscSender senderMini, senderHP;
	

	void mousePressed(int x, int y, int button);
	bool debug;
};

