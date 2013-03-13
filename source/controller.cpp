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
  if (MouseButtonIsPressed(0)) {
    const ofVec2f force = model.mouse_position - OpenFrameworksVector(model.ball->GetPosition());
    model.ball->ApplyForceToCenter(Box2dVector(force.lengthSquared() * force.normalized()));
  }
  previous_buttons = buttons;
  previous_keys = keys;
}

bool Controller::MouseButtonIsPressed(int button) {
  return buttons[button];
}
