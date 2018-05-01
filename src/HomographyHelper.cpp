
#include "HomographyHelper.h"

int np::HomographyHelper::constructed = 0;

void np::HomographyHelper::setup( int pw, int ph ){
    cornersX.resize(4);
    cornersY.resize(4);
    ui.setName("homography " + ofToString(constructed++));
    ui.add( cornersX[0].set("x0", 0,  0, pw) );
    ui.add( cornersY[0].set("y0", 0,  0, ph) );
    ui.add( cornersX[1].set("x1", pw, 0, pw) );
    ui.add( cornersY[1].set("y1", 0,  0, ph) );
    ui.add( cornersX[2].set("x2", pw, 0, pw) );
    ui.add( cornersY[2].set("y2", ph, 0, ph) );
    ui.add( cornersX[3].set("x3", 0,  0, pw) );
    ui.add( cornersY[3].set("y3", ph, 0, ph) );
    ui.add( bDrawCorners.set("draw corners", true) );
    ui.add( updateHomography.set("update homography", false) );

	originalCorners[0].set(0, 0);
	originalCorners[1].set(pw, 0);
	originalCorners[2].set(pw, ph);
	originalCorners[3].set(0, ph);
	
	distortedCorners[0].set( cornersX[0], cornersY[0] );
	distortedCorners[1].set( cornersX[1], cornersY[1] );
	distortedCorners[2].set( cornersX[2], cornersY[2] );
	distortedCorners[3].set( cornersX[3], cornersY[3] );
    
	homography = ofxHomography::findHomography(originalCorners, distortedCorners );
    updateHomography.addListener( this, &np::HomographyHelper::updateHomographyCall );
}

void np::HomographyHelper::calculateHomography() {
    distortedCorners[0].set( cornersX[0], cornersY[0] );
    distortedCorners[1].set( cornersX[1], cornersY[1] );
    distortedCorners[2].set( cornersX[2], cornersY[2] );
    distortedCorners[3].set( cornersX[3], cornersY[3] );
    homography = ofxHomography::findHomography(originalCorners, distortedCorners);
}

void np::HomographyHelper::updateHomographyCall( bool & value ) {
    if( updateHomography ){
        calculateHomography();
        updateHomography = false;
    }
}
    
void np::HomographyHelper::begin() {
	ofPushMatrix();
    ofMultMatrix(homography);
}

void np::HomographyHelper::end() {
    ofPopMatrix();
	drawCorners();
}

void np::HomographyHelper::drawCorners() {

    if(bDrawCorners){
        ofPushStyle();
        ofFill();
        ofSetColor( 255, 0, 0 );
        for( int i=0; i<4; ++i ){
            ofDrawCircle( cornersX[i], cornersY[i], 6 );
        }        
        ofPopStyle();
    }
}
