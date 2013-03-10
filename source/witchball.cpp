#include <Box2D/Box2D.h>

#include "constants.h"
#include "controller.h"
#include "utilities.h"
#include "witchball.h"

WitchBall::WitchBall()
: model(), view(), controller(model), collision() {}

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
  controller.Update();
  model.Update();
}

void WitchBall::draw() {
  view.Draw(model);
}

void WitchBall::keyPressed(int key) {
  controller.OnKeyPressed(key);
}

void WitchBall::keyReleased(int key) {
  controller.OnKeyReleased(key);
}

void WitchBall::mouseMoved(int x, int y) {
  controller.OnMouseMoved(x, y);
}

void WitchBall::mouseDragged(int x, int y, int button) {
  controller.OnMouseDragged(x, y, button);
}

void WitchBall::mousePressed(int x, int y, int button) {
  controller.OnMousePressed(x, y, button);
}

void WitchBall::mouseReleased(int x, int y, int button) {
  controller.OnMouseReleased(x, y, button);
}
