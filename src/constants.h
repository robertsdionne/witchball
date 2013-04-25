#ifndef WITCHBALL_CONSTANTS_H_
#define WITCHBALL_CONSTANTS_H_

#include <Box2D.h>

#include "ofMain.h"
#include "utilities.h"

/**
 * Audio properties.
 */
extern const int kConcurrentSounds;

extern const char *kBackgroundMusicFilename;
extern const char *kBackgroundMusicTwoFilename;
extern const char *kBackhit1;
extern const char *kBackhit2;
extern const char *kBackhit3;
extern const char *kBackhit4;
extern const char *kHit1;
extern const char *kHit2;
extern const char *kHit3;
extern const char *kHit4;
extern const char *kWallBounceFilename;

/**
 * Video properties.
 */
extern const int kHeight;
extern const int kWidth;
extern const char *kGlutDisplayString;
extern const float kHalfHeight;
extern const float kHalfWidth;
extern const float kAspectRatio;

/**
 * Level properties.
 */
extern const float kCourtWidth;
extern const float kCourtHeight;
extern const float kHalfCourtWidth;
extern const float kHalfCourtHeight;

/**
 * Physics properties.
 */
extern const float kAngularDamping;
extern const b2Vec2 kAntiGravity;
extern const float kBallRadius;
extern const int kBox2dPositionIterations;
extern const int kBox2dVelocityIterations;
extern const float kDampingSpeed;
extern const float kDensity;
extern const bool kFixedRotation;
extern const float kFriction;
extern const b2Vec2 kGravity;
extern const float kLinearDamping;
extern const float kMouseDensity;
extern const float kMouseMass;
extern const float kPlayerRadius;
extern const float kRestitution;
extern const float kSmoothGravityDiscontinuityXRange;
extern const float kSmoothGravityDiscontinuityYRange;
extern const float kTimeStep;
extern const b2Vec2 kZeroGravity;

extern const b2Vec2 kTopLeftGravity;
extern const b2Vec2 kTopRightGravity;
extern const b2Vec2 kBottomLeftGravity;
extern const b2Vec2 kBottomRightGravity;

extern const float kGravityAngle[];
extern const b2Vec2 kTopLeftQuadrantGravity[];
extern const b2Vec2 kTopRightQuadrantGravity[];
extern const b2Vec2 kBottomLeftQuadrantGravity[];
extern const b2Vec2 kBottomRightQuadrantGravity[];

/**
 * Model Properties
 */
extern const float kBallTrailAlphaStart;
extern const float kBallTrailFadeCoefficient;
extern const int kBallTrailLength;
extern const int kBallTrailSpacing;

extern const float kGravityMixerRate;
extern const float kPlayerMoveDelta;
extern const int kPointsToWin;
extern const float kPlayerBallCollisionMultiplier;
extern const float kPlayerTrailAlphaStart;
extern const float kPlayerTrailFadeCoefficient;
extern const int kPlayerTrailLength;
extern const int kPlayerTrailSpacing;

/**
 * Controller properties.
 */
extern const float kControllerRateX;
extern const float kControllerRateY;

extern const ofPoint kPlayer1TopBack[];
extern const ofPoint kPlayer1TopForward[];
extern const ofPoint kPlayer2TopBack[];
extern const ofPoint kPlayer2TopForward[];
extern const ofPoint kPlayer1BottomBack[];
extern const ofPoint kPlayer1BottomForward[];
extern const ofPoint kPlayer2BottomBack[];
extern const ofPoint kPlayer2BottomForward[];

/**
 * View properties.
 */
extern const ofMatrix4x4 kViewMatrix;
extern const ofMatrix4x4 kViewMatrixInverse;

#endif  // WITCHBALL_CONSTANTS_H_
