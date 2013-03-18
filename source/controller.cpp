#include "constants.h"
#include "controller.h"
#include "model.h"
#include "ofMain.h"
#include "utilities.h"

Controller::Controller(Model &model)
: model(model), keys(), previous_keys() {}

void Controller::OnKeyPressed(int key) {
  keys[key] = true;
}

void Controller::OnKeyReleased(int key) {
  keys[key] = false;
}

void Controller::OnMouseDragged(int x, int y, int button) {
  OnMouseMoved(x, y);
}

void Controller::OnMouseMoved(int x, int y) {
  model.mouse_position = ofVec3f(x, y) * kViewMatrixInverse;
}

void Controller::OnMousePressed(int x, int y, int button) {
  buttons[button] = true;
}

void Controller::OnMouseReleased(int x, int y, int button) {
  buttons[button] = false;
}

void Controller::Update() {
  if (keys[OF_KEY_BACKSPACE] && !previous_keys[OF_KEY_BACKSPACE]) {
    model.draw_gravity = Model::GravityVisual((EnumValue(model.draw_gravity) + 1) % 4);
  }
  if (keys['q']) {
    model.player1_position = ofClamp(model.player1_position + kPlayerMoveDelta, 0.0, 1.0);
  } else {
    model.player1_position = ofClamp(model.player1_position - kPlayerMoveDelta, 0.0, 1.0);
  }
  if (keys['p']) {
    model.player2_position = ofClamp(model.player2_position + kPlayerMoveDelta, 0.0, 1.0);
  } else {
    model.player2_position = ofClamp(model.player2_position - kPlayerMoveDelta, 0.0, 1.0);
  }
  previous_buttons = buttons;
  previous_keys = keys;
}

bool Controller::MouseButtonIsPressed(int button) {
  return buttons[button];
}
