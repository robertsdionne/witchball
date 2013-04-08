#include "constants.h"
#include "parameter.h"

DEFINE_PARAMETER_RANGE(float, kBallTrailAlphaStart, 128.0, 0.0, 255.0);
DEFINE_PARAMETER_RANGE(float, kBallTrailFadeCoefficient, 0.65, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(int, kBallTrailLength, 30, 0, 128);
DEFINE_PARAMETER_RANGE(int, kBallTrailSpacing, 1, 1, 128);

DEFINE_PARAMETER_RANGE(float, kControllerRateX, 1.0 / 5.0, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(float, kControllerRateY, 1.0 / 40.0, 0.0, 1.0);

DEFINE_PARAMETER_RANGE(float, kPlayerTrailAlphaStart, 128.0, 0.0, 255.0);
DEFINE_PARAMETER_RANGE(float, kPlayerTrailFadeCoefficient, 0.65, 0.0, 1.0);
DEFINE_PARAMETER_RANGE(int, kPlayerTrailLength, 10, 0, 128);
DEFINE_PARAMETER_RANGE(int, kPlayerTrailSpacing, 1, 1, 128);
