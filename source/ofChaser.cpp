//
//  ofChaser.cpp
//  minim_04
//
//  Created by stephen clark on 2/20/13.
//
//

#include "constants.h"
#include "ofChaser.h"

ofChaser::ofChaser(float _a, float _b, float _c, float _d, float _targX, float _targY, float _extX, float _extY){

    a= _a;
    b= _b;
    c= _c;
    d= _d;
    targX= _targX;
    targY= _targY;
    extX= _extX;
    extY= _extY;
    
    target.set(targX, targY);
    extPoint.set(extX, extY);
    
    beginPoint.set(a, b);
    endPoint.set(c, d);
    
    force=0;
    
}

void ofChaser::update(){

    extPoint.x=extX;
    extPoint.y=extY;
    
    target.x=targX;
    target.y=targY;
    
    dir=target-endPoint;
    dir.normalize();
    
    deltaBody.x=targX-a;
    deltaBody.y=targY-b;
    
    deltaExt.x=extX-a;
    deltaExt.y=extY-b;
    
    distBody= sqrt(deltaBody.x * deltaBody.x + deltaBody.y * deltaBody.y);
    distExt= sqrt(deltaExt.x * deltaExt.x + deltaExt.y * deltaExt.y);
    
    if (distBody <= distExt) {
        c+=0.25*dir.x;
        d+=0.25*dir.y;
        
        c+=ofNoise(100)*10 * kCourtWidth / kWidth;
        d+=ofNoise(100)*10 * kCourtWidth / kWidth;

    } else{
        c-=0.7*dir.x;
        d-=0.7*dir.y;
        
        c-=ofNoise(100)*10 * kCourtWidth / kWidth;
        d-=ofNoise(100)*10 * kCourtWidth / kWidth;

    }
    if (c<=-kCourtWidth / 2.0) {
        c=-kCourtWidth / 2.0;
    }
    if (c>=kCourtWidth / 2.0) {
        c=kCourtWidth / 2.0;
    }
    if (d<=-kCourtHeight / 2.0) {
        d=-kCourtHeight / 2.0;
    }
    if (d>=kCourtHeight / 2.0) {
        d=kCourtHeight / 2.0;
    }

    

}

void ofChaser::draw(){
    ofSetColor(20, 40, 20);
    ofLine(a, b, c, d);
    
    
}