//
//  Panel1.h
//  animationDemo
//
//  Created by james KONG on 2/1/13.
//
//

#pragma once

#include "ofxState.h"
#include "SharedData.h"

class Panel1 : public Apex::ofxState<SharedData>
{
public:
	void update(){
	}
	void draw()
	{
		
//		int r = getSharedData().backgroundColor.r;
//		int g = getSharedData().backgroundColor.g;
//		int b = getSharedData().backgroundColor.b;
		ofSetColor(ofColor::white);
		getSharedData().sequence.getFrameAtPercent(getSharedData().frame)->draw(0,0,ofGetWidth(),ofGetHeight());
		ofPushStyle();
		ofSetColor(getSharedData().backgroundColor);
		getSharedData().font.drawString(getName(), ofGetWidth() >> 1, ofGetHeight() >> 1);
		ofPopStyle();
	}
	string getName()
	{
		return "PANEL1";
	}
};
class Panel2 : public Apex::ofxState<SharedData>
{
public:
	void update(){
	}
	void draw()
	{
		ofBackground(255, 0, 0);
		getSharedData().font.drawString(getName(), ofGetWidth() >> 1, ofGetHeight() >> 1);
		ofPushStyle();
		ofSetColor(128);
		ofFill();
		ofCircle(ofGetWidth() >> 1, ofGetHeight() >> 1,getSharedData().circleSize);
		ofPopStyle();
		
		if(getSharedData().drawRect)getSharedData().font.drawString("I am triggered by LABEL BUTTON", 0, (ofGetHeight() >> 1)+50);
	}
	string getName()
	{
		return "PANEL2";
	}
};
class Panel3 : public Apex::ofxState<SharedData>
{
public:
	void update(){
	}
	void draw()
	{
		ofBackground(0, 255, 0);
		getSharedData().font.drawString(getName(), ofGetWidth() >> 1, 50);
		
		if(getSharedData().bDraw1){
			getSharedData().img1.draw(0,ofGetHeight()>>2);
		}
		if(getSharedData().bDraw2){
			getSharedData().img2.draw(ofGetWidth()*(1/4.0f),ofGetHeight()>>2);
		}
		if(getSharedData().bDraw3){
			getSharedData().img3.draw(ofGetWidth()*(0.5),ofGetHeight()>>2);
		}
		if(getSharedData().bDraw4){
			getSharedData().img4.draw(ofGetWidth()*(3/4.0),ofGetHeight()>>2);
		}
		
		ofPushMatrix();
		ofTranslate(ofGetWidth() >> 1, ofGetHeight() >> 1);
		ofRotateZ(getSharedData().rot);
		ofTranslate(-ofGetWidth() >> 1, -ofGetHeight() >> 1);
		ofRectangle rect = getSharedData().font.getStringBoundingBox(getSharedData().str, 0, 0);
		getSharedData().font.drawString(getSharedData().str, (ofGetWidth() >> 1)-(rect.width*0.5), ofGetHeight() >> 1);
		ofPopMatrix();
	}
	string getName()
	{
		return "PANEL3";
	}
};
class Panel4 : public Apex::ofxState<SharedData>
{
public:
	void update(){
	}
	void draw()
	{
		ofBackground(0, 0, 255);
		ofPushMatrix();
		ofTranslate(getSharedData().scroll);
		for (int i = 0 ; i < 20 ; i++) {
			ofPushStyle();
			if(getSharedData().toggles[i])
			{
				ofSetColor(255,0,0);
			}
			else
			{
				ofSetColor(255);
			}
			getSharedData().font.drawString("LABLE_"+ofToString(i),(ofGetWidth() >> 1),50*1.5*i+50);
			ofPushStyle();
		}
		ofPopMatrix();
		ofSetColor(255);
		getSharedData().font.drawString(getName()+"_SCROLLABLE", 0, ofGetHeight() >> 1);
		
	}
	string getName()
	{
		return "PANEL4";
	}
};