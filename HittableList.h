#pragma once

#include "Hittable.h"

#include <vector>

class HittableList : public Hittable
{
public:
    std::vector<std::shared_ptr<Hittable>> objects;

    HittableList() {}
    HittableList(std::shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(std::shared_ptr<Hittable> object) {
        objects.push_back(object);
    }

    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override {
        HitRecord tmpRec;
        bool hitAnything = false;
        double closestSoFar = rayT.max;

        for (const std::shared_ptr<Hittable>& object : objects) {
            if (object->hit(r, Interval(rayT.min, closestSoFar), tmpRec)) {
                hitAnything = true;
                closestSoFar = tmpRec.t;
                rec = tmpRec;
            }
        }

        return hitAnything;
    }
};