// This file is a part of VRSuit project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <math/MathTypes.h>

// direction in (0, 360)
// height in (-90,90)
void updateCamera(Real yaw, Real pitch, Real zoom)
{
    V3 init = V3X;
    V3 cameraPositionXY = init * rotateAroundZ(yaw);
    V3 cameraPositionXYPerpendicular = V3X * rotateAroundZ(yaw + 90);
    V3 cameraPositionNormalized = cameraPositionXY * rotateAround(cameraPositionXYPerpendicular, pitch);
    V3 cameraPosition = cameraPositionNormalized * zoom;
    V3 cameraDirection = -1.0 * cameraPositionNormalized;
    // glSetCamera(cameraPosition, cameraDirection);
}
