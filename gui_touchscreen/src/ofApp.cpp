#include "ofApp.h"

void ofApp::setup() {
    ofSetBackgroundColor(0); // Set the background color to black
    sender.setup(HOST, PORT);
    
    int screenWidth = 1920;
    int screenHeight = 1080;
    ofSetWindowShape(screenWidth, screenHeight);
    
    int buttonWidth = 200;  // Width of each button
    int buttonHeight = 96;  // Height of each button
    int buttonGap = 100;     // Gap between buttons
    
    // Create the three large buttons in a horizontal array with a gap between them
    for (int i = 0; i < 2; i++) {
        int x = ofGetWidth() / 2 - (buttonWidth * 2 + buttonGap * 1) / 2 + i * (buttonWidth + buttonGap);
        int y = ofGetHeight() / 2 - buttonHeight / 2;
        ofRectangle buttonRect(x, y + 215, buttonWidth, buttonHeight);
        buttons.push_back(buttonRect);
        buttonClicked.push_back(false);
    }
    
    // Create the five small buttons below the large buttons
    int smallButtonWidth = 120;  // Width of each small button
    int smallButtonHeight = 70; // Height of each small button
    int smallbuttonGap = 160;     // Gap between buttons
    
    for (int i = 0; i < 5; i++) {
        int x = ofGetWidth() / 2 - (smallButtonWidth * 5 + smallbuttonGap * 4) / 2 + i * (smallButtonWidth + smallbuttonGap);
        int y = ofGetHeight() / 2;
        ofRectangle smallButtonRect(x, y + 215 + 160, smallButtonWidth, smallButtonHeight);
        smallButtons.push_back(smallButtonRect);
        smallButtonClicked.push_back(false);
    }
    
    // Assign names to large buttons
    buttonNames.push_back("BARITONE Voice");
    buttonNames.push_back("SOPRANO Voice");
    
    // Assign names to small buttons
    smallButtonNames.push_back("Friendly");
    smallButtonNames.push_back("Sad");
    smallButtonNames.push_back("Cheerful");
    smallButtonNames.push_back("Whispering");
    smallButtonNames.push_back("Excited");
    
    resetButton.set(80,  ofGetHeight() / 2 - camHeight - 190,  120, 60);
    
    webcamButton.set(80, ofGetHeight() / 2 - camHeight - 190 + 100, 120, 120);
    
    geneButton.set(80,   ofGetHeight() / 2 - camHeight - 190 + 250, 186, 120);
    
    videoGrabber.setDesiredFrameRate(30);
    videoGrabber.initGrabber(camWidth, camHeight);
    capturedFrame.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    
}


void ofApp::update() {
    videoGrabber.update();
    
    // Check if the captureFrame flag is true
    if (captureFrame) {
        // Capture the frame from the webcam
        capturedFrame.setFromPixels(videoGrabber.getPixels());
        
        // Save the captured frame to a specific location
        string desktopPath = "C:/Users/InbalAmram/Documents/GitHub/D-iD/";
        string fileName = "image.jpeg";
        string filePath = desktopPath + fileName;
        capturedFrame.save(filePath);
        
        // Reset the captureFrame flag to false
        captureFrame = false;
        webcamButtonEnabled = false;
        geneButtonEnabled = true;
    }
    
    if(geneButtonEnabled == false) geneDataSend = 0;
    
    if(geneDataSend) {
        geneButtonEnabled     = false;
        buttonClicked[0]      = false;
        buttonClicked[1]      = false;
        buttonClicked[2]      = false;
        smallButtonClicked[0] = false;
        smallButtonClicked[1] = false;
        smallButtonClicked[2] = false;
        smallButtonClicked[3] = false;
        smallButtonClicked[4] = false;
        webcamButtonEnabled   = false;
    } 
    
    ofxOscMessage m;
    m.setAddress("/generation");
    m.addIntArg(geneDataSend);
    m.addIntArg(bigChoice);
    m.addIntArg(smallChoice);
    sender.sendMessage(m, false);
}

