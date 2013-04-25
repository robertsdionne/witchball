#ifndef WITCHBALL_CONTROLLER_H_
#define WITCHBALL_CONTROLLER_H_

#include <map>

class b2Body;
class Model;

class Controller {
public:
  Controller(Model &model);
  
  virtual ~Controller() {}
	
	void touchDown(ofTouchEventArgs & touch);
	void touchMoved(ofTouchEventArgs & touch);
  void touchUp(ofTouchEventArgs & touch);
	void touchDoubleTap(ofTouchEventArgs & touch);
	void touchCancelled(ofTouchEventArgs & touch);
  
  void OnKeyPressed(int key);
  
  void OnKeyReleased(int key);
  
  void OnMouseDragged(int x, int y, int button);
  
  void OnMouseMoved(int x, int y);
  
  void OnMousePressed(int x, int y, int button);
  
  void OnMouseReleased(int x, int y, int button);
  
  void Update();
  
private:
  bool MouseButtonIsPressed(int button);
  
private:
  Model &model;
  std::map<int, bool> buttons, keys, previous_buttons, previous_keys;
};

#endif  // WITCHBALL_CONTROLLER_H_
