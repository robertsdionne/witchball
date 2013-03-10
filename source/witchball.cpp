#include <Box2D/Box2D.h>
#include <iostream>

#include "constants.h"
#include "utilities.h"
#include "witchball.h"

WitchBall::WitchBall()
: model(), collision() {}

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
    model.ball_body->ApplyForce(Box2dVector(force.lengthSquared() * force.normalized()),
                          model.ball_body->GetWorldCenter() + kBallRadius * b2Vec2(
                          cos(model.ball_body->GetAngle()), sin(model.ball_body->GetAngle())));
  }
  model.Update();
  previous_buttons = buttons;
  previous_keys = keys;
}

void WitchBall::draw() {
  ofDrawBitmapString(ofToString(ofGetFrameRate()), ofPoint(0, 10));
  ofMultMatrix(kViewMatrix);
  const ofPoint ball_position = OpenFrameworksVector(model.ball_body->GetPosition());
  const float angle = model.ball_body->GetAngle();
  const ofVec2f b = ofVec2f(cos(angle), sin(angle));
  ofSetColor(ofColor::white);
  ofLine(ofPoint(-kHalfCourtWidth, 0.0), ofPoint(kHalfCourtWidth, 0.0));
  if (buttons[0]) {
    ofSetColor(ofColor::black);
    ofLine(ball_position + kBallRadius * b, model.mouse_position);
  }
  ofSetColor(ofColor::white);
  ofCircle(ball_position, kBallRadius);
  ofSetColor(ofColor::black);
  const ofVec2f a = ofVec2f(sin(angle), -cos(angle));
  ofLine(ball_position + kBallRadius * a, ball_position - kBallRadius * a);
  ofLine(ball_position + kBallRadius * b, ball_position - kBallRadius * b);
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
