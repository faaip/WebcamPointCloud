#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(66,66,66);
    
    //initialize the video grabber
    vidGrabber.setVerbose(true);
    vidGrabber.setup(320,240);
    
    //store the width and height for convenience
    int width = vidGrabber.getWidth();
    int height = vidGrabber.getHeight();
    
    //add one vertex to the mesh for each pixel
    for (int y = 0; y < height; y++){
        for (int x = 0; x<width; x++){
            mainMesh.addVertex(ofPoint(x,y,0));	// mesh index = x + y*width
												// this replicates the pixel array within the camera bitmap...
            mainMesh.addColor(ofFloatColor(0,0,0));  // placeholder for colour data, we'll get this from the camera
        }
    }
    
    for (int y = 0; y<height-1; y++){
        for (int x=0; x<width-1; x++){
            mainMesh.addIndex(x+y*width);				// 0
            mainMesh.addIndex((x+1)+y*width);			// 1
            mainMesh.addIndex(x+(y+1)*width);			// 10
            
            mainMesh.addIndex((x+1)+y*width);			// 1
            mainMesh.addIndex((x+1)+(y+1)*width);		// 11
            mainMesh.addIndex(x+(y+1)*width);			// 10
        }
    }
    
    extrusionAmount = 300.0;
    cam.setDistance(275);
    
    // GUI setup
    gui.setup("GUI");
    gui.add(ampFactor.set("amp factor",0.5,0,1));
    gui.add(flip.set("flip",true));
    gui.add(camEnabled.set("cam mvt",true));
    gui.add(drawFace.set("draw mesh",false));
    gui.add(drawWireframe.set("draw wireframe", false));
    gui.add(drawPointcloud.set("draw pointcloud",true));
    

}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle("fps: " + ofToString(ofGetFrameRate()) +  " cam dist: " + ofToString(cam.getDistance()));
    
    //grab a new frame
    vidGrabber.update();
    
    //update the mesh if we have a new frame
    if (vidGrabber.isFrameNew()){
        //this determines how far we extrude the mesh
        for (int i=0; i<vidGrabber.getWidth()*vidGrabber.getHeight(); i++){
            
            ofFloatColor sampleColor(vidGrabber.getPixels()[i*3]/255.f,				// r
                                     vidGrabber.getPixels()[i*3+1]/255.f,			// g
                                     vidGrabber.getPixels()[i*3+2]/255.f);			// b
            
            //now we get the vertex aat this position
            //we extrude the mesh based on it's brightness
            ofVec3f tmpVec = mainMesh.getVertex(i);
            tmpVec.z = sampleColor.getBrightness() * (extrusionAmount*ampFactor);
            mainMesh.setVertex(i, tmpVec);
            
            mainMesh.setColor(i, sampleColor);
        }
    }
    
    if(flip){cam.setScale(-1,-1,1);}else{cam.setScale(1,-1,1);}
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(20);
    ofEnableDepthTest();
    cam.begin();
    
    //You can either draw the mesh or the wireframe
    ofPushMatrix();
    ofTranslate(-vidGrabber.getWidth()/2,-vidGrabber.getHeight()/2);
    if(drawWireframe) {mainMesh.drawWireframe();}else
        if(drawFace){mainMesh.drawFaces();}else
    if(drawPointcloud)mainMesh.drawVertices();
    ofPopMatrix();
    cam.end();
    
    if( !hideGui ){
        ofDisableDepthTest();
        gui.draw();
    }
    if(camEnabled){cam.enableMouseInput();}else{cam.disableMouseInput();}
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'h' || key == 'H'){
        hideGui = !hideGui;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
