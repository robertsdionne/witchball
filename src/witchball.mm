#include <Box2D/Box2D.h>

#include "constants.h"
#include "controller.h"
#include "playscreen.h"
#include "screen.h"
#include "slider.h"
#include "utilities.h"
#include "witchball.h"

WitchBall::WitchBall() : current_screen(nullptr) {}

WitchBall::~WitchBall() {
  if (current_screen) {
    delete current_screen;
    current_screen = nullptr;
  }
}

void WitchBall::setup() {
	//ofxAccelerometer.setup();
	//If you want a landscape oreintation
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	ofBackground(127,127,127);
  current_screen = new PlayScreen();
  current_screen->Setup();
}

void WitchBall::update() {
  if (current_screen) {
    current_screen->Update();
  }
}

void WitchBall::draw() {
  if (current_screen) {
    current_screen->Draw();
  }
}

void WitchBall::exit(){
	
}

void WitchBall::touchDown(ofTouchEventArgs & touch){
	if (current_screen) {
    current_screen->touchDown(touch);
  }
}

void WitchBall::touchMoved(ofTouchEventArgs & touch){
	if (current_screen) {
    current_screen->touchMoved(touch);
  }
}

void WitchBall::touchUp(ofTouchEventArgs & touch){
	if (current_screen) {
    current_screen->touchUp(touch);
  }
}

void WitchBall::touchDoubleTap(ofTouchEventArgs & touch){
	if (current_screen) {
    current_screen->touchDoubleTap(touch);
  }
}

void WitchBall::touchCancelled(ofTouchEventArgs & touch){
	if (current_screen) {
    current_screen->touchCancelled(touch);
  }
}

void WitchBall::lostFocus(){
	
}

void WitchBall::gotFocus(){
	
}

void WitchBall::gotMemoryWarning(){
	
}

void WitchBall::deviceOrientationChanged(int newOrientation){
	
}

void WitchBall::RestartScene() {
  if (current_screen) {
    delete current_screen;
    current_screen = nullptr;
  }
  setup();
}
