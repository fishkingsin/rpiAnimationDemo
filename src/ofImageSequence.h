//
//  ofImageSequence.h
//  rpiAnimationDemo
//
//  Created by james KONG on 4/1/13.
//
//

#pragma once
#include "ofMain.h"
class ofImageSequence
{
public:
	void exit()
	{
		while (!images.empty()) {
			ofImage* img=&images.back();
			img->clear();
			img->~ofImage();
			images.pop_back();
		}
	}
	void setup(string path)
	{
//		ofBackground(0);
//		ofSetWindowTitle("The Moon is made of plops");
		
		// read the directory for the images
		// we know that they are named in seq
		ofDirectory dir;
		dir.allowExt("png");
		int nFiles = dir.listDir(path);
		if(nFiles) {
			
			for(int i=0; i<dir.numFiles(); i++) {
				
				// add the image to the vector
				string filePath = dir.getPath(i);
				images.push_back(ofImage());
				images.back().loadImage(filePath);
				
			}
			
		}
		else printf("Could not find folder\n");
		
		// this toggle will tell the sequence
		// be be indepent of the app fps
//		bFrameIndependent = true;
		
		// this will set the speed to play
		// the animation back we set the
		// default to 24fps
//		sequenceFPS = 24;
		
		// set the app fps
//		appFPS = 60;
		frameIndex = 0;
	}
    void update()
	{
		
	}
    void draw(float x, float y, float w, float h )
	{
		// we need some images if not return
//		if((int)images.size() <= 0) {
//			ofSetColor(255);
//			ofDrawBitmapString("No Images...", 150, ofGetHeight()/2);
//			return;
//		}
		
		// this is the total time of the animation based on fps
//		float totalTime = images.size() / sequenceFPS;
		
		
//		int frameIndex = 0;
//
//		if(bFrameIndependent) {
//			// calculate the frame index based on the app time
//			// and the desired sequence fps. then mod to wrap
//			frameIndex = (int)(ofGetElapsedTimef() * sequenceFPS) % images.size();
//		}
//		else {
//			// set the frame index based on the app frame
//			// count. then mod to wrap.
//			frameIndex = ofGetFrameNum() % images.size();
//		}
		
		// draw the image sequence at the new frame count
		ofSetColor(255);
		images[frameIndex].draw(x,y,w,h);
		
		
		// draw where we are in the sequence
//		float x = 0;
//		for(int offset = 0; offset < 5; offset++) {
//			int i = (frameIndex + offset) % images.size();
//			ofSetColor(255);
//			images[i].draw(200+x, ofGetHeight()-40, 40, 40);
//			x += 40;
//		}

	}
	int getLength()
	{
		return images.size();
	}
	int frameIndex;
//	int   appFPS;
//    float sequenceFPS;
//    bool  bFrameIndependent;
    vector <ofImage> images;
};

