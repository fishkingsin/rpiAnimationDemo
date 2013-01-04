#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
#ifdef TARGET_OSX
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1920,1080, OF_WINDOW);			// <-------- setup the GL context
#else
	ofSetupOpenGL(1920,1080, OF_WINDOW);			// <-------- setup the GL context
#endif
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
