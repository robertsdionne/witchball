#include <Box2D/Box2D.h>
#include <iostream>

#include "constants.h"
#include "utilities.h"
#include "witchball.h"

WitchBall::WitchBall()
: model(), view(), collision() {}

void WitchBall::setup() {
  ofSetFrameRate(60);
  ofSetVerticalSync(true);
  model.Setup();
  model.world.SetContactListener(&collision);
  sound_background_music.loadSound(kBackgroundMusicFilename);
  sound_background_music_2.loadSound(kBackgroundMusicTwoFilename);
  sound_background_music.play();
  sound_background_music_2.setLoop(true);
  sound_background_music_2.play();
}

void WitchBall::update() {
  if (buttons[0]) {
    const ofVec2f force = model.mouse_position - OpenFrameworksVector(model.ball_body->GetPosition());
    model.ball_body->ApplyForceToCenter(Box2dVector(force.lengthSquared() * force.normalized()));
  }
  model.Update();
  previous_buttons = buttons;
  previous_keys = keys;
}

void WitchBall::draw() {
  view.Draw(model);
}

void WitchBall::keyPressed(int key) {
  keys[key] = true;
}

void WitchBall::keyReleased(int key) {
  keys[key] = false;
}

void WitchBall::mouseMoved(int x, int y) {
  model.mouse_position = ofVec3f(x, y) * kViewMatrixInverse;
}

void WitchBall::mouseDragged(int x, int y, int button) {
  mouseMoved(x, y);
}

void WitchBall::mousePressed(int x, int y, int button) {
  buttons[button] = true;
}

void WitchBall::mouseReleased(int x, int y, int button) {
  buttons[button] = false;
}

void WitchBall::windowResized(int w, int h) {
}

void WitchBall::gotMessage(ofMessage msg) {
}

void WitchBall::dragEvent(ofDragInfo dragInfo) {
}
