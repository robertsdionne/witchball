#ifndef WITCHBALL_CONSTANTS_H_
#define WITCHBALL_CONSTANTS_H_

#include <Box2D/Box2D.h>

#include "ofMain.h"

/**
 * Audio properties.
 */
constexpr int kConcurrentSounds = 10;

constexpr const char *kBackgroundMusicFilename = "../../assets/bgm.wav";
constexpr const char *kBackgroundMusicTwoFilename = "../../assets/bgm2.wav";
constexpr const char *kWallBounceFilename = "../../assets/wallbounce.wav";

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
constexpr float kAngularDamping = 0.1;
const b2Vec2 kAntiGravity = b2Vec2(0.0, 9.81); // m/s^2
constexpr float kBallRadius = 11.0 * kCourtWidth / kWidth;
constexpr int kBox2dPositionIterations = 3;
constexpr int kBox2dVelocityIterations = 8;
constexpr float kDensity = 1.0; // kg/m^2
constexpr float kFriction = 0.3;
const b2Vec2 kGravity = b2Vec2(0.0, -9.81); // m/s^2
constexpr float kLinearDamping = 0.1;
constexpr float kPlayerRadius = 17.0 * kCourtWidth / kWidth;
constexpr float kRestitution = 0.7;
constexpr float kTimeStep = 1.0 / 60.0; // seconds
const b2Vec2 kZeroGravity = b2Vec2(0.0, 0.0); // m/s^2

/**
 * View properties.
 */
const ofMatrix4x4 kViewMatrix =
    ofMatrix4x4::newScaleMatrix(kWidth / kCourtWidth, -kWidth / kCourtWidth, 1) *
        ofMatrix4x4::newTranslationMatrix(kHalfWidth, kHalfHeight, 0.0);
const ofMatrix4x4 kViewMatrixInverse = ofMatrix4x4::getInverseOf(kViewMatrix);

#endif  // WITCHBALL_CONSTANTS_H_
