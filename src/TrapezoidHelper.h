
#pragma once

#include "ofMain.h"
#include "ofxHomography.h"

namespace np{

class TrapezoidHelper {

public:
    ofParameterGroup & setup( int pw, int ph, std::string name="trapezoid correction" );
    
    ofParameterGroup parameters;
        ofParameter<int>   xOffset;
        ofParameter<int>   yOffset;
        ofParameter<float> top;
        ofParameter<float> bottom;
        ofParameter<float> stretch;
        ofParameter<float> scale;
        ofParameter<bool> bDrawCorners;
        
    void calculateHomography();
    void drawCorners();
    
    void begin();
    void end();

    ofPoint originalCorners[4];
    ofMatrix4x4 homography;    
    
    ofParameterGroup & label (std::string name);     

private:
	void onFloatChange( float & value );
	void onIntChange(   int & value );

	int pw;
	int ph;
    ofPoint distortedCorners[4];
    void updateHomographyCall( bool & value );
    
};

}
