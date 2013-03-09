#ifndef WITCHBALL_CONSTANTS_H_
#define WITCHBALL_CONSTANTS_H_

#include <Box2D/Box2D.h>

#include "ofMain.h"

constexpr int kHeight = 600; // pixels

constexpr int kWidth = 1200; // pixels

constexpr float kAngularDamping = 0.1;

const b2Vec2 kAntiGravity = b2Vec2(0.0, 9.81); // m/s^2

constexpr float kAspectRatio = static_cast<float>(kWidth) / static_cast<float>(kHeight);

constexpr int kBox2dPositionIterations = 3;

constexpr int kBox2dVelocityIterations = 8;

constexpr float kCourtWidth = 20.0;

constexpr float kBallRadius = 11.0 * kCourtWidth / kWidth;

constexpr float kHalfCourtWidth = kCourtWidth / 2.0;

constexpr float kHalfCourtHeight = kHalfCourtWidth / kAspectRatio;

constexpr float kDensity = 1.0;

constexpr float kFriction = 0.3;

const b2Vec2 kGravity = b2Vec2(0.0, -9.81); // m/s^2

constexpr float kHalfHeight = kHeight / 2;

constexpr float kHalfWidth = kWidth / 2;

constexpr float kLinearDamping = 0.1;

constexpr float kRestitution = 0.7;

constexpr float kTimeStep = 1.0 / 60.0; // seconds

const ofMatrix4x4 kViewMatrix =
    ofMatrix4x4::newScaleMatrix(kWidth / kCourtWidth, -kWidth / kCourtWidth, 1) *
        ofMatrix4x4::newTranslationMatrix(kHalfWidth, kHalfHeight, 0.0);

const ofMatrix4x4 kViewMatrixInverse = ofMatrix4x4::getInverseOf(kViewMatrix);

const b2Vec2 kZeroGravity = b2Vec2(0.0, 0.0); // m/s^2

#endif  // WITCHBALL_CONSTANTS_H_
