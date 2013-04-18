#include "ofMain.h"
#include "witchball.h"

int main(){
	ofSetupOpenGL(1200,768, OF_FULLSCREEN);			// <-------- setup the GL context

	ofRunApp(new WitchBall());
}
