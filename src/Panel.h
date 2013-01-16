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
#include "ofxTurboJpeg.h"
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
		getSharedData().sequence.frameIndex = int(getSharedData().sequence.getLength()*getSharedData().frame);
		getSharedData().sequence.draw(0,0,ofGetWidth(),ofGetHeight());
		ofPushStyle();
		ofSetColor(getSharedData().backgroundColor);
		getSharedData().font.drawString(getName(), ofGetWidth() >> 1, ofGetHeight() >> 1);
		ofPopStyle();
	}
	void stateEnter()
	{
		getSharedData().sequence.setup("charlie_brown/");
	}
	
	void stateExit()
	{
		getSharedData().sequence.exit();
	}
	string getName()
	{
		return "PANEL1";
	}
};
class Panel2 : public Apex::ofxState<SharedData>
{
public:
	ofxThreadedImageLoader loader;
	
	float width,height,dx;
	
	ofRectangle rect;
	int col,row;
	ofRectangle screenRect;
	struct ImageData
	{
	public:
		ofImage image;
		ofPoint* pt;
		float alpha;
		bool isLoading;
	};
	struct ImageEntry
	{
	public:
		ImageEntry() {
			data = NULL;
		}
		ImageData *data;
		string filename;
	};
	
	vector<ImageData*> imagesData;
	
	
	deque<ImageEntry> images_to_load;
	
