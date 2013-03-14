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
  if (keys[' '] && !previous_keys[' ']) {
    model.RotateClockwise();
  }
  if (keys[OF_KEY_BACKSPACE] && !previous_keys[OF_KEY_BACKSPACE]) {
    model.RotateCounterClockwise();
  }
  if (keys['q']) {
    UpdatePlayerPosition(model.player1_top, kPlayer1TopForward[EnumValue(model.court_position)]);
    UpdatePlayerPosition(model.player1_bottom, kPlayer1BottomForward[EnumValue(model.court_position)]);
  } else {
    UpdatePlayerPosition(model.player1_top, kPlayer1TopBack[EnumValue(model.court_position)]);
    UpdatePlayerPosition(model.player1_bottom, kPlayer1BottomBack[EnumValue(model.court_position)]);
  }
  if (keys['p']) {
    UpdatePlayerPosition(model.player2_top, kPlayer2TopForward[EnumValue(model.court_position)]);
    UpdatePlayerPosition(model.player2_bottom, kPlayer2BottomForward[EnumValue(model.court_position)]);
  } else {
    UpdatePlayerPosition(model.player2_top, kPlayer2TopBack[EnumValue(model.court_position)]);
    UpdatePlayerPosition(model.player2_bottom, kPlayer2BottomBack[EnumValue(model.court_position)]);
  }
  previous_buttons = buttons;
  previous_keys = keys;
}

bool Controller::MouseButtonIsPressed(int button) {
  return buttons[button];
}

void Controller::UpdatePlayerPosition(b2Body *player, ofPoint target) {
  const ofVec2f position = OpenFrameworksVector(player->GetPosition());
  const ofVec2f delta = (target - position) * kControllerRate;
  const ofVec2f new_position = position + delta;
  player->SetTransform(Box2dVector(new_position), 0.0);
}
