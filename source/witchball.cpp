#include <Box2D/Box2D.h>

#include "constants.h"
#include "controller.h"
#include "slider.h"
#include "utilities.h"
#include "witchball.h"

WitchBall::WitchBall()
: model(), view(), controller(model), sound_collision(), score_keeper_collision(),
  contact_listener(), sound_background_music(), sound_background_music_2() {}

WitchBall::~WitchBall() {
  for (int i = 0; i < float_panel.getNumControls(); ++i) {
    delete float_panel.getControl(i);
  }
  float_panel.clear();
  for (int i = 0; i < int_panel.getNumControls(); ++i) {
    delete int_panel.getControl(i);
  }
  int_panel.clear();
}

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
  float_panel.setup("float parameters");
  for (auto parameter : Parameter<float>::GetParameters()) {
    float_panel.add(new Slider<float>(parameter));
  }
  int_panel.setup("int parameters", "settings.xml",
                  float_panel.getPosition().x + float_panel.getWidth() + 1);
  for (auto parameter : Parameter<int>::GetParameters()) {
    int_panel.add(new Slider<int>(parameter));
  }
}

void WitchBall::update() {
  controller.Update();
  model.elapsed_time = ofGetElapsedTimef();
  model.Update();
}

void WitchBall::draw() {
  view.Draw(model);
  if (model.show_sliders) {
    float_panel.draw();
    int_panel.draw();
  }
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
