#ifndef WITCHBALL_CONSTANTS_H_
#define WITCHBALL_CONSTANTS_H_

#include <Box2D/Box2D.h>

constexpr int kBox2dPositionIterations = 3;

constexpr int kBox2dVelocityIterations = 8;

const b2Vec2 kGravity = b2Vec2(0.0, 9.81); // m/s^2

constexpr int kHeight = 768; // pixels

constexpr float kTimeStep = 1.0 / 60.0; // seconds

constexpr int kWidth = 1024; // pixels

#endif  // WITCHBALL_CONSTANTS_H_
