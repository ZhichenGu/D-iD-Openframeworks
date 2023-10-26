#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	//tweak window settings
	//ofGLFWWindowSettings settings;
	//settings.setSize(1920, 1080);
	//settings.setPosition(glm::vec2(1921, 0));


	////make the window
	//auto mainWindow = ofCreateWindow(settings);

	////run the app 
	//shared_ptr<ofApp> mainApp(new ofApp);

	//ofRunApp(mainWindow, mainApp);
	//ofRunMainLoop();

	// Tweak window settings
	ofGLFWWindowSettings settings;
	settings.setSize(1920, 1110);
	settings.setPosition(glm::vec2(1921, 30)); // Set the position to (0, 0)
	//settings.windowMode = OF_FULLSCREEN;   // Set the window mode to fullscreen

	// Create the window
	auto mainWindow = ofCreateWindow(settings);

	// Run the app
	shared_ptr<ofApp> mainApp(new ofApp);

	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();
}
