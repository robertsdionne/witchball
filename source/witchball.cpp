#include <Box2D/Box2D.h>

#include "constants.h"
#include "controller.h"
#include "utilities.h"
#include "witchball.h"

WitchBall::WitchBall()
: model(), view(), controller(model), sound_collision(), score_keeper_collision(),
  contact_listener(), sound_background_music(), sound_background_music_2() {}

void WitchBall::setup() {
  model.Setup();
  contact_listener.AddContactListener(&sound_collision);
  contact_listener.AddContactListener(&score_keeper_collision);
  model.world.SetContactListener(&contact_listener);
  view.Setup();
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
