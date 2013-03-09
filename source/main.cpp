#include "constants.h"
#include "ofAppGlutWindow.h"
#include "ofMain.h"
#include "witchball.h"

int main(const int argument_count, const char *arguments[]) {
  ofAppGlutWindow window;
  ofSetupOpenGL(&window, kWidth, kHeight, OF_WINDOW);
  ofRunApp(new WitchBall());
}
