#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(125);
	ofSetFrameRate(60);
	video.setDeviceID(0);
	video.setDesiredFrameRate(60);
	video.initGrabber(640, 480);
	debug = true;
	sumVal = 0;

	vector<ofVideoDevice> devices = video.listDevices();
	for (const auto& device : devices) {
		cout << "Device ID: " << device.id << ", Name: " << device.deviceName << endl;
	}

	senderMini.setup("192.168.1.188", 1337);
	senderHP.setup("192.168.1.72",9999 );

}

//--------------------------------------------------------------
void ofApp::update() {
	frameCount++;
	video.update();		//Decode the new frame if needed
	//Do computing only if the new frame was obtained
	if (video.isFrameNew()) {
		//Store the previous frame, if it exists till now
		if (grayImage.bAllocated) {
			grayImagePrev = grayImage;
		}

		//Getting a new frame
		image.setFromPixels(video.getPixels());
		image.mirror(false, true);
		grayImage = image; //Convert to grayscale image

		//Do processing if grayImagePrev is initialised
		if (grayImagePrev.bAllocated) {
			//Get absolute difference
			diff.absDiff(grayImage, grayImagePrev);

			//We want to amplify the difference to obtain
			//better visibility of motion
			//We do it by multiplication. But to do it, we
			//need to convert diff to float image first
			diffFloat = diff;	//Convert to float image
			diffFloat *= 5.0;	//Amplify the pixel values (original = 5.0)

			//Update the accumulation buffer
			if (!bufferFloat.bAllocated) {
				//If the buffer is not initialized, then
				//just set it equal to diffFloat
				bufferFloat = diffFloat;
			}
			else {
				//Slow damping the buffer to zero
				bufferFloat *= 0.05; //original = 0.85
				//Add current difference image to the buffer

				bufferFloat += diffFloat;
				bufferFloat.erode(); //helps get rid of noise (remove if not needed)
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	//ofBackground( 255, 255, 255 );	//Set the background color

	//Draw only if diffFloat image is ready.
	//It happens when the second frame from the video is obtained
	if (diffFloat.bAllocated) {
		//Get image dimensions
		int w = grayImage.width;
		int h = grayImage.height;

		//Set color for images drawing
		ofSetColor(255, 255, 255);

		//Draw images grayImage,  diffFloat, bufferFloat
		if (debug)
		{
			//grayImage.draw( 0, 0, w/2, h/2 );
			//diffFloat.draw( w/2, 0, w/2, h/2 );
			bufferFloat.draw(0, h / 2, w / 2, h / 2);
			
		}
		else image.draw(0, 0, ofGetWidth(), ofGetHeight());

		//Draw the image motion areas
		if (debug)
		{
			//Shift and scale the coordinate system
			ofPushMatrix();
			ofTranslate(w / 2, h / 2);
			ofScale(0.5, 0.5);
			//Draw bounding rectangle
			ofSetColor(0, 0, 0);
			ofNoFill();
		}

		//Get bufferFloat pixels
		float *pixels = bufferFloat.getPixelsAsFloats();

		//Scan all pixels
		for (int y = 0; y < h; y += 1)
		{
			for (int x = 0; x < w; x += 1)
			{

				//Get the pixel value
				float value = pixels[x + w * y];
				sumVal += value;
				//If value exceed threshold, then draw pixel
				//if ( value >= 1.4 ) {                           //original was 0.9
				//   if (debug) ofDrawRectangle( x, y, 1, 1 );
				//   //EDIT HERE: this is where you'll be activating
				//   //the grid locations or generating particles
				//   //the debug mode draws small black points in the bottom right square
				//}
			}
		}
		//cout << "sumVal:" << sumVal << endl;

		if (frameCount > 150) {
			frameCount = 0;
			ofxOscBundle bundleMini;
			ofxOscMessage tagMini;

			ofxOscBundle bundleHP;
			ofxOscMessage tagHP;

			/*cout << "sumVal:" << sumVal << endl;*/
		

			if (sumVal >= 3000 && sumVal <= 14000) {
				ofSetBackgroundColor(0, 255, 0);
				index = ofRandom(3); 
				tagMini.setAddress("/mini");
				tagMini.addIntArg(index);
				bundleMini.addMessage(tagMini);

				tagHP.setAddress("/data");
				tagHP.addIntArg(index);
				bundleHP.addMessage(tagHP);

			}
			else if (sumVal >= 30000) {
				ofSetBackgroundColor(255, 0, 0);
				index = ofRandom(3, 7);
				tagMini.setAddress("/mini");
				tagMini.addIntArg(index);
				bundleMini.addMessage(tagMini);

				tagHP.setAddress("/data");
				tagHP.addIntArg(index);
				bundleHP.addMessage(tagHP);
			}
			else if (sumVal <= 1400) {
				ofSetBackgroundColor(0, 255, 255);
				index = ofRandom(7, 10);
				tagMini.setAddress("/mini");
				tagMini.addIntArg(index);
				bundleMini.addMessage(tagMini);

				tagHP.setAddress("/data");
				tagHP.addIntArg(index);
				bundleHP.addMessage(tagHP);
			}

			else {
				ofSetBackgroundColor(0);
			}
			
			
			
			senderMini.sendBundle(bundleMini);
			senderHP.sendBundle(bundleHP);
		}

		sumVal = 0;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	debug = !debug;
}
