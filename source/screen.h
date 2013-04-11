#ifndef WITCHBALL_SCREEN_H_
#define WITCHBALL_SCREEN_H_

#include "ofMain.h"

class Screen {
public:
  virtual ~Screen() {}

  virtual void Setup() {}

  virtual void Update() {}

  virtual void Draw() {}

  virtual void KeyPressed(int key) {}

  virtual void KeyReleased(int key) {}

  virtual void MouseMoved(int x, int y) {}

  virtual void MouseDragged(int x, int y, int button) {}

  virtual void MousePressed(int x, int y, int button) {}

  virtual void MouseReleased(int x, int y, int button) {}

  virtual void WindowResized(int w, int h) {}

  virtual void DragEvent(ofDragInfo dragInfo) {}

  virtual void GotMessage(ofMessage msg) {}

protected:
  Screen() {}
};

#endif  // WITCHBALL_SCREEN_H_
