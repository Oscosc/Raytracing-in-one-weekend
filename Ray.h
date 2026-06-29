#pragma once

#include "vec3.h"

class Ray
{
public:
    Ray() {}

    Ray(const point3& origin, const vec3& direction, double time) : orig(origin), dir(direction), tm(time) {}

    Ray(const point3& origin, const vec3& direction) : Ray(origin, direction, 0) {}

    const point3& origin() const { return orig; }
    const vec3& direction() const { return dir; }
    double time() const { return tm; }

    point3 at(double t) const {
        return orig + t * dir;
    }

private:
    point3 orig;
    vec3 dir;
    double tm;
};