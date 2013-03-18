#ifndef WITCHBALL_MODEL_H_
#define WITCHBALL_MODEL_H_

#include <Box2D/Box2D.h>
#include <list>

#include "ofMain.h"

class Model {
public:
  Model();
  
  virtual ~Model() {}
  
  void Setup();
  
  void Update();
  
  void UpdateGravities();

  b2Vec2 GravityAt(b2Vec2 position) const;
	
  void IncrementPlayerOneCount();
  
  void IncrementPlayerTwoCount();

  void RotateClockwise();

  void RotateCounterClockwise();

private:
  void CreateBall(ofPoint position = ofPoint(), ofVec2f velocity = ofVec2f(-3.0, 0.0));
  
  void CreateBorder();
  
  b2Body *CreatePlayer(ofPoint position = ofPoint());
  
  void CreatePlayers();
  
  void UpdatePlayerPosition(b2Body *player, ofPoint target);
  
  void UpdateTrails();
    
public:
  enum class CourtPosition {
    POSITION_1,
    POSITION_2,
    POSITION_3,
    POSITION_4
  };
  
  enum class GravityVisual {
    NONE,
    QUADRANT
  };
  
  b2World world;
  
  b2Body *ball, *border;
  
  b2Body *player1_top, *player1_bottom, *player2_top, *player2_bottom;
  
  bool mouse_pressed;
  ofPoint mouse_position;
  ofPoint mouse_gravity_position;

  float mouse_mass_scale;
  b2Vec2 top_left_quadrant_gravity, top_right_quadrant_gravity;
  b2Vec2 bottom_left_quadrant_gravity, bottom_right_quadrant_gravity;

  CourtPosition court_position;
	
  int player1_score = 0;
  int player2_score = 0;
  
  int player1_increment_count = 0;
  int player2_increment_count = 0;
  
  float player1_position;
  float player2_position;
  
  GravityVisual draw_gravity;

  std::list<ofVec2f> ball_trail;
  std::list<ofVec2f> player1_top_trail, player1_bottom_trail;
  std::list<ofVec2f> player2_top_trail, player2_bottom_trail;
};

#endif  // WITCHBALL_MODEL_H_
