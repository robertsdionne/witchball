#ifndef WITCHBALL_WITCHBALL_H_
#define WITCHBALL_WITCHBALL_H_

#include <Box2D/Box2D.h>
#include <map>

#include "collisionplayer.h";
#include "ofMain.h"

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
  static b2Vec2 Box2dVector(ofVec2f vector);
  
  static b2Vec2 Lerp(b2Vec2 from, b2Vec2 to, float t);
  
  static ofVec2f Lerp(ofVec2f from, ofVec2f to, float t);
  
  static ofVec2f OpenFrameworksVector(b2Vec2 vector);

  
  void CreateBall(ofPoint position = ofPoint(), ofVec2f velocity = ofVec2f());
  
  void CreateBorder();
  
  void Gravity();
  
private:
  b2World world;
  
  b2Body *ball_body, *border_body;
  
  b2CircleShape ball_shape;
  
  b2ChainShape border_shape;
  
  b2Fixture *ball_fixture, *border_fixture;
  
  CollisionPlayer collision;
  
  ofPoint mouse_position;
  
  ofSoundPlayer sound_background_music, sound_background_music_2;
  
  std::map<int, bool> buttons, previous_buttons;
  std::map<int, bool> keys, previous_keys;
};

#endif  // WITCHBALL_WITCHBALL
