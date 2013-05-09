#include <Box2D/Box2D.h>

#include "constants.h"
#include "controller.h"
#include "playscreen.h"
#include "titlescreen.h"
#include "screen.h"
#include "slider.h"
#include "utilities.h"
#include "witchball.h"

WitchBall::WitchBall() : current_screen(nullptr) {}

WitchBall::~WitchBall() {
  if (current_screen) {
    delete current_screen;
    current_screen = nullptr;
  }
}

void WitchBall::setup() {
	current_screen = new TitleScreen();
  current_screen->Setup();
}

void WitchBall::RunPlayScreen() {
  if (current_screen) {
    delete current_screen;
    current_screen = nullptr;
  }
  current_screen = new PlayScreen();
  current_screen->Setup();
}

void WitchBall::RunTitleScreen() {
  if (current_screen) {
    delete current_screen;
    current_screen = nullptr;
  }
  current_screen = new TitleScreen();
  current_screen->Setup();
}

void WitchBall::update() {
  if (current_screen) {
    current_screen->Update();
  }
}

void WitchBall::draw() {
  if (current_screen) {
    current_screen->Draw();
  }
}

void WitchBall::keyPressed(int key) {
  if (current_screen) {
    current_screen->KeyPressed(key);
  }
}

void WitchBall::keyReleased(int key) {
  if (current_screen) {
    current_screen->KeyReleased(key);
  }
}

void WitchBall::mouseMoved(int x, int y) {
  if (current_screen) {
    current_screen->MouseMoved(x, y);
  }
}

void WitchBall::mouseDragged(int x, int y, int button) {
  if (current_screen) {
    current_screen->MouseDragged(x, y, button);
  }
}

void WitchBall::mousePressed(int x, int y, int button) {
  if (current_screen) {
    current_screen->MousePressed(x, y, button);
  }
}

void WitchBall::mouseReleased(int x, int y, int button) {
  if (current_screen) {
    current_screen->MouseReleased(x, y, button);
  }
}

void WitchBall::RestartScene() {
  if (current_screen) {
    delete current_screen;
    current_screen = nullptr;
  }
  setup();
}
