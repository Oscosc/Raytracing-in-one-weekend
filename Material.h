#pragma once

#include "Hittable.h"

class Material
{
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered)
    const {
        return false;
    }
};


class Lambertian : public Material
{
public:
    Lambertian(const Color& albedo) : albedo(albedo) {}

    bool scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered)
    const override {
        
        vec3 scatterDirection = rec.normal + randomUnitVector();

        if(scatterDirection.nearZero())
            scatterDirection = rec.normal;

        scattered = Ray(rec.p, scatterDirection);
        attenuation = albedo;
        return true;
    }

private:
    Color albedo;
};


class Metal : public Material
{
public:
    Metal(const Color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered)
    const override {
        
        vec3 reflected = reflect(rayIn.direction(), rec.normal);
        reflected = unitVector(reflected) + (fuzz * randomUnitVector());

        scattered = Ray(rec.p, reflected);
        attenuation = albedo;
        return true;
    }

private:
    Color albedo;
    double fuzz;
};


class Dielectric : public Material
{
public:
    Dielectric(double refractionIndex) : refractionIndex(refractionIndex) {}

    bool scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered)
    const override {
        attenuation = Color(1, 1, 1);
        double ri = rec.frontFace ? (1.0 / refractionIndex) : refractionIndex;

        vec3 unitDirection = unitVector(rayIn.direction());
        double cosTheta = std::fmin(dot(-unitDirection, rec.normal), 1.0);
        double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

        bool cannotRefract = ri * sinTheta > 1.0;
        vec3 direction;

        if (cannotRefract || reflectance(cosTheta, ri) > randomDouble())
            direction = reflect(unitDirection, rec.normal);
        else
            direction = refract(unitDirection, rec.normal, ri);

        scattered = Ray(rec.p, direction);
        return true;
    }

private:
    double refractionIndex;

    // Schlick's approximation of reflectance
    static double reflectance(double cosine, double refractionIndex) {
        double r0 = (1 - refractionIndex) / (1 + refractionIndex);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }
};