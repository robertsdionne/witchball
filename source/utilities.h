#ifndef WITCHBALL_UTILITIES_H_
#define WITCHBALL_UTILITIES_H_

#include <Box2D/Box2D.h>

#include "ofMain.h"

b2Vec2 Box2dVector(ofVec2f openframeworks_vector);

b2Vec2 Lerp(b2Vec2 from, b2Vec2 to, float t);

ofVec2f Lerp(ofVec2f from, ofVec2f to, float t);

ofVec2f OpenFrameworksVector(b2Vec2 box2d_vector);

#endif  // WITCHBALL_UTILITIES_H_
