#ifndef WITCHBALL_TITLESCREEN_CONTROLLER_H_
#define WITCHBALL_TITLESCREEN_CONTROLLER_H_

#include <map>

class b2Body;
class TitleScreenModel;

class TitleScreenController {
public:
  TitleScreenController(TitleScreenModel &model);
  
  virtual ~TitleScreenController() {}
  
  void OnKeyPressed(int key);
  
  void OnKeyReleased(int key);
  
  void Update();
  
private:
  bool MouseButtonIsPressed(int button);
  
private:
  TitleScreenModel &model;
  std::map<int, bool> buttons, keys, previous_buttons, previous_keys;
};

#endif  // WITCHBALL_TITLESCREEN_CONTROLLER_H_
