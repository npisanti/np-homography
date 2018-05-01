
#include "TrapezoidHelper.h"

ofParameterGroup &  np::TrapezoidHelper::setup( int pw, int ph, std::string name ){
	this->pw = pw;
	this->ph = ph;
	
    parameters.setName( name );
    parameters.add( xOffset.set("x offset", 0, -pw/2, pw/2) );
    parameters.add( yOffset.set("y offset", 0, -ph/2, ph/2) );
	parameters.add( top.set("top stretch", 1.0f, 0.2f, 2.0f) );
	parameters.add( bottom.set("bottom stretch", 1.0f, 0.2f, 2.0f) );
	parameters.add( stretch.set("v stretch", 1.0f, 0.2f, 2.0f) );
	parameters.add( scale.set("scaling", 1.0f, 0.2f, 1.5f) );
    parameters.add( bDrawCorners.set("draw corners", false) );


	originalCorners[0].set(0, 0);
	originalCorners[1].set(pw, 0);
	originalCorners[2].set(pw, ph);
	originalCorners[3].set(0, ph);
	
	distortedCorners[0].set( 0, 0 );
	distortedCorners[1].set( pw, 0 );
	distortedCorners[2].set( pw, ph );
	distortedCorners[3].set( 0, ph );

	xOffset.addListener( this, &TrapezoidHelper::onIntChange);
	yOffset.addListener( this, &TrapezoidHelper::onIntChange);
	top.addListener( this, &TrapezoidHelper::onFloatChange);
	bottom.addListener( this, &TrapezoidHelper::onFloatChange);
	stretch.addListener( this, &TrapezoidHelper::onFloatChange);
	scale.addListener( this, &TrapezoidHelper::onFloatChange);
	
	homography = ofxHomography::findHomography(originalCorners, distortedCorners );
    
    return parameters;
}

void np::TrapezoidHelper::calculateHomography() {
	
	float w = pw * scale;
	float h = ph * scale;
	
	float ymargin = h*(stretch-1.0f)*0.5f;
	float y01 = -ymargin;
	float y23 = h + ymargin;
	
	float topmargin = w * (top-1.0f)*0.5f;
	float x0 = -topmargin;
	float x1 = w + topmargin;
	
	float botmargin = w * (bottom-1.0f)*0.5f;
	float x2 = w + botmargin;
	float x3 = - botmargin;
	
	float xoff = xOffset + (pw-w)*0.5f;
	float yoff = yOffset + (ph-h)*0.5f;
	
    distortedCorners[0].set( x0 + xoff, y01 + yoff );
    distortedCorners[1].set( x1 + xoff, y01 + yoff  );
    distortedCorners[2].set( x2 + xoff, y23 + yoff  );
    distortedCorners[3].set( x3 + xoff, y23 + yoff  );
    homography = ofxHomography::findHomography(originalCorners, distortedCorners);
}
    
    
ofParameterGroup & np::TrapezoidHelper::label (std::string name){
    parameters.setName( name );
    return parameters;
}    

void np::TrapezoidHelper::begin() {
	ofPushMatrix();
    ofMultMatrix(homography);
}

void np::TrapezoidHelper::end() {
    ofPopMatrix();
	drawCorners();
}

void np::TrapezoidHelper::drawCorners() {

    if(bDrawCorners){
        ofPushStyle();
        ofFill();
        ofSetColor( 255, 0, 0 );
        for( int i=0; i<4; ++i ){
            ofDrawCircle( distortedCorners[i].x, distortedCorners[i].y, 6 );
        }        
        ofPopStyle();
    }
}

void np::TrapezoidHelper::onFloatChange( float & value ) {
	calculateHomography();
}

void np::TrapezoidHelper::onIntChange( int & value ) {
	calculateHomography();
}
