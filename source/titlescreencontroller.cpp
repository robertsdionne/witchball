#include "constants.h"
#include "titlescreencontroller.h"
#include "titlescreenmodel.h"
#include "ofMain.h"
#include "utilities.h"
#include "witchball.h"

TitleScreenController::TitleScreenController(TitleScreenModel &model)
: model(model), keys(), previous_keys() {}

void TitleScreenController::OnKeyPressed(int key) {
  keys[key] = true;
}

void TitleScreenController::OnKeyReleased(int key) {
  keys[key] = false;
}

void TitleScreenController::OnMousePressed(int x, int y, int button) {
  buttons[button] = true;
}

void TitleScreenController::OnMouseReleased(int x, int y, int button) {
  buttons[button] = false;
}

void TitleScreenController::Update() {
  if (keys['`'] && !previous_keys['`']) {
    model.show_sliders = !model.show_sliders;
  }
	if (keys['q'] || buttons[kPlayer1MouseButton]) {
		model.player1_position = ofClamp(model.player1_position + kPlayerMoveDelta, 0.0, 1.0);
	} else {
		model.player1_position = ofClamp(model.player1_position - kPlayerMoveDelta, 0.0, 1.0);
	}
	if (keys['p'] || buttons[kPlayer2MouseButton]) {
		model.player2_position = ofClamp(model.player2_position + kPlayerMoveDelta, 0.0, 1.0);
	} else {
		model.player2_position = ofClamp(model.player2_position - kPlayerMoveDelta, 0.0, 1.0);
	}

  previous_buttons = buttons;
  previous_keys = keys;
}
