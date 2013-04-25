//
//  ofChaser.h
//  minim_04
//
//  Created by stephen clark on 2/20/13.
//
//

#ifndef __minim_05__ofChaser__
#define __minim_05__ofChaser__

#include "ofMain.h"
#include <iostream>

class ofChaser{
public:
    void update();
    void draw();
    
    ofChaser(float a, float b, float c, float d, float targX, float targY, float extX, float extY);
    
    float a,b,c,d, targX,targY, extX,extY;
    
    ofPoint extPoint;
    ofPoint beginPoint;
    
    ofPoint target;
    ofPoint endPoint;
    ofVec2f dir;
    
    ofPoint deltaBody;
    ofPoint deltaExt;
    
    ofVec2f momentum;
    
    float distBody, distExt;
    float force;
    
    
};

#endif /* defined(__minim_04__ofChaser__) */
