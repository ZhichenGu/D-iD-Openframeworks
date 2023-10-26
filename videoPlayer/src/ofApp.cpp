#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    receiver.setup(PORT);

    string filePath_0 = "C:/Users/InbalAmram/Desktop/Video folder/0.mp4";
    if (videoPlayer0.load(filePath_0)) {
        //        videoPlayer0.play();
    }

    string filePath_1 = "C:/Users/InbalAmram/Desktop/Video folder/1.mp4";
    if (videoPlayer1.load(filePath_1)) {
        //        videoPlayer1.play();
    }

    string filePath_2 = "C:/Users/InbalAmram/Desktop/Video folder/2.mp4";
    if (videoPlayer2.load(filePath_2)) {
        //        videoPlayer2.play();
    }

    string filePath_3 = "C:/Users/InbalAmram/Desktop/Video folder/3.mp4";
    if (videoPlayer3.load(filePath_3)) {
        //        videoPlayer3.play();
    }

    string filePath_4 = "C:/Users/InbalAmram/Desktop/Video folder/4.mp4";
    if (videoPlayer4.load(filePath_4)) {
        //        videoPlayer4.play();
    }

    string filePath_5 = "C:/Users/InbalAmram/Desktop/Video folder/5.mp4";
    if (videoPlayer5.load(filePath_5)) {
        //        videoPlayer5.play();
    }

    string filePath_6 = "C:/Users/InbalAmram/Desktop/Video folder/6.mp4";
    if (videoPlayer6.load(filePath_6)) {
        //        videoPlayer6.play();
    }

    string filePath_7 = "C:/Users/InbalAmram/Desktop/Video folder/7.mp4";
    if (videoPlayer7.load(filePath_7)) {
        //        videoPlayer7.play();
    }

    string filePath_8 = "C:/Users/InbalAmram/Desktop/Video folder/8.mp4";
    if (videoPlayer8.load(filePath_8)) {
        //        videoPlayer8.play();
    }

    string filePath_9 = "C:/Users/InbalAmram/Desktop/Video folder/9.mp4";
    if (videoPlayer9.load(filePath_9)) {
        //        videoPlayer9.play();
    }

    number = 10;
}

//--------------------------------------------------------------
void ofApp::update() {
    videoPlayer0.update();
    videoPlayer1.update();
    videoPlayer2.update();
    videoPlayer3.update();
    videoPlayer4.update();
    videoPlayer5.update();
    videoPlayer6.update();
    videoPlayer7.update();
    videoPlayer8.update();
    videoPlayer9.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(0);

    while (receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        receiver.getNextMessage(m);

        if (m.getAddress() == "/data") {
            number = m.getArgAsInt(0);
        }
    }

    if (number == 0) videoPlaying(videoPlayer0), videoStop(videoPlayer1, videoPlayer2, videoPlayer3, videoPlayer4,
        videoPlayer5, videoPlayer6, videoPlayer7, videoPlayer8,
        videoPlayer9);

    if (number == 1) videoPlaying(videoPlayer1), videoStop(videoPlayer0, videoPlayer2, videoPlayer3, videoPlayer4,
        videoPlayer5, videoPlayer6, videoPlayer7, videoPlayer8,
        videoPlayer9);

    if (number == 2) videoPlaying(videoPlayer2), videoStop(videoPlayer1, videoPlayer0, videoPlayer3, videoPlayer4,
        videoPlayer5, videoPlayer6, videoPlayer7, videoPlayer8,
        videoPlayer9);

    if (number == 3) videoPlaying(videoPlayer3), videoStop(videoPlayer1, videoPlayer2, videoPlayer0, videoPlayer4,
        videoPlayer5, videoPlayer6, videoPlayer7, videoPlayer8,
        videoPlayer9);

    if (number == 4) videoPlaying(videoPlayer4), videoStop(videoPlayer1, videoPlayer2, videoPlayer3, videoPlayer0,
        videoPlayer5, videoPlayer6, videoPlayer7, videoPlayer8,
        videoPlayer9);

    if (number == 5) videoPlaying(videoPlayer5), videoStop(videoPlayer1, videoPlayer2, videoPlayer3, videoPlayer4,
        videoPlayer0, videoPlayer6, videoPlayer7, videoPlayer8,
        videoPlayer9);

    if (number == 6) videoPlaying(videoPlayer6), videoStop(videoPlayer1, videoPlayer2, videoPlayer3, videoPlayer4,
        videoPlayer5, videoPlayer0, videoPlayer7, videoPlayer8,
        videoPlayer9);

    if (number == 7) videoPlaying(videoPlayer7), videoStop(videoPlayer1, videoPlayer2, videoPlayer3, videoPlayer4,
        videoPlayer5, videoPlayer6, videoPlayer0, videoPlayer8,
        videoPlayer9);

    if (number == 8) videoPlaying(videoPlayer8), videoStop(videoPlayer1, videoPlayer2, videoPlayer3, videoPlayer4,
        videoPlayer5, videoPlayer6, videoPlayer7, videoPlayer0,
        videoPlayer9);

    if (number == 9) videoPlaying(videoPlayer9), videoStop(videoPlayer1, videoPlayer2, videoPlayer3, videoPlayer4,
        videoPlayer5, videoPlayer6, videoPlayer7, videoPlayer8,
        videoPlayer0);
    else {
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 'f' || key == 'F') {
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void ofApp::videoPlaying(ofVideoPlayer videoPlayer) {
    videoPlayer.play();

    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofRotateDeg(270);
    int modifyY = (1920 - 1080) / 2;
    ofSetColor(255);
    videoPlayer.draw(-ofGetWidth() / 4 - 60, -ofGetHeight() / 2 - modifyY, 1080, 1920);
    ofPopMatrix();
}

void ofApp::videoStop(ofVideoPlayer videoPlayer1, ofVideoPlayer videoPlayer2, ofVideoPlayer videoPlayer3,
    ofVideoPlayer videoPlayer4, ofVideoPlayer videoPlayer5, ofVideoPlayer videoPlayer6,
    ofVideoPlayer videoPlayer7, ofVideoPlayer videoPlayer8, ofVideoPlayer videoPlayer9) {

    videoPlayer1.stop();
    videoPlayer2.stop();
    videoPlayer3.stop();
    videoPlayer4.stop();
    videoPlayer5.stop();
    videoPlayer6.stop();
    videoPlayer7.stop();
    videoPlayer8.stop();
    videoPlayer9.stop();

}
