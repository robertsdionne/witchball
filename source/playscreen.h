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

  virtual void KeyPressed(int key) override;

  virtual void KeyReleased(int key) override;

  virtual void MouseMoved(int x, int y) override;

  virtual void MouseDragged(int x, int y, int button) override;

  virtual void MousePressed(int x, int y, int button) override;

  virtual void MouseReleased(int x, int y, int button) override;

  virtual void WindowResized(int w, int h) override {}

  virtual void DragEvent(ofDragInfo dragInfo) override {}

  virtual void GotMessage(ofMessage msg) override {}

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
