#include "ofAppGlutWindow.h"
#include "ofMain.h"
#include "witchball.h"

constexpr int kWidth = 1024;
constexpr int kHeight = 768;

int main(const int argument_count, const char *arguments[]) {
  ofAppGlutWindow window;
  ofSetupOpenGL(&window, kWidth, kHeight, OF_WINDOW);
  ofRunApp(new WitchBall());
}
