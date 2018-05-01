#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    fbo.allocate( PROJECTOR_WIDTH, PROJECTOR_HEIGHT );
    homography.setup( PROJECTOR_WIDTH, PROJECTOR_HEIGHT );

    gui.setup("", "settings.xml", ofGetWidth()-220, 20 );
    gui.add( homography.ui );

}

//--------------------------------------------------------------
void ofApp::update(){
    fbo.begin();
		ofSetLineWidth( 1.5f );
        ofClear(0, 255, 0, 255);
        ofSetColor(0);
        ofNoFill();
        float cx = fbo.getWidth()*0.5f;
        float cy = fbo.getHeight()*0.5f;
        ofDrawLine( 0, cy, fbo.getWidth(), cy  );
        ofDrawLine( cx, 0, cx, fbo.getHeight() );
        ofDrawRectangle(cx-50, cy-50, 100, 100);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    fbo.draw(0, 0);
    
    gui.draw();
}

void ofApp::drawSecondWindow(ofEventArgs& args){
    homography.begin();
        ofBackground(30);
        ofSetColor(255);
        fbo.draw(0, 0);        
    homography.end();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch( key ){
        case 'h':
            homography.calculateHomography();
        break;
        
        case 't': homography.top = 1.0f; break;
        case 'b': homography.bottom = 1.0f; break;
        case 'v': homography.stretch = 1.0f; break;
        case 's': homography.scale = 1.0f; break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){ }
//--------------------------------------------------------------
