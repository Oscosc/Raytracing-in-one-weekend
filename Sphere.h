#pragma once

#include "Hittable.h"

class Sphere : public Hittable
{
public:
    // Stationary Sphere
    Sphere(const point3& center, double radius, std::shared_ptr<Material> mat)
        : center(center, vec3(0, 0, 0)), radius(std::fmax(0, radius)), mat(mat) {}

    // Moving Sphere
    Sphere(const point3& center1, const point3& center2, double radius, std::shared_ptr<Material> mat)
        : center(center1, center2 - center1), radius(std::fmax(0, radius)), mat(mat) {}

    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override {
        point3 currentCenter = center.at(r.time());
        vec3 oc = currentCenter - r.origin();
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
        vec3 outwardNormal = (rec.p - currentCenter) / radius;
        rec.setFaceNormal(r, outwardNormal);
        rec.mat = mat;

        return true;
    }


private:
    Ray center;
    double radius;
    std::shared_ptr<Material> mat;
};