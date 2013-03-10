#include <Box2D/Box2D.h>

#include "utilities.h"
#include "ofMain.h"

b2Vec2 Box2dVector(ofVec2f openframeworks_vector) {
  return b2Vec2(openframeworks_vector.x, openframeworks_vector.y);
}

b2Vec2 Lerp(b2Vec2 from, b2Vec2 to, float t) {
  return (1.0 - t) * from + t * to;
}

ofVec2f Lerp(ofVec2f from, ofVec2f to, float t) {
  return (1.0 - t) * from + t * to;
}

ofVec2f OpenFrameworksVector(b2Vec2 box2d_vector) {
  return ofVec2f(box2d_vector.x, box2d_vector.y);
}
