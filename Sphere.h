#pragma once

#include "Hittable.h"

class Sphere : public Hittable
{
public:
    Sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override {
        vec3 oc = center - r.origin();
        double a = r.direction().lengthSquared();
        double h = dot(r.direction(), oc);
        double c = oc.lengthSquared() - radius * radius;

        double discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;
        
        double sqrtd = std::sqrt(discriminant);

        double root = (h - sqrtd) / a;
        if (!rayT.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!rayT.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outwardNormal = (rec.p - center) / radius;
        rec.setFaceNormal(r, outwardNormal);

        return true;
    }


private:
    point3 center;
    double radius;
};