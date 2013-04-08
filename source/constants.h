#ifndef WITCHBALL_CONSTANTS_H_
#define WITCHBALL_CONSTANTS_H_

#include <Box2D/Box2D.h>

#include "ofMain.h"
#include "parameter.h"
#include "utilities.h"

/**
 * Audio properties.
 */
constexpr int kConcurrentSounds = 10;

constexpr const char *kBackgroundMusicFilename = "bgm.wav";
constexpr const char *kBackgroundMusicTwoFilename = "bgm2.wav";
constexpr const char *kBackhit1 = "backhit1.wav";
constexpr const char *kBackhit2 = "backhit2.wav";
constexpr const char *kBackhit3 = "backhit3.wav";
constexpr const char *kBackhit4 = "backhit4.wav";
constexpr const char *kHit1 = "hit1.wav";
constexpr const char *kHit2 = "hit2.wav";
constexpr const char *kHit3 = "hit3.wav";
constexpr const char *kHit4 = "hit4.wav";
constexpr const char *kWallBounceFilename = "wallbounce.wav";

/**
 * Video properties.
 */
constexpr int kHeight = 600; // pixels
constexpr int kWidth = 1200; // pixels
constexpr const char *kGlutDisplayString = "rgba double depth alpha samples>=4";
constexpr float kHalfHeight = kHeight / 2; // pixels
constexpr float kHalfWidth = kWidth / 2; // pixels
constexpr float kAspectRatio = static_cast<float>(kWidth) / static_cast<float>(kHeight);

/**
 * Level properties.
 */
constexpr float kCourtWidth = 20.0; // m
constexpr float kCourtHeight = kCourtWidth / kAspectRatio; // m
constexpr float kHalfCourtWidth = kCourtWidth / 2.0; // m
constexpr float kHalfCourtHeight = kCourtHeight / 2.0; // m

/**
 * Physics properties.
 */
constexpr float kAngularDamping = 0.0;
const b2Vec2 kAntiGravity = b2Vec2(0.0, 9.81); // m/s^2
constexpr float kBallRadius = 11.0 * kCourtWidth / kWidth;
constexpr int kBox2dPositionIterations = 3;
constexpr int kBox2dVelocityIterations = 8;
constexpr float kCollisionDelay = 0.4;
constexpr float kDampingSpeed = 12.0;
constexpr float kDensity = 1.0; // kg/m^2
constexpr bool kFixedRotation = true;
constexpr float kFriction = 0.0;
const b2Vec2 kGravity = b2Vec2(0.0, -9.81); // m/s^2
constexpr float kLinearDamping = 0.1;
constexpr float kMouseDensity = 10.0;
constexpr float kMouseMass = 50.0;
constexpr float kPlayerRadius = 17.0 * kCourtWidth / kWidth;
constexpr float kPlayerHitRadius = 33.0 * kCourtWidth / kWidth;
constexpr float kRestitution = 1.0;
constexpr float kSmoothGravityDiscontinuityXRange = 10.0 * kBallRadius;
constexpr float kSmoothGravityDiscontinuityYRange = 10.0 * kBallRadius;
constexpr float kTimeStep = 1.0 / 60.0; // seconds
const b2Vec2 kZeroGravity = b2Vec2(0.0, 0.0); // m/s^2

const b2Vec2 kTopLeftGravity = Box2dVector(-9.81 * ofVec2f(-1.0, 1.0).normalized());
const b2Vec2 kTopRightGravity = Box2dVector(-9.81 * ofVec2f(1.0, 1.0).normalized());
const b2Vec2 kBottomLeftGravity = Box2dVector(-9.81 * ofVec2f(-1.0, -1.0).normalized());
const b2Vec2 kBottomRightGravity = Box2dVector(-9.81 * ofVec2f(1.0, -1.0).normalized());
const b2Vec2 kBumperForce = b2Vec2(0.2,0.0); //force applied to ball when it gets too close to the sides of the field

const b2Vec2 kTopGravity = Box2dVector(-9.81 * ofVec2f(0.0, 1.0).normalized());
const b2Vec2 kBottomGravity = Box2dVector(-9.81 * ofVec2f(0.0, -1.0).normalized());

