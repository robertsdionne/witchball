#ifndef WITCHBALL_VIEW_H_
#define WITCHBALL_VIEW_H_

class Model;
class b2Body;

class View {
public:
  View() {}
  
  virtual ~View() {}
  
  void Draw(const Model &model) const;
  
  void Setup() const;
  
private:
  void DrawBall(const b2Body *ball) const;
  
  void DrawCourt() const;
  
  void DrawFramesPerSecond() const;
  
  void SetupViewpoint() const;
};

#endif  // WITCHBALL_VIEW_H_
