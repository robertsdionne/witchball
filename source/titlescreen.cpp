//
//  titlescreen.cpp
//  witchball
//
//  Created by Shervin Ghazazani on 4/24/13.
//
//

#include "titlescreen.h"
#include "witchball.h"

TitleScreen::TitleScreen() : view(), model(), controller(model) {
  sound_background_music.loadSound("bgm.wav");
}

TitleScreen::~TitleScreen() {
  
}

void TitleScreen::Setup() {
  view.Setup();
  model.Setup();
  sound_background_music.play();
}

void TitleScreen::Update() {
  controller.Update();
  model.Update();
}

void TitleScreen::Draw() {
	view.Draw(model);
}

void TitleScreen::KeyPressed(int key) {
  controller.OnKeyPressed(key);
}

void TitleScreen::KeyReleased(int key) {
  controller.OnKeyReleased(key);
}

void TitleScreen::MouseMoved(int x, int y) {
  //controller.OnMouseMoved(x, y);
}

void TitleScreen::MouseDragged(int x, int y, int button) {
  //controller.OnMouseDragged(x, y, button);
}

void TitleScreen::MousePressed(int x, int y, int button) {
  controller.OnMousePressed(x, y, button);
}

void TitleScreen::MouseReleased(int x, int y, int button) {
  controller.OnMouseReleased(x, y, button);
}
