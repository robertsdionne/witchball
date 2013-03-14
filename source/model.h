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
	
	void IncrementPlayerOneCount();
	void IncrementPlayerTwoCount();
  
private:
  void CreateBall(ofPoint position = ofPoint(), ofVec2f velocity = ofVec2f());
  
  void CreateBorder();
  
  b2Body *CreatePlayer(ofPoint position = ofPoint());
  
  void CreatePlayers();
	
	
  
  void Gravity();
  
public:
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
  
  CourtPosition court_position;
	
	int player1_score = 0;
	int player2_score = 0;
	
	int player1_increment_count = 0;
	int player2_increment_count = 0;
};

#endif  // WITCHBALL_MODEL_H_
