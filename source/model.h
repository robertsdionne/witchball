#ifndef WITCHBALL_MODEL_H_
#define WITCHBALL_MODEL_H_

#include <Box2D/Box2D.h>
#include <list>

#include "ofChaser.h"
#include "ofMain.h"

class Model {
public:
  Model(bool fake);
  
  virtual ~Model() {}
  
  void Setup();
  
  void Update();
  
  void UpdateGravities();

  b2Vec2 GravityAt(b2Vec2 position) const;
	
  void IncrementPlayerOneCount();
  
  void IncrementPlayerTwoCount();

  void RotateClockwise();

  void RotateCounterClockwise();
  
  float p1glowMax, p2glowMax;


private:
  void CreateBall(ofPoint position = ofPoint(1, 0), ofVec2f velocity = ofVec2f(3.5, 3.5));
  
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

  bool fake;
  
  b2World world;
  
  b2Body *ball, *border;
  
  b2Body *player1_top, *player1_bottom, *player2_top, *player2_bottom;
  
  bool mouse_pressed;
  ofPoint mouse_position;
  
  b2Vec2 top_left_quadrant_gravity, top_right_quadrant_gravity;
  b2Vec2 bottom_left_quadrant_gravity, bottom_right_quadrant_gravity;
  
  float gravity_angle;

  CourtPosition court_position;
  bool play_gravity;

  int last_hit_player = 0;
  ofVec2f strike_position;
  float strike_alpha, p1_score_alpha, p2_score_alpha;

  float counter_clockwise_alpha;
  float clockwise_alpha;
	
  int player1_score = 0;
  int player2_score = 0;
  
  int player1_increment_count = 0;
  int player2_increment_count = 0;
  
  float player1_position;
  float player2_position;
  
  GravityVisual draw_gravity;

  float elapsed_time, last_collision_time;

  std::list<ofVec2f> ball_trail;
  std::list<ofVec2f> player1_top_trail, player1_bottom_trail;
  std::list<ofVec2f> player2_top_trail, player2_bottom_trail;

  ofPoint testPoint;

  ofChaser** topChaser;
  ofChaser** botChaser;
  ofChaser** leftChaser;
  ofChaser** rightChaser;

  int nChasers;

  bool show_sliders = false;
};

#endif  // WITCHBALL_MODEL_H_
