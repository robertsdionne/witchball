#ifndef WITCHBALL_CONSTANTS_H_
#define WITCHBALL_CONSTANTS_H_

#include <Box2D/Box2D.h>

#include "ofMain.h"
#include "parameter.h"
#include "utilities.h"

extern Parameter<float> kAngularDamping;
extern Parameter<b2Vec2> kAntiGravity;
extern Parameter<float> kAspectRatio;

extern Parameter<float> kBallRadius;
extern Parameter<float> kBallTrailAlphaStart;
extern Parameter<float> kBallTrailFadeCoefficient;
extern Parameter<int> kBallTrailLength;
extern Parameter<int> kBallTrailSpacing;
extern Parameter<int> kBox2dPositionIterations;
extern Parameter<int> kBox2dVelocityIterations;
extern Parameter<b2Vec2> kBumperForce;
extern Parameter<float> kBumperForceStrength;

extern Parameter<float> kCollisionDelay;
extern Parameter<float> kControllerRateX;
extern Parameter<float> kControllerRateY;
extern Parameter<float> kCourtHeight;
extern Parameter<float> kCourtWidth;

extern Parameter<float> kDampingSpeed;
extern Parameter<float> kDensity;

extern Parameter<int> kFixedRotation;
extern Parameter<float> kFrameRate;
extern Parameter<float> kFriction;

extern Parameter<b2Vec2> kGravity;
extern Parameter<float> kGravityMixerRate;
extern Parameter<float> kGravityStrength;

extern Parameter<float> kHalfCourtHeight;
extern Parameter<float> kHalfCourtWidth;
extern Parameter<float> kHalfHeight;
extern Parameter<float> kHalfWidth;
extern Parameter<int> kHeight;

extern Parameter<float> kLinearDamping;

extern Parameter<float> kPixelScale;
extern Parameter<float> kPlayerHitRadius;
extern Parameter<float> kPlayerMoveDelta;
extern Parameter<float> kPlayerRadius;
extern Parameter<float> kPlayerTrailAlphaStart;
extern Parameter<float> kPlayerTrailFadeCoefficient;
extern Parameter<int> kPlayerTrailLength;
extern Parameter<int> kPlayerTrailSpacing;
extern Parameter<int> kPointsToWin;

extern Parameter<float> kRestitution;
extern Parameter<float> kRotateAlphaRate;
extern Parameter<float> kRotateAlphaStart;

extern Parameter<float> kSmoothGravityDiscontinuityXRange;
extern Parameter<float> kSmoothGravityDiscontinuityYRange;
extern Parameter<float> kStrikeAlphaRate;
extern Parameter<float> kStrikeAlphaStart;

extern Parameter<float> kTimeStep;

extern Parameter<int> kWidth;

extern Parameter<b2Vec2> kZeroGravity;

/**
 * Video properties.
 */
constexpr const char *kGlutDisplayString = "rgba double depth alpha samples>=4";

inline b2Vec2 GetTopLeftQuadrantGravity(int position) {
  switch (position) {
    case 0:
      return kGravity;
      break;
    case 1:
      return kGravity;
      break;
    case 2:
      return kAntiGravity;
      break;
    default:
      return kGravity;
      break;
  }
}

inline b2Vec2 GetTopRightQuadrantGravity(int position) {
  switch (position) {
    case 0:
      return kGravity;
      break;
    case 1:
      return kGravity;
      break;
    case 2:
      return kAntiGravity;
      break;
    default:
      return kGravity;
      break;
  }
}

inline b2Vec2 GetBottomLeftQuadrantGravity(int position) {
  switch (position) {
    case 0:
      return kAntiGravity;
      break;
    case 1:
      return kAntiGravity;
      break;
    case 2:
      return kGravity;
      break;
    default:
      return kAntiGravity;
      break;
  }
}

inline b2Vec2 GetBottomRightQuadrantGravity(int position) {
  switch (position) {
    case 0:
      return kAntiGravity;
      break;
    case 1:
      return kAntiGravity;
      break;
    case 2:
      return kGravity;
      break;
    default:
      return kAntiGravity;
      break;
  }
}

/**
 * Model Properties
 */

