#ifndef WITCHBALL_CONSTANTS_H_
#define WITCHBALL_CONSTANTS_H_

#include <Box2D/Box2D.h>

constexpr float kAngularDamping = 0.1;

constexpr float kBallRadius = 25.0;

constexpr int kBox2dPositionIterations = 3;

constexpr int kBox2dVelocityIterations = 8;

constexpr float kDensity = 1.0;

constexpr float kFriction = 0.3;

const b2Vec2 kGravity = b2Vec2(0.0, 9.81); // m/s^2

constexpr int kHeight = 768; // pixels

constexpr float kLinearDamping = 0.1;

constexpr float kRestitution = 0.7;

constexpr float kTimeStep = 1.0 / 60.0; // seconds

constexpr int kWidth = 1024; // pixels

#endif  // WITCHBALL_CONSTANTS_H_
