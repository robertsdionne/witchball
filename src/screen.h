#ifndef WITCHBALL_SCREEN_H_
#define WITCHBALL_SCREEN_H_

#include "ofMain.h"

class Screen {
public:
  virtual ~Screen() {}

  virtual void Setup() {}

  virtual void Update() {}

  virtual void Draw() {}

  virtual void touchDown(ofTouchEventArgs & touch) {}
	
	virtual void touchMoved(ofTouchEventArgs & touch) {}
	
	virtual void touchUp(ofTouchEventArgs & touch) {}
	
	virtual void touchDoubleTap(ofTouchEventArgs & touch) {}
	
	virtual void touchCancelled(ofTouchEventArgs & touch) {}

protected:
	Screen() {}
};

#endif  // WITCHBALL_SCREEN_H_