const ofPoint kPlayer1TopBack[] = {
  ofPoint(-/*kHalfCourtWidth*/10 + /*kPlayerRadius*/17.0/60.0, /*kPlayerRadius*/17.0/60.0),
  ofPoint(/*kHalfCourtWidth*/10 - /*kPlayerRadius*/17.0/60.0, /*kPlayerRadius*/17.0/60.0),
  ofPoint(/*kHalfCourtWidth*/10 - /*kPlayerRadius*/17.0/60.0, -/*kHalfCourtHeight*/5 + /*kPlayerRadius*/17.0/60.0),
  ofPoint(-/*kHalfCourtWidth*/10 + /*kPlayerRadius*/17.0/60.0, -/*kHalfCourtHeight*/5 + /*kPlayerRadius*/17.0/60.0)
};
const ofPoint kPlayer1TopForward[] = {
  ofPoint(-/*kPlayerRadius*/17.0/60.0, /*kPlayerRadius*/17.0/60.0),
  ofPoint(/*kPlayerRadius*/17.0/60.0, /*kPlayerRadius*/17.0/60.0),
  ofPoint(/*kPlayerRadius*/17.0/60.0, -/*kHalfCourtHeight*/5 + /*kPlayerRadius*/17.0/60.0),
  ofPoint(-/*kPlayerRadius*/17.0/60.0, -/*kHalfCourtHeight*/5 + /*kPlayerRadius*/17.0/60.0)
};

const ofPoint kPlayer2TopBack[] = {
  ofPoint(/*kHalfCourtWidth*/10 - /*kPlayerRadius*/17.0/60.0, /*kPlayerRadius*/17.0/60.0),
  ofPoint(/*kHalfCourtWidth*/10 - /*kPlayerRadius*/17.0/60.0, -/*kHalfCourtHeight*/5 + /*kPlayerRadius*/17.0/60.0),
  ofPoint(-/*kHalfCourtWidth*/10 + /*kPlayerRadius*/17.0/60.0, -/*kHalfCourtHeight*/5 + /*kPlayerRadius*/17.0/60.0),
  ofPoint(-/*kHalfCourtWidth*/10 + /*kPlayerRadius*/17.0/60.0, /*kPlayerRadius*/17.0/60.0)
};
const ofPoint kPlayer2TopForward[] = {
  ofPoint(/*kPlayerRadius*/17.0/60.0, /*kPlayerRadius*/17.0/60.0),
  ofPoint(/*kPlayerRadius*/17.0/60.0, -/*kHalfCourtHeight*/5 + /*kPlayerRadius*/17.0/60.0),
  ofPoint(-/*kPlayerRadius*/17.0/60.0, -/*kHalfCourtHeight*/5 + /*kPlayerRadius*/17.0/60.0),
  ofPoint(-/*kPlayerRadius*/17.0/60.0, /*kPlayerRadius*/17.0/60.0)
};

const ofPoint kPlayer1BottomBack[] = {
  -kPlayer1TopBack[0],
  -kPlayer1TopBack[1],
  -kPlayer1TopBack[2],
  -kPlayer1TopBack[3]
};
const ofPoint kPlayer1BottomForward[] = {
  -kPlayer1TopForward[0],
  -kPlayer1TopForward[1],
  -kPlayer1TopForward[2],
  -kPlayer1TopForward[3]
};

const ofPoint kPlayer2BottomBack[] = {
  -kPlayer2TopBack[0],
  -kPlayer2TopBack[1],
  -kPlayer2TopBack[2],
  -kPlayer2TopBack[3]
};
const ofPoint kPlayer2BottomForward[] = {
  -kPlayer2TopForward[0],
  -kPlayer2TopForward[1],
  -kPlayer2TopForward[2],
  -kPlayer2TopForward[3]
};

/**
 * View properties.
 */
const ofMatrix4x4 kViewMatrix =
    ofMatrix4x4::newScaleMatrix(/*kWidth*/ 1200 / /*kCourtWidth*/ 20, -/*kWidth*/ 1200 / /*kCourtWidth*/ 20, 1) *
        ofMatrix4x4::newTranslationMatrix(/*kHalfWidth*/ 600, /*kHalfHeight*/ 300, 0.0);
const ofMatrix4x4 kViewMatrixInverse = ofMatrix4x4::getInverseOf(kViewMatrix);

#endif  // WITCHBALL_CONSTANTS_H_
