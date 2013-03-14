#ifndef WITCHBALL_VIEW_H_
#define WITCHBALL_VIEW_H_

class Model;
class b2Body;

class View {
public:
  View() {}
  
  virtual ~View() {}
  
  void Draw(const Model &model) const;
  
  void Setup();
  
private:
  void DrawBall(const b2Body *ball) const;
  
  void DrawCourt() const;
  
  void DrawFramesPerSecond() const;
  
  void DrawPlayer(const b2Body *player, ofColor color) const;
  
  void DrawPlayers(const Model &model) const;
  
  void SetupViewpoint() const;

  ofColor color_p1;
  ofColor color_p2;
};



#endif  // WITCHBALL_VIEW_H_
