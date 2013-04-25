//
//  titlescreen.cpp
//  witchball
//
//  Created by Shervin Ghazazani on 4/24/13.
//
//

#include "titlescreen.h"
#include "witchball.h"

TitleScreen::TitleScreen() : view() {
	
}

TitleScreen::~TitleScreen() {
  
}

void TitleScreen::Setup() {
	view.Setup();

}

void TitleScreen::Update() {

}

void TitleScreen::Draw() {
	view.Draw();
}

void TitleScreen::KeyPressed(int key) {
	dynamic_cast<WitchBall *>(ofGetAppPtr())->RunPlayScreen();
}

void TitleScreen::KeyReleased(int key) {
  //controller.OnKeyReleased(key);
}

void TitleScreen::MouseMoved(int x, int y) {
  //controller.OnMouseMoved(x, y);
}

void TitleScreen::MouseDragged(int x, int y, int button) {
  //controller.OnMouseDragged(x, y, button);
}

void TitleScreen::MousePressed(int x, int y, int button) {
  //controller.OnMousePressed(x, y, button);
}

void TitleScreen::MouseReleased(int x, int y, int button) {
  //controller.OnMouseReleased(x, y, button);
}
