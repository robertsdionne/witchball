#include "constants.h"
#include "controller.h"
#include "model.h"
#include "ofMain.h"
#include "utilities.h"
#include "witchball.h"

Controller::Controller(Model &model)
: model(model), keys(), previous_keys() {}

void Controller::OnKeyPressed(int key) {
  keys[key] = true;
}

void Controller::OnKeyReleased(int key) {
  keys[key] = false;
}

void Controller::OnMouseDragged(int x, int y, int button) {
  model.mouse_position = ofVec3f(x, y) * kViewMatrixInverse;
}

void Controller::OnMouseMoved(int x, int y) {}

void Controller::OnMousePressed(int x, int y, int button) {
  buttons[button] = true;
  OnMouseDragged(x, y, button);
}

void Controller::OnMouseReleased(int x, int y, int button) {
  buttons[button] = false;
}

void Controller::Update() {
  if (MouseButtonIsPressed(0)) {
    model.mouse_pressed = true;
    model.last_input_time = ofGetElapsedTimef();
  } else {
    model.mouse_pressed = false;
  }
  if (keys[OF_KEY_BACKSPACE] && !previous_keys[OF_KEY_BACKSPACE]) {
    model.draw_gravity = Model::GravityVisual((EnumValue(model.draw_gravity) + 1) % 2);
  }
  if (keys['`'] && !previous_keys['`']) {
    model.show_sliders = !model.show_sliders;
    model.last_input_time = ofGetElapsedTimef();
  }
  if (model.elapsed_time > model.last_collision_time + kCollisionDelay) {
    if (keys['s'] || keys['S'] || buttons[kPlayer1MouseButton]) {
      model.player1_position = ofClamp(model.player1_position + kPlayerMoveDelta, 0.0, 1.0);
      model.last_input_time = ofGetElapsedTimef();
    } else {
      model.player1_position = ofClamp(model.player1_position - kPlayerMoveDelta, 0.0, 1.0);
    }
    if (keys['k'] || keys['K'] || buttons[kPlayer2MouseButton]) {
      model.player2_position = ofClamp(model.player2_position + kPlayerMoveDelta, 0.0, 1.0);
      model.last_input_time = ofGetElapsedTimef();
    } else {
      model.player2_position = ofClamp(model.player2_position - kPlayerMoveDelta, 0.0, 1.0);
    }
  }
  if (keys['R'] && !previous_keys['R']) {
    dynamic_cast<WitchBall *>(ofGetAppPtr())->RestartScene();
    return;
  }
  previous_buttons = buttons;
  previous_keys = keys;
}

bool Controller::MouseButtonIsPressed(int button) {
  return buttons[button];
}
