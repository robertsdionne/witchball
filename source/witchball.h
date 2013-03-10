#ifndef WITCHBALL_WITCHBALL_H_
#define WITCHBALL_WITCHBALL_H_

#include <Box2D/Box2D.h>
#include <map>

#include "collisionplayer.h"
#include "model.h"
#include "ofMain.h"
#include "view.h"

class WitchBall : public ofBaseApp {
public:
  WitchBall();
  
  virtual ~WitchBall() {}
  
  void setup();
  
  void update();
  
  void draw();

  
  void keyPressed  (int key);
  
  void keyReleased(int key);
  
  void mouseMoved(int x, int y);
  
  void mouseDragged(int x, int y, int button);
  
  void mousePressed(int x, int y, int button);
  
  void mouseReleased(int x, int y, int button);
  
  void windowResized(int w, int h);
  
  void dragEvent(ofDragInfo dragInfo);
  
  void gotMessage(ofMessage msg);
  
private:
  Model model;
  View view;
  
  CollisionPlayer collision;
  
  ofSoundPlayer sound_background_music, sound_background_music_2;
  
  std::map<int, bool> buttons, previous_buttons;
  std::map<int, bool> keys, previous_keys;
};

#endif  // WITCHBALL_WITCHBALL
