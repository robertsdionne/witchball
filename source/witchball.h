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
#include "view.h"

class Screen;

class WitchBall : public ofBaseApp {
public:
  WitchBall();
  
  virtual ~WitchBall();
  
  void setup();
  
  void update();
  
  void draw();

  void keyPressed(int key);
  
  void keyReleased(int key);
  
  void mouseMoved(int x, int y);
  
  void mouseDragged(int x, int y, int button);
  
  void mousePressed(int x, int y, int button);
  
  void mouseReleased(int x, int y, int button);
  
  void windowResized(int w, int h) {}
  
  void dragEvent(ofDragInfo dragInfo) {}
  
  void gotMessage(ofMessage msg) {}

  void RestartScene();
  
private:
  Screen *current_screen;
};

#endif  // WITCHBALL_WITCHBALL
