#pragma once

class HitRecord
{
public:
    point3 p;
    vec3 normal;
    double t;
    bool frontFace;

    void setFaceNormal(const Ray& r, const vec3& outwardNormal) {
        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& r, Interval rayT, HitRecord& rec) const = 0;
};