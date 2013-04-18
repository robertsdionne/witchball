//
//  constants.cpp
//  emptyExample
//
//  Created by Shervin Ghazazani on 4/16/13.
//
//

#include "constants.h"
#include <Box2D.h>
#include "ofMain.h"
#include "utilities.h"

/**
 * Audio properties.
 */
const int kConcurrentSounds = 10;

const char *kBackgroundMusicFilename = "bgm.wav";
const char *kBackgroundMusicTwoFilename = "bgm2.wav";
const char *kBackhit1 = "backhit1.wav";
const char *kBackhit2 = "backhit2.wav";
const char *kBackhit3 = "backhit3.wav";
const char *kBackhit4 = "backhit4.wav";
const char *kHit1 = "hit1.wav";
const char *kHit2 = "hit2.wav";
const char *kHit3 = "hit3.wav";
const char *kHit4 = "hit4.wav";
const char *kWallBounceFilename = "wallbounce.wav";

/**
 * Video properties.
 */
const int kHeight = 768; // pixels
const int kWidth = 1024; // pixels
const char *kGlutDisplayString = "rgba double depth alpha samples>=4";
const float kHalfHeight = kHeight / 2; // pixels
const float kHalfWidth = kWidth / 2; // pixels
const float kAspectRatio = static_cast<float>(kWidth) / static_cast<float>(kHeight);

/**
 * Level properties.
 */
const float kCourtWidth = 20.0; // m
const float kCourtHeight = kCourtWidth / kAspectRatio; // m
const float kHalfCourtWidth = kCourtWidth / 2.0; // m
const float kHalfCourtHeight = kCourtHeight / 2.0; // m

/**
 * Physics properties.
 */
const float kAngularDamping = 0.0;
const b2Vec2 kAntiGravity = b2Vec2(0.0, 9.81); // m/s^2
const float kBallRadius = 11.0 * kCourtWidth / kWidth;
const int kBox2dPositionIterations = 3;
const int kBox2dVelocityIterations = 8;
const float kDampingSpeed = 10.0;
const float kDensity = 1.0; // kg/m^2
const bool kFixedRotation = true;
const float kFriction = 0.0;
const b2Vec2 kGravity = b2Vec2(0.0, -9.81); // m/s^2
const float kLinearDamping = 0.1;
const float kMouseDensity = 10.0;
const float kMouseMass = 50.0;
const float kPlayerRadius = 17.0 * kCourtWidth / kWidth;
const float kRestitution = 0.99;
const float kSmoothGravityDiscontinuityXRange = 10.0 * kBallRadius;
const float kSmoothGravityDiscontinuityYRange = 10.0 * kBallRadius;
const float kTimeStep = 1.0 / 60.0; // seconds
const b2Vec2 kZeroGravity = b2Vec2(0.0, 0.0); // m/s^2

const b2Vec2 kTopLeftGravity = Box2dVector(-9.81 * ofVec2f(-1.0, 1.0).normalized());
const b2Vec2 kTopRightGravity = Box2dVector(-9.81 * ofVec2f(1.0, 1.0).normalized());
const b2Vec2 kBottomLeftGravity = Box2dVector(-9.81 * ofVec2f(-1.0, -1.0).normalized());
const b2Vec2 kBottomRightGravity = Box2dVector(-9.81 * ofVec2f(1.0, -1.0).normalized());

const float kGravityAngle[] = {
  0.0,
  90.0,
  180.0,
  270.0
};

const b2Vec2 kTopLeftQuadrantGravity[] = {
  kTopLeftGravity,
  kTopRightGravity,
  kBottomRightGravity,
  kBottomLeftGravity
};

const b2Vec2 kTopRightQuadrantGravity[] = {
  kTopRightGravity,
  kBottomRightGravity,
  kBottomLeftGravity,
  kTopLeftGravity
};

const b2Vec2 kBottomLeftQuadrantGravity[] = {
  kBottomLeftGravity,
  kTopLeftGravity,
  kTopRightGravity,
  kBottomRightGravity
};

const b2Vec2 kBottomRightQuadrantGravity[] = {
  kBottomRightGravity,
  kBottomLeftGravity,
  kTopLeftGravity,
  kTopRightGravity
};

/**
 * Model Properties
 */
const float kBallTrailAlphaStart = 128.0;
const float kBallTrailFadeCoefficient = 0.9;
const int kBallTrailLength = 30;
const int kBallTrailSpacing = 1;

const float kGravityMixerRate = 0.05;
const float kPlayerMoveDelta = 0.015;
const int kPointsToWin = 7;
const float kPlayerBallCollisionMultiplier = 0.1;
const float kPlayerTrailAlphaStart = 128.0;
const float kPlayerTrailFadeCoefficient = 0.65;
const int kPlayerTrailLength = 10;
const int kPlayerTrailSpacing = 1;

/**
 * Controller properties.
 */
const float kControllerRateX = 1.0 / 5.0;
const float kControllerRateY = 1.0 / 40.0;

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
