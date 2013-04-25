#include "parameter.h"
#include "playscreen.h"
#include "slider.h"

PlayScreen::PlayScreen()
: model(), view(), controller(model), sound_collision(), score_keeper_collision(),
  contact_listener(), sound_background_music(), sound_background_music_2() {}


PlayScreen::~PlayScreen() {
  for (int i = 0; i < float_panel.getNumControls(); ++i) {
    delete float_panel.getControl(i);
  }
  float_panel.clear();
  for (int i = 0; i < int_panel.getNumControls(); ++i) {
    delete int_panel.getControl(i);
  }
  int_panel.clear();
}

void PlayScreen::Setup() {
  model.Setup();
  contact_listener.AddContactListener(&sound_collision);
  contact_listener.AddContactListener(&score_keeper_collision);
  model.world.SetContactListener(&contact_listener);
  view.Setup();
	/*
  sound_background_music.loadSound("bgm.wav");
  sound_background_music_2.loadSound("bgm2.wav");
  sound_background_music.play();
  sound_background_music_2.setLoop(true);
  sound_background_music_2.play();
	 */
  float_panel.setup("float parameters");
  for (auto parameter : GetParameters<float>()) {
    float_panel.add(new Slider<float>(parameter));
  }
  int_panel.setup("int parameters", "settings.xml",
                  float_panel.getPosition().x + float_panel.getWidth() + 1);
  for (auto parameter : GetParameters<int>()) {
    int_panel.add(new Slider<int>(parameter));
  }
}

void PlayScreen::Update() {
  model.elapsed_time = ofGetElapsedTimef();
  model.Update();
  controller.Update();
}

void PlayScreen::Draw() {
  view.Draw(model);
  if (model.show_sliders) {
    float_panel.draw();
    int_panel.draw();
  }
}

void PlayScreen::touchDown(ofTouchEventArgs & touch) {
	controller.touchDown(touch);
}

void PlayScreen::touchMoved(ofTouchEventArgs & touch) {
	controller.touchMoved(touch);
}

void PlayScreen::touchUp(ofTouchEventArgs & touch) {
	controller.touchUp(touch);
}

void PlayScreen::touchDoubleTap(ofTouchEventArgs & touch) {
	controller.touchDoubleTap(touch);
}

void PlayScreen::touchCancelled(ofTouchEventArgs & touch) {
	controller.touchCancelled(touch);
}