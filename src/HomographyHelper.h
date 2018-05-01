
#pragma once

#include "ofMain.h"
#include "ofxHomography.h"

namespace np{

class HomographyHelper {

public:
    void setup( int pw, int ph );
    
    ofParameterGroup ui;
        vector<ofParameter<int>> cornersX;
        vector<ofParameter<int>> cornersY;
        ofParameter<bool> bDrawCorners;
        ofParameter<bool> updateHomography;
        
    void calculateHomography();
    void drawCorners();
    
    void begin();
    void end();


    ofPoint originalCorners[4];
    ofMatrix4x4 homography;         

private:
    ofPoint distortedCorners[4];
    void updateHomographyCall( bool & value );
    
    static int constructed;
};

}
