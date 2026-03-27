#pragma once

#include "Interval.h"
#include "vec3.h"

using Color = vec3;

inline double linearToGamma(double linearComponent) {
    if(linearComponent > 0)
        return std::sqrt(linearComponent);
    return 0;
}

void writeColor(std::ostream& out, const Color& pixelColor) {
    double r = pixelColor.x();
    double g = pixelColor.y();
    double b = pixelColor.z();

    r = linearToGamma(r);
    g = linearToGamma(g);
    b = linearToGamma(b);

    static const Interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}