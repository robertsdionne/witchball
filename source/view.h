#ifndef WITCHBALL_VIEW_H_
#define WITCHBALL_VIEW_H_

#include <list>

#include "ofMain.h"

class Model;
class b2Body;

class View {
public:
  View() {}
  
  virtual ~View() {}
  
  void Draw(const Model &model) const;
  
  void Setup();
  
private:
  void DrawStrikeIndicator(const Model &model) const;

  void DrawBall(const b2Body *ball, ofColor color) const;
  
  void DrawBallTrail(const Model &model, const std::list<ofVec2f> ball_trail, ofColor color) const;

  void DrawCourt(const Model &model) const;
  
  void DrawFramesPerSecond() const;
  
  void DrawGravity(const Model &model) const;
  
  void DrawGravityAt(ofPoint position, const Model &model) const;
  
  void DrawPlayer(const b2Body *player, ofColor color) const;
  
  void DrawPlayers(const Model &model) const;
  
  void DrawScore(const Model &model) const;
  
  void SetupViewpoint() const;

  ofColor color_p1;
  ofColor color_p2;
};



#endif  // WITCHBALL_VIEW_H_
