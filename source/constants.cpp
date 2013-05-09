#include "constants.h"
#include "parameter.h"

/**
 * MOUSE BUTTONS!!
 */
DEFINE_PARAMETER(int, kPlayer1MouseButton, 2);
DEFINE_PARAMETER(int, kPlayer2MouseButton, 0);

DEFINE_PARAMETER_RANGE(float, kAngularDamping, 0.0, 0.0, 1.0);
DEFINE_PARAMETER(b2Vec2, kAntiGravity, b2Vec2(0.0, DEPENDENCY(kGravityStrength)));
DEFINE_PARAMETER(float, kAspectRatio, 2.0);
//                 static_cast<float>(DEPENDENCY(kWidth)) / static_cast<float>(DEPENDENCY(kHeight)));

DEFINE_PARAMETER_RANGE(float, kBallRadius, 11.0 * DEPENDENCY(kPixelScale), 0.0, 1.0);

DEFINE_PARAMETER_RANGE(float, kBallTrailAlphaStart, 128.0, 0.0, 255.0);
DEFINE_PARAMETER_RANGE(float, kBallTrailFadeCoefficient, 0.65, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(int, kBallTrailLength, 30, 0, 128);
DEFINE_PARAMETER_RANGE(int, kBallTrailSpacing, 1, 1, 128);
DEFINE_PARAMETER_RANGE(int, kBox2dPositionIterations, 3, 1, 10);
DEFINE_PARAMETER_RANGE(int, kBox2dVelocityIterations, 8, 1, 10);
DEFINE_PARAMETER(b2Vec2, kBumperForce, b2Vec2(DEPENDENCY(kBumperForceStrength), 0.0));
DEFINE_PARAMETER_RANGE(float, kBumperForceStrength, 0.2, 0.0, 5.0);

DEFINE_PARAMETER_RANGE(float, kCollisionDelay, 0.5, 0.0, 2.0);
DEFINE_PARAMETER_RANGE(float, kControllerRateX, 1.0 / 5.0, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, kControllerRateY, 0.06, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, kCourtHeight,
                       DEPENDENCY(kCourtWidth) / DEPENDENCY(kAspectRatio), 1.0, 50.0);
DEFINE_PARAMETER_RANGE(float, kCourtWidth, 20.0, 1.0, 50.0);

DEFINE_PARAMETER_RANGE(float, kDampingSpeed, 12.0, 0.0, 1000.0);
DEFINE_PARAMETER_RANGE(float, kDampingSpeedBump, 1.0, 1.0, 5.0);
DEFINE_PARAMETER_RANGE(float, kDampingSpeedMinimum, 12.0, 0.0, 1000.0);
DEFINE_PARAMETER_RANGE(float, kDampingSpeedRate, 0.00001, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, kDensity, 1.0, 0.1, 10.0);

DEFINE_PARAMETER_RANGE(int, kFixedRotation, 1, 0, 1);
DEFINE_PARAMETER_RANGE(float, kFrameRate, 60.0, 1.0, 100.0);
DEFINE_PARAMETER_RANGE(float, kFriction, 0.0, 0.0, 1.0);

DEFINE_PARAMETER(b2Vec2, kGravity, b2Vec2(0.0, -DEPENDENCY(kGravityStrength)));
DEFINE_PARAMETER_RANGE(float, kGravityMixerRate, 0.05, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, kGravityStrength, 2.81, 0.0, 25.0);

DEFINE_PARAMETER(float, kHalfCourtHeight, DEPENDENCY(kCourtHeight) / 2.0);
DEFINE_PARAMETER(float, kHalfCourtWidth, DEPENDENCY(kCourtWidth) / 2.0);
DEFINE_PARAMETER(float, kHalfHeight, DEPENDENCY(kHeight) / 2.0);
DEFINE_PARAMETER(float, kHalfWidth, DEPENDENCY(kWidth) / 2.0);
DEFINE_PARAMETER_RANGE(int, kHeight, 600, 1, 1080);

DEFINE_PARAMETER_RANGE(float, kLinearDamping, 0.05, 0.0, 1.0);

DEFINE_PARAMETER_RANGE(float, kPixelScale, DEPENDENCY(kCourtWidth) / DEPENDENCY(kWidth), 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, kPlayerHitRadius,
                       33.0 * DEPENDENCY(kCourtWidth) / DEPENDENCY(kWidth), 0.0, 3.0);
DEFINE_PARAMETER_RANGE(float, kPlayerMoveDelta, 0.020, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, kPlayerRadius,
                       17.0 * DEPENDENCY(kCourtWidth) / DEPENDENCY(kWidth), 0.0, 2.0);
DEFINE_PARAMETER_RANGE(float, kPlayerTrailAlphaStart, 128.0, 0.0, 255.0);
DEFINE_PARAMETER_RANGE(float, kPlayerTrailFadeCoefficient, 0.65, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(int, kPlayerTrailLength, 10, 0, 128);
DEFINE_PARAMETER_RANGE(int, kPlayerTrailSpacing, 1, 1, 128);
DEFINE_PARAMETER_RANGE(int, kPointsToWin, 7, 1, 10);

DEFINE_PARAMETER_RANGE(float, kRestitution, 1.0, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, kRotateAlphaRate, 0.01, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, kRotateAlphaStart, 1.0, 0.0, 1.0);

DEFINE_PARAMETER_RANGE(float, kStrikeAlphaRate, 0.01, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, kStrikeAlphaStart, 1.0, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, kSmoothGravityDiscontinuityXRange,
                       10.0 * DEPENDENCY(kBallRadius), 0.0, 20.0);
DEFINE_PARAMETER_RANGE(float, kSmoothGravityDiscontinuityYRange,
                       10.0 * DEPENDENCY(kBallRadius), 0.0, 20.0);

DEFINE_PARAMETER_RANGE(float, kTimeStep, 1.0 / DEPENDENCY(kFrameRate), 1.0 / 1000.0, 1.0);

DEFINE_PARAMETER_RANGE(int, kWidth, 1200, 1, 1920);

DEFINE_PARAMETER(ofMatrix4x4, kViewMatrix,
                 ofMatrix4x4::newScaleMatrix(DEPENDENCY(kWidth) / DEPENDENCY(kCourtWidth),
                                             -DEPENDENCY(kWidth) / DEPENDENCY(kCourtWidth), 1) *
                 ofMatrix4x4::newTranslationMatrix(DEPENDENCY(kHalfWidth),
                                                   DEPENDENCY(kHalfHeight), 0.0));
DEFINE_PARAMETER(ofMatrix4x4, kViewMatrixInverse,
                 ofMatrix4x4::getInverseOf(DEPENDENCY(kViewMatrix)));

DEFINE_PARAMETER(b2Vec2, kZeroGravity, b2Vec2(0.0, 0.0));
