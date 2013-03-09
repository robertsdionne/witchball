#include "constants.h"
#include "ofAppGlutWindow.h"
#include "ofMain.h"
#include "witchball.h"

int main(const int argument_count, const char *arguments[]) {
  ofAppGlutWindow window;
  window.setGlutDisplayString("rgba double depth alpha samples>=4");
  ofSetupOpenGL(&window, kWidth, kHeight, OF_WINDOW);
  ofRunApp(new WitchBall());
}
