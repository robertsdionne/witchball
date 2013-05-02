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

void TitleScreenController::Update() {
  if (keys['`'] && !previous_keys['`']) {
    model.show_sliders = !model.show_sliders;
  }
	if (keys['q']) {
		model.player1_position = ofClamp(model.player1_position + kPlayerMoveDelta, 0.0, 1.0);
	} else {
		model.player1_position = ofClamp(model.player1_position - kPlayerMoveDelta, 0.0, 1.0);
	}
	if (keys['p']) {
		model.player2_position = ofClamp(model.player2_position + kPlayerMoveDelta, 0.0, 1.0);
	} else {
		model.player2_position = ofClamp(model.player2_position - kPlayerMoveDelta, 0.0, 1.0);
	}

  previous_buttons = buttons;
  previous_keys = keys;
}