	void setup()
	{
		
		width = 10800;
		height = ofGetHeight();
		rect.width = 270;
		rect.height = 270;
		col  =width/rect.width;
		row  =height/rect.height;
		int i =0 ;
		for(int y = 0 ; y < row ; y++)
		{
			for(int x = 0 ; x < col ; x++)
			{
				ofPoint* pt = new ofPoint(x*rect.width,y*rect.height);
				//				ofImage* img = new ofImage();
				ImageData* data = new ImageData();
				
				data->pt = pt;
				data->isLoading = false;
				//				data->image = img;
				char name[256];
				//				sprintf(name,"pano/%04d.png",i);
				//				loader.loadFromDisk(data->image , name);
				
				imagesData.push_back(data);
				i++;
			}
		}
		screenRect.set(-200,-200,ofGetWidth()+200,ofGetHeight()+200);
		loader.startThread(true, false);
	}
	void update(){
		
		dx =  getSharedData().spin*-(width-ofGetWidth());
		int i = 0 ;
		vector<ImageData*>::iterator it;
		
		for(it=imagesData.begin() ; it!=imagesData.end() ; it++ )
		{
			ImageData* d = *it;
			//			ofImage *img = d->image;
			ofPoint * p = d->pt;
			if(screenRect.inside(p->x+dx, p->y) )
			{
				
				if(!d->image.isAllocated() && !d->isLoading)
				{
					//					d->image = new ofImage();
					char name[256];
					sprintf(name,"pano/%04d.jpg",i);
					//					d->image.loadImage(name);
					//					loader.loadFromDisk(&d->image, name);
					ImageEntry entry;
					d->isLoading = true;
					entry.data = d;
					
					entry.filename = name;
					images_to_load.push_back(entry);
				}
				
				if(d->alpha<255 && d->image.isAllocated())d->alpha+=5;
			}
			else
			{
				if(d->image.isAllocated())d->image.clear();
				//				if(d->image!=NULL)
				//				{
				//					d->image->~ofImage();
				//					d->image = NULL;
				//				}
				d->alpha = 0;
				
			}
			i++;
			i%=160;
		}
		while (images_to_load.size()>0)
		{
			ImageEntry entry = images_to_load.front();
			ofPoint * p = entry.data->pt;
			entry.data->isLoading = false;
			if(screenRect.inside(p->x+dx, p->y))
			{
				
				if(!entry.data->image.isAllocated())
				{
					getSharedData().turboJpeg.load(entry.filename,entry.data->image);
					//			entry.data->image.loadImage(entry.filename);
					ofLogVerbose() << entry.filename;
					//			ofLogVerbose("entry size") << images_to_load.size();
					entry.data->isLoading = false;
					entry.data->alpha=0;
					break;
				}
			}
			images_to_load.pop_front();
		}
	}
	void draw()
	{
		ofBackground(255, 0, 0);
		getSharedData().font.drawString(getName(), ofGetWidth() >> 1, ofGetHeight() >> 1);
		ofPushMatrix();
		ofTranslate(dx,0);
		vector<ImageData*>::iterator it;
		
		for(it=imagesData.begin() ; it!=imagesData.end() ; it++ )
		{
			ImageData* d = *it;
			ofImage *img = &d->image;
			ofPoint * p = d->pt;
			
			if(screenRect.inside(p->x+dx, p->y))
			{
				ofPushStyle();
				ofEnableAlphaBlending();
				ofSetColor(255,125);
				ofNoFill();
				ofRect(p->x,p->y,rect.width,rect.height);
				if(img!=NULL)
				{
					ofSetColor(255,d->alpha);
					if(img->isAllocated())img->draw(p->x,p->y,rect.width,rect.height);
				}
				ofPopStyle();
			}
		}
		ofPopMatrix();
		//		ofPushStyle();
		//		ofSetColor(128);
		//		ofFill();
		//		ofCircle(ofGetWidth() >> 1, ofGetHeight() >> 1,getSharedData().circleSize);
		//		ofPopStyle();
		
		if(getSharedData().drawRect)getSharedData().font.drawString("I am triggered by LABEL BUTTON", 0, (ofGetHeight() >> 1)+50);
	}
	void stateEnter()
	{
		vector < ImageData*>::iterator it;
		int i = 0;
		for(it=imagesData.begin() ; it!=imagesData.end() ; it++ )
		{
			ImageData* d = *it;
			
			ofPoint * p = d->pt;
			if(screenRect.inside(p->x+dx, p->y) )
			{
				
				//				if(d->image==NULL)
				{
					//					d->image = new ofImage();
					char name[256];
					sprintf(name,"pano/%04d.jpg",i);
//					d->image.loadImage(name);
					getSharedData().turboJpeg.load(name,d->image);
					//					loader.loadFromDisk(d->image, name);
					
				}
				
				if(d->alpha<255)d->alpha+=5;
			}
			i++;
		}
	}
	void stateExit()
	{
		vector<ImageData*>::iterator it;
		for(it=imagesData.begin() ; it!=imagesData.end() ; it++ )
		{
			ImageData* d = *it;
			
			//			if(d->image!=NULL)
			{
				d->image.clear();
				//				d->image->~ofImage();
				//				d->image = NULL;
			}
		}
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
		ofScale(getSharedData().circleSize, getSharedData().circleSize);
		ofRotateZ(getSharedData().rot);
		ofTranslate(-ofGetWidth() >> 1, -ofGetHeight() >> 1);
		ofRectangle rect = getSharedData().font.getStringBoundingBox(getSharedData().str, 0, 0);
		getSharedData().font.drawString(getSharedData().str, (ofGetWidth() >> 1)-(rect.width*0.5), ofGetHeight() >> 1);
		ofPopMatrix();
	}
	void stateEnter()
	{
		getSharedData().turboJpeg.load("image1.jpg",getSharedData().img1);
		getSharedData().turboJpeg.load("image2.jpg",getSharedData().img2);
		getSharedData().turboJpeg.load("image3.jpg",getSharedData().img3);
		getSharedData().turboJpeg.load("image4.jpg",getSharedData().img4);
//		getSharedData().img1.loadImage("image1.png");
//		getSharedData().img2.loadImage("image2.png");
//		getSharedData().img3.loadImage("image3.png");
//		getSharedData().img4.loadImage("image4.png");
	}
	
	void stateExit()
	{
		getSharedData().img1.clear();
		getSharedData().img2.clear();
		getSharedData().img3.clear();
		getSharedData().img4.clear();
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