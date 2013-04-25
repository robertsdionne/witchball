#ifndef WITCHBALL_WITCHBALL_H_
#define WITCHBALL_WITCHBALL_H_

#include <Box2D/Box2D.h>

#include "collisionsoundplayer.h"
#include "collisionscorekeeper.h"
#include "compositecontactlistener.h"
#include "controller.h"
#include "model.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "view.h"

class Screen;

class WitchBall : public ofxiPhoneApp {
public:
  WitchBall();
  
  virtual ~WitchBall();
  
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

  void RestartScene();
  
private:
  Screen *current_screen;
};

#endif  // WITCHBALL_WITCHBALL
