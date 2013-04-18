#include <Box2D/Box2D.h>

#include "constants.h"
#include "controller.h"
#include "utilities.h"
#include "witchball.h"

WitchBall::WitchBall()
: model(), view(), controller(model), sound_collision(), score_keeper_collision(),
  contact_listener(), sound_background_music(), sound_background_music_2() {}

void WitchBall::setup() {
	
	// initialize the accelerometer
	//ofxAccelerometer.setup();
	
	//If you want a landscape oreintation
	iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);
	ofSetCircleResolution(50);
	ofBackground(255,255,255);
	
	
  model.Setup();
  //contact_listener.AddContactListener(&sound_collision);
  contact_listener.AddContactListener(&score_keeper_collision);
  model.world.SetContactListener(&contact_listener);
  view.Setup();
	/*
  sound_background_music.loadSound(kBackgroundMusicFilename);
  sound_background_music_2.loadSound(kBackgroundMusicTwoFilename);
  sound_background_music.play();
  sound_background_music_2.setLoop(true);
  sound_background_music_2.play();
	 */
}

void WitchBall::update() {
//  controller.Update();
//  model.Update();
}

void WitchBall::draw() {
//  view.Draw(model);
}

void WitchBall::exit(){
	
}

void WitchBall::touchDown(ofTouchEventArgs & touch){
	controller.OnTouchDown(touch);
}


void WitchBall::touchMoved(ofTouchEventArgs & touch){
	controller.OnTouchMoved(touch);
}

void WitchBall::touchUp(ofTouchEventArgs & touch){
	controller.OnTouchUp(touch);
}

void WitchBall::touchDoubleTap(ofTouchEventArgs & touch){
	controller.OnTouchDoubleTap(touch);
}

void WitchBall::touchCancelled(ofTouchEventArgs & touch){
	controller.OnTouchCancelled(touch);
}

void WitchBall::lostFocus(){
	
}

void WitchBall::gotFocus(){
	printf("Got Focus called");
	
}

void WitchBall::gotMemoryWarning(){
	
}

void WitchBall::deviceOrientationChanged(int newOrientation){
	
}