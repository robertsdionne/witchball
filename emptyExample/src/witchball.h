#ifndef WITCHBALL_WITCHBALL_H_
#define WITCHBALL_WITCHBALL_H_

#include "Box2D.h"
//#include <Box2D/Box2D.h>
#include <map>

#include "collisionsoundplayer.h"
#include "collisionscorekeeper.h"
#include "compositecontactlistener.h"
#include "controller.h"
#include "model.h"
#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "view.h"

class WitchBall : public ofxiPhoneApp {
public:
  WitchBall();
  
  virtual ~WitchBall() {}
  
  void setup();
  
  void update();
  
  void draw();

	void exit();
	
	void touchDown(ofTouchEventArgs & touch);
	void touchMoved(ofTouchEventArgs & touch);
	void touchUp(ofTouchEventArgs & touch);
	void touchDoubleTap(ofTouchEventArgs & touch);
	void touchCancelled(ofTouchEventArgs & touch);
	
	void lostFocus();
	void gotFocus();
	void gotMemoryWarning();
	void deviceOrientationChanged(int newOrientation);

private:
  Model model;
  View view;
  Controller controller;
  CollisionSoundPlayer sound_collision;
  collisionscorekeeper score_keeper_collision;
  CompositeContactListener contact_listener;
  ofSoundPlayer sound_background_music, sound_background_music_2;
};

#endif  // WITCHBALL_WITCHBALL
