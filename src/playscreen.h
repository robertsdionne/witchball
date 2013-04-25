#ifndef WITCHBALL_PLAYSCREEN_H_
#define WITCHBALL_PLAYSCREEN_H_

#include <Box2D/Box2D.h>

#include "collisionsoundplayer.h"
#include "collisionscorekeeper.h"
#include "compositecontactlistener.h"
#include "controller.h"
#include "model.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "screen.h"
#include "view.h"

class PlayScreen : public Screen {
public:
  PlayScreen();

  virtual ~PlayScreen();

  virtual void Setup() override;

  virtual void Update() override;

  virtual void Draw() override;
	
	virtual void touchDown(ofTouchEventArgs & touch) override;
	
	virtual void touchMoved(ofTouchEventArgs & touch) override;
	
	virtual void touchUp(ofTouchEventArgs & touch) override;
	
	virtual void touchDoubleTap(ofTouchEventArgs & touch) override;
	
	virtual void touchCancelled(ofTouchEventArgs & touch) override;
	
private:
  Model model;
  View view;
  Controller controller;
  CollisionSoundPlayer sound_collision;
  collisionscorekeeper score_keeper_collision;
  CompositeContactListener contact_listener;
  ofSoundPlayer sound_background_music, sound_background_music_2;
  ofxPanel float_panel;
  ofxPanel int_panel;
};

#endif  // WITCHBALL_PLAYSCREEN_H_
