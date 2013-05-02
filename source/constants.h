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
extern Parameter<float> kDampingSpeedBump;
extern Parameter<float> kDampingSpeedMinimum;
extern Parameter<float> kDampingSpeedRate;
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

extern Parameter<ofMatrix4x4> kViewMatrix;
extern Parameter<ofMatrix4x4> kViewMatrixInverse;

extern Parameter<int> kWidth;

extern Parameter<b2Vec2> kZeroGravity;

/**
 * Video properties.
 */
constexpr const char *kGlutDisplayString = "rgba double depth alpha ";

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

inline ofVec2f GetPlayer1TopLeft(int position) {
  switch (position) {
    case 0:
      return ofVec2f(-kHalfCourtWidth + kPlayerRadius, kPlayerRadius);
      break;
    case 1:
      return ofVec2f(kPlayerRadius, kPlayerRadius);
      break;
    case 2:
      return ofVec2f(kPlayerRadius, -kHalfCourtHeight + kPlayerRadius);
      break;
    default:
      return ofVec2f(-kHalfCourtWidth + kPlayerRadius, -kHalfCourtHeight + kPlayerRadius);
      break;
  }
}

inline ofVec2f GetPlayer1TopRight(int position) {
  switch (position) {
    case 0:
      return ofVec2f(-kPlayerRadius, kPlayerRadius);
      break;
    case 1:
      return ofVec2f(kHalfCourtWidth - kPlayerRadius, kPlayerRadius);
      break;
    case 2:
      return ofVec2f(kHalfCourtWidth - kPlayerRadius, -kHalfCourtHeight + kPlayerRadius);
      break;
    default:
      return ofVec2f(-kPlayerRadius, -kHalfCourtHeight + kPlayerRadius);
      break;
  }
}

inline ofVec2f GetPlayer2TopLeft(int position) {
  switch (position) {
    case 0:
      return ofVec2f(kHalfCourtWidth - kPlayerRadius, kPlayerRadius);
      break;
    case 1:
      return ofVec2f(kHalfCourtWidth - kPlayerRadius, -kHalfCourtHeight + kPlayerRadius);
      break;
    case 2:
      return ofVec2f(-kPlayerRadius, -kHalfCourtHeight + kPlayerRadius);
      break;
    default:
      return ofVec2f(-kPlayerRadius, kPlayerRadius);
      break;
  }
}

inline ofVec2f GetPlayer2TopRight(int position) {
  switch (position) {
    case 0:
      return ofVec2f(kPlayerRadius, kPlayerRadius);
      break;
    case 1:
      return ofVec2f(kPlayerRadius, -kHalfCourtHeight + kPlayerRadius);
      break;
    case 2:
      return ofVec2f(-kHalfCourtWidth + kPlayerRadius, -kHalfCourtHeight + kPlayerRadius);
      break;
    default:
      return ofVec2f(-kHalfCourtWidth + kPlayerRadius, kPlayerRadius);
      break;
  }
}

inline ofVec2f GetPlayer1BottomLeft(int position) {
  return -GetPlayer1TopLeft(position);
}

inline ofVec2f GetPlayer1BottomRight(int position) {
  return -GetPlayer1TopRight(position);
}

inline ofVec2f GetPlayer2BottomLeft(int position) {
  return -GetPlayer2TopLeft(position);
}

inline ofVec2f GetPlayer2BottomRight(int position) {
  return -GetPlayer2TopRight(position);
}

#endif  // WITCHBALL_CONSTANTS_H_