const float kGravityAngle[] = {
  0.0,
  90.0,
  180.0,
  270.0
};

const b2Vec2 kTopLeftQuadrantGravity[] = {
  kTopGravity,
  kTopGravity,
  kBottomGravity,
  kTopGravity
};

const b2Vec2 kTopRightQuadrantGravity[] = {
  kTopGravity,
  kTopGravity,
  kBottomGravity,
  kTopGravity
};

const b2Vec2 kBottomLeftQuadrantGravity[] = {
  kBottomGravity,
  kBottomGravity,
  kTopGravity,
  kBottomGravity
};

const b2Vec2 kBottomRightQuadrantGravity[] = {
  kBottomGravity,
  kBottomGravity,
  kTopGravity,
  kBottomGravity
};

extern Parameter<float> kBallTrailAlphaStart;
extern Parameter<float> kBallTrailFadeCoefficient;
extern Parameter<int> kBallTrailLength;
extern Parameter<int> kBallTrailSpacing;

extern Parameter<float> kControllerRateX;
extern Parameter<float> kControllerRateY;

extern Parameter<float> kGravityMixerRate;

extern Parameter<float> kPlayerTrailAlphaStart;
extern Parameter<float> kPlayerTrailFadeCoefficient;
extern Parameter<int> kPlayerTrailLength;
extern Parameter<int> kPlayerTrailSpacing;

/**
 * Model Properties
 */

constexpr float kPlayerMoveDelta = 0.015;
constexpr int kPointsToWin = 7;
constexpr float kPlayerBallCollisionMultiplier = 0.1;

constexpr float kStrikeAlphaRate = 0.01;
constexpr float kStrikeAlphaStart = 1.0;
constexpr float kRotateAlphaRate = 0.01;
constexpr float kRotateAlphaStart = 1.0;

const ofPoint kPlayer1TopBack[] = {
  ofPoint(-kHalfCourtWidth + kPlayerRadius, kPlayerRadius),
  ofPoint(kHalfCourtWidth - kPlayerRadius, kPlayerRadius),
  ofPoint(kHalfCourtWidth - kPlayerRadius, -kHalfCourtHeight + kPlayerRadius),
  ofPoint(-kHalfCourtWidth + kPlayerRadius, -kHalfCourtHeight + kPlayerRadius)
};
const ofPoint kPlayer1TopForward[] = {
  ofPoint(-kPlayerRadius, kPlayerRadius),
  ofPoint(kPlayerRadius, kPlayerRadius),
  ofPoint(kPlayerRadius, -kHalfCourtHeight + kPlayerRadius),
  ofPoint(-kPlayerRadius, -kHalfCourtHeight + kPlayerRadius)
};

const ofPoint kPlayer2TopBack[] = {
  ofPoint(kHalfCourtWidth - kPlayerRadius, kPlayerRadius),
  ofPoint(kHalfCourtWidth - kPlayerRadius, -kHalfCourtHeight + kPlayerRadius),
  ofPoint(-kHalfCourtWidth + kPlayerRadius, -kHalfCourtHeight + kPlayerRadius),
  ofPoint(-kHalfCourtWidth + kPlayerRadius, kPlayerRadius)
};
const ofPoint kPlayer2TopForward[] = {
  ofPoint(kPlayerRadius, kPlayerRadius),
  ofPoint(kPlayerRadius, -kHalfCourtHeight + kPlayerRadius),
  ofPoint(-kPlayerRadius, -kHalfCourtHeight + kPlayerRadius),
  ofPoint(-kPlayerRadius, kPlayerRadius)
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
    ofMatrix4x4::newScaleMatrix(kWidth / kCourtWidth, -kWidth / kCourtWidth, 1) *
        ofMatrix4x4::newTranslationMatrix(kHalfWidth, kHalfHeight, 0.0);
const ofMatrix4x4 kViewMatrixInverse = ofMatrix4x4::getInverseOf(kViewMatrix);

#endif  // WITCHBALL_CONSTANTS_H_
