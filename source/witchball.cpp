#include "constants.h"
#include "witchball.h"

WitchBall::WitchBall()
: world(kGravity) {}

void WitchBall::setup() {
}

void WitchBall::update() {
  world.Step(kTimeStep, kBox2dVelocityIterations, kBox2dPositionIterations);
}

void WitchBall::draw() {
}

void WitchBall::keyPressed(int key) {
}

void WitchBall::keyReleased(int key) {
}

void WitchBall::mouseMoved(int x, int y) {
}

void WitchBall::mouseDragged(int x, int y, int button) {
}

void WitchBall::mousePressed(int x, int y, int button) {
}

void WitchBall::mouseReleased(int x, int y, int button) {
}

void WitchBall::windowResized(int w, int h) {
}

void WitchBall::gotMessage(ofMessage msg) {
}

void WitchBall::dragEvent(ofDragInfo dragInfo) {
}
