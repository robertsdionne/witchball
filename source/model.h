#ifndef WITCHBALL_MODEL_H_
#define WITCHBALL_MODEL_H_

#include <Box2D/Box2D.h>

#include "collisionplayer.h"
#include "ofMain.h"

class Model {
public:
  Model();
  
  virtual ~Model() {}
  
  void Setup();
  
  void Update();
  
private:
  void CreateBall(ofPoint position = ofPoint(), ofVec2f velocity = ofVec2f());
  
  void CreateBorder();
  
  void Gravity();
  
public:
  b2World world;
  
  b2Body *ball_body, *border_body;
  
  ofPoint mouse_position;
};

#endif  // WITCHBALL_MODEL_H_