void ofApp::draw() {
    
    // Draw the camera feed above the large buttons
    int buttonHeight = 50;
    
    int camX = ofGetWidth() / 2 -  camWidth;
    int camY = ofGetHeight() / 2 - camHeight - buttonHeight - 140;
    videoGrabber.draw(camX, camY, camWidth * 2, camHeight * 2);
    
    for (int i = 0; i < buttons.size(); i++) {
        if (buttonClicked[i]) {
            ofSetColor(255, 0, 0);
        } else {
            ofSetColor(0, 255, 0);
        }
        ofDrawRectRounded(buttons[i], 3);
    }
    
    for (int i = 0; i < smallButtons.size(); i++) {
        if (smallButtonClicked[i]) {
            ofSetColor(255, 0, 0);
        } else {
            ofSetColor(0, 255, 0);
        }
        ofDrawRectRounded(smallButtons[i], 3);
    }
    
    // Display "Button Clicked" next to each clicked button
    for (int i = 0; i < buttons.size(); i++) {
        if (buttonClicked[i]) {
            ofSetColor(255);
            ofDrawBitmapString("Clicked", buttons[i].getX() + 10, buttons[i].getY() + 140);
            
            bigChoice = i + 1;
        }
        else {
            ofSetColor(255);
            ofDrawBitmapString(buttonNames[i], buttons[i].getX() + 10, buttons[i].getY() + 140);
        }
    }
    
    for (int i = 0; i < smallButtons.size(); i++) {
        if (smallButtonClicked[i]) {
            ofSetColor(255);
            ofDrawBitmapString("Clicked", smallButtons[i].getX() + 5, smallButtons[i].getY() + 110);
            
            smallChoice = i + 1;
        }
        else {
            ofSetColor(255);
            ofDrawBitmapString(smallButtonNames[i], smallButtons[i].getX() + 5, smallButtons[i].getY() + 110);
        }
    }
    
    // Draw the reset button
    if (resetButtonClicked) {
        ofSetColor(255, 0, 0);
    } else {
        ofSetColor(0, 0, 255);
    }
    
    ofDrawRectRounded(resetButton, 3);
    
    // Display "Reset" label for the reset button
    ofSetColor(255);
    ofDrawBitmapString("Reset", resetButton.getX() + 10, resetButton.getY() + 20);
    
    // Create the "Webcam" button
    if (webcamButtonEnabled) {
        ofColor webcamButtonColor(0, 0, 255);
        ofSetColor(webcamButtonColor);
        ofDrawRectRounded(webcamButton, 3);
        ofSetColor(255);
        ofDrawBitmapString("Webcam", webcamButton.getX() + 7, webcamButton.getY() + 32);
    } else {
        // If the "Webcam" button is not enabled, you can display it in a disabled state
        ofSetColor(100); // Change the color to gray or another disabled color
        ofDrawRectRounded(webcamButton, 3);
        ofSetColor(150); // Change the text color to a lighter gray
        ofDrawBitmapString("Webcam", webcamButton.getX() + 7, webcamButton.getY() + 32);
    }
    
    // Create the "Generation" button
    if (geneButtonEnabled) {
        ofColor geneButtonColor(0, 0, 255);
        ofSetColor(geneButtonColor);
        ofDrawRectRounded(geneButton, 3);
        ofSetColor(255);
        ofDrawBitmapString("Generation\n\nPlease wait 1 minute", geneButton.getX() + 7, geneButton.getY() + 32);
    }

    ofSetColor(255);
    ofDrawBitmapString(instructions, 1340, 120);
}


void ofApp::mousePressed(int x, int y, int button) {
    bool clickedButton = false;  // Flag to check if a button was clicked
    
    // Check if the mouse click is within the reset button
    if (resetButton.inside(x, y)) {
        // Reset all buttons to green
        for (int i = 0; i < buttons.size(); i++) {
            buttonClicked[i] = false;
            webcamButtonEnabled = false;
            geneButtonEnabled = false;
            geneDataSend = false;
        }
        for (int i = 0; i < smallButtons.size(); i++) {
            smallButtonClicked[i] = false;
            webcamButtonEnabled = false;
            geneButtonEnabled = false;
            geneDataSend = false;
        }
        
        resetButtonClicked = true;
    }
    
    // Check if the mouse click is within any of the buttons (both small and large)
    for (int i = 0; i < buttons.size(); i++) {
        if (buttons[i].inside(x, y)) {
            clickedButton = true;
            
            if (!resetButtonClicked) {
                // If the clicked button is already red, turn it green
                if (buttonClicked[i]) {
                    buttonClicked[i] = false;
                    webcamButtonEnabled = false;
                    geneButtonEnabled = false;
                    geneDataSend = false;
                } else {
                    // Turn the clicked button red and turn all other red buttons green
                    for (int j = 0; j < buttons.size(); j++) {
                        buttonClicked[j] = false;
                        webcamButtonEnabled = false;
                        geneButtonEnabled = false;
                        geneDataSend = false;
                    }
                    buttonClicked[i] = true;
                }
            }
        }
    }
    
    // Check if the mouse click is within any of the small buttons
    for (int i = 0; i < smallButtons.size(); i++) {
        if (smallButtons[i].inside(x, y)) {
            clickedButton = true;
            
            if (!resetButtonClicked) {
                // If the clicked button is already red, turn it green
                if (smallButtonClicked[i]) {
                    smallButtonClicked[i] = false;
                    webcamButtonEnabled = false;
                    geneButtonEnabled = false;
                    geneDataSend = false;
                } else {
                    // Turn the clicked button red and turn all other red buttons green
                    for (int j = 0; j < smallButtons.size(); j++) {
                        smallButtonClicked[j] = false;
                        webcamButtonEnabled = false;
                        geneButtonEnabled = false;
                        geneDataSend = false;
                    }
                    smallButtonClicked[i] = true;
                }
            }
        }
    }
    
    for (int i = 0; i < buttons.size(); i++) {
        for (int j = 0; j < smallButtons.size(); j++) {
            if (buttonClicked[i] == true && smallButtonClicked[j] == true) {
                webcamButtonEnabled = true;
            }
        }
    }
    
    // If a button was clicked, update the display for both small and large buttons
    if (clickedButton) {
        // Update the display for small buttons
        for (int i = 0; i < smallButtons.size(); i++) {
            if (smallButtonClicked[i]) {
                ofSetColor(255, 0, 0);
            } else {
                ofSetColor(0, 255, 0);
            }
            ofDrawRectangle(smallButtons[i]);
        }
        
        // Update the display for large buttons
        for (int i = 0; i < buttons.size(); i++) {
            if (buttonClicked[i]) {
                ofSetColor(255, 0, 0);
            } else {
                ofSetColor(0, 255, 0);
            }
            ofDrawRectangle(buttons[i]);
        }
    }
    
    // Check if the mouse click is within the reset button and reset its state
    if (resetButtonClicked) {
        resetButtonClicked = false;
    }
    
    // Check if the "Webcam" button is clicked and if it's enabled
    if (webcamButton.inside(x, y) && webcamButtonEnabled) {
        captureFrame = true;
    }
    
    if (geneButton.inside(x, y) && geneButtonEnabled) {
        geneDataSend = true;
    }
}



/* ############################################### */
void ofApp::keyPressed(int key) {
    if (key == 'f' || key == 'F') {
        ofToggleFullscreen();
    }
}
