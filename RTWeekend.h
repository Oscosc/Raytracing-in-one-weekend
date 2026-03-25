#pragma once

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degreesToRadians(double degrees) {
    return degrees * pi / 180.0;
}


// Common Headers

#include "Color.h"
#include "Interval.h"
#include "Ray.h"
#include "vec3.h"