#ifndef WITCHBALL_MODEL_H_
#define WITCHBALL_MODEL_H_

#include <Box2D/Box2D.h>

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
  
  b2Body *CreatePlayer(ofPoint position = ofPoint());
  
  void CreatePlayers();
  
  void Gravity();
  
public:
  enum class PlayerCopy {
    TOP,
    BOTTOM
  };
  
  enum class CourtPosition {
    POSITION_1,
    POSITION_2,
    POSITION_3,
    POSITION_4
  };
  
  b2World world;
  
  b2Body *ball, *border;
  
  b2Body *player1_top, *player1_bottom, *player2_top, *player2_bottom;
  
  ofPoint mouse_position;
};

#endif  // WITCHBALL_MODEL_H_
