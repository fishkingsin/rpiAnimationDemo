#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	glDisable(GL_DEPTH_TEST);
	ofSetLogLevel(OF_LOG_NOTICE);
	stateMachine.getSharedData().counter = 0;
	stateMachine.getSharedData().lastUpdate = ofGetElapsedTimeMillis();
	stateMachine.getSharedData().font.loadFont("vag.ttf", 50);
	
	//	stateMachine.getSharedData().img1.loadImage("image1.png");
	//	stateMachine.getSharedData().img2.loadImage("image2.png");
	//	stateMachine.getSharedData().img3.loadImage("image3.png");
	//	stateMachine.getSharedData().img4.loadImage("image4.png");
	//	stateMachine.getSharedData().sequence.setup("charlie_brown/");
	stateMachine.getSharedData().spin = 0;
	
	stateMachine.addState(new Panel1());
	stateMachine.addState(new Panel2());
	stateMachine.addState(new Panel3());
	stateMachine.addState(new Panel4());
	receiver.setup(PORT);
	stateMachine.changeState("PANEL1");
}

//--------------------------------------------------------------
void testApp::update(){
	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
		
		// check for mouse moved message
		if(m.getAddress() == "/PANEL1"){
			stateMachine.changeState("PANEL1");
		}
		// check for mouse button message
		else if(m.getAddress() == "/PANEL2"){
			stateMachine.changeState("PANEL2");
		}
		else if(m.getAddress() == "/PANEL3"){
			stateMachine.changeState("PANEL3");
		}
		else if(m.getAddress() == "/PANEL4"){
			stateMachine.changeState("PANEL4");
		}
		else if(m.getAddress() == "/MATRIX3"){
			stateMachine.getSharedData().bDraw1 = m.getArgAsInt32(0);
			stateMachine.getSharedData().bDraw2 = m.getArgAsInt32(1);
			stateMachine.getSharedData().bDraw3 = m.getArgAsInt32(2);
			stateMachine.getSharedData().bDraw4 = m.getArgAsInt32(3);
		}
		else if(m.getAddress() == "/RED"){
			stateMachine.getSharedData().backgroundColor.r = m.getArgAsFloat(0);
		}
		else if(m.getAddress() == "/GREEN"){
			stateMachine.getSharedData().backgroundColor.g = m.getArgAsFloat(0);
		}
		else if(m.getAddress() == "/BLUE"){
			stateMachine.getSharedData().backgroundColor.b = m.getArgAsFloat(0);
		}
		else if(m.getAddress() == "/R2SLIDER"){
			stateMachine.getSharedData().rot = m.getArgAsFloat(0);
		}
		else if(m.getAddress() == "/DROP DOWN LIST"){
			stateMachine.getSharedData().str = m.getArgAsString(0);
		}
		else if(m.getAddress() == "/LABEL BUTTON"){
			stateMachine.getSharedData().drawRect = m.getArgAsInt32(0);
		}
		else if(m.getAddress() == "/NORTH SOUTH"){
			stateMachine.getSharedData().circleSize = m.getArgAsFloat(0);
			//			ofLogVerbose(m.getAddress()) << m.getArgAsFloat(0);
		}
		else if(m.getAddress() == "/FRAME"){
			//			ofLogVerbose("FRAME") << m.getArgAsFloat(0);
			stateMachine.getSharedData().frame = m.getArgAsFloat(0);
			//			ofLogVerbose(m.getAddress()) << m.getArgAsFloat(0);
		}
		else if(m.getAddress() == "/SCROLLABLE/Y"){
			stateMachine.getSharedData().scroll.y = m.getArgAsFloat(0);
		}
		else if(m.getAddress() == "/ENABLE_SCREENSAVER"){
			
			stateMachine.getSharedData().enableScreensaver = m.getArgAsInt32(0);
		}

		
		else if(m.getAddress() == "/SPINNER"){
			
			stateMachine.getSharedData().spin = m.getArgAsFloat(0);
		}
		else if(m.getAddress().find("LABEL_BUTTON_")!=string::npos){
			ofLogVerbose("LABEL_BUTTON_") << m.getAddress().substr(14,string::npos);
			
			int index = atoi(m.getAddress().substr(14,string::npos).c_str());
			if(index<20)stateMachine.getSharedData().toggles[index] = m.getArgAsInt32(0);
			//			ofLogVerbose(m.getAddress()) << m.getArgAsFloat(0);
		}
		else{
			// unrecognized message: display on the bottom of the screen
			string msg_string;
			msg_string = m.getAddress();
			msg_string += ": ";
			for(int i = 0; i < m.getNumArgs(); i++){
				// get the argument type
				msg_string += m.getArgTypeName(i);
				msg_string += ":";
				// display the argument - make sure we get the right type
				if(m.getArgType(i) == OFXOSC_TYPE_INT32){
					msg_string += ofToString(m.getArgAsInt32(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
					msg_string += ofToString(m.getArgAsFloat(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
					msg_string += m.getArgAsString(i);
				}
				else{
					msg_string += "unknown";
				}
			}
			ofLogVerbose() << msg_string;
			
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
	
}