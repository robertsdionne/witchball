#ifndef WITCHBALL_TITLESCREEN_H_
#define WITCHBALL_TITLESCREEN_H_

#include <Box2D/Box2D.h>
#include "ofMain.h"
#include "titlescreencontroller.h"
#include "ofxGui.h"
#include "screen.h"
#include "titlescreenmodel.h"
#include "titlescreenview.h"


class TitleScreen : public Screen {
	
public:
  TitleScreen();

  virtual ~TitleScreen();

  virtual void Setup() override;
	
  virtual void Update() override;
	
  virtual void Draw() override;
	
  virtual void KeyPressed(int key) override;
	
  virtual void KeyReleased(int key) override;
	
  virtual void MouseMoved(int x, int y) override;
	
  virtual void MouseDragged(int x, int y, int button) override;
	
  virtual void MousePressed(int x, int y, int button) override;
	
  virtual void MouseReleased(int x, int y, int button) override;
	
  virtual void WindowResized(int w, int h) override {}
	
  virtual void DragEvent(ofDragInfo dragInfo) override {}
	
  virtual void GotMessage(ofMessage msg) override {}
	
private:
	TitleScreenView view;
	TitleScreenModel model;
	TitleScreenController controller;
	
};

#endif // WITCHBALL_TITLESCREEN_H_
