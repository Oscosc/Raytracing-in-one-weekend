#pragma once

#include "Hittable.h"
#include "Material.h"

class Camera
{
public:
    double aspectRatio     = 16.0 / 9.0;
    int    imageWidth      = 400;
    int    samplesPerPixel = 10;
    int    maxDepth        = 10;

    void render(const Hittable& world) {
        initialize();

        std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

        for (int j = 0; j < imageHeight; j++) {
            std::clog << "\rScanlines remaining: " << (imageHeight - j) << " " << std::flush;
            for (int i = 0; i < imageWidth; i++) {
                Color pixelColor(0, 0, 0);
                for (int sample = 0; sample < samplesPerPixel; sample++) {
                    Ray r = getRay(i, j);
                    pixelColor += rayColor(r, maxDepth, world);
                }
                writeColor(std::cout, pixelSamplesScale * pixelColor);
            }
        }

        std::clog << "\rDone.                 \n";
    }

private:
    int    imageHeight;
    double pixelSamplesScale;
    point3 center;
    point3 pixel00Loc;
    vec3   pixelDeltaU;
    vec3   pixelDeltaV;

    void initialize() {
        imageHeight = int(imageWidth / aspectRatio);
        imageHeight = (imageHeight < 1) ? 1 : imageHeight;

        pixelSamplesScale = 1.0 / samplesPerPixel;

        center = point3(0, 0, 0);

        double focalLength = 1.0;
        double viewportHeight = 2.0;
        double viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);

        vec3 viewportU = vec3(viewportWidth, 0, 0);
        vec3 viewportV = vec3(0, -viewportHeight, 0);

        pixelDeltaU = viewportU / imageWidth;
        pixelDeltaV = viewportV / imageHeight;

        vec3 viewportUpperLeft = center
            - vec3(0, 0, focalLength) - viewportU/2 - viewportV/2;

        pixel00Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
    }

    Ray getRay(int i, int j) const {
        vec3 offset = sampleSquare();
        vec3 pixelSample = pixel00Loc
                           + ((i + offset.x()) * pixelDeltaU)
                           + ((j + offset.y()) * pixelDeltaV);
        
        point3 rayOrigin = center;
        vec3 rayDirection = pixelSample - rayOrigin;

        return Ray(rayOrigin, rayDirection);
    }

    vec3 sampleSquare() const {
        return vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
    }

    Color rayColor(const Ray& r, int depth, const Hittable& world) const {
        if(depth <= 0)
            return Color(0, 0, 0);

        HitRecord rec;

        if (world.hit(r, Interval(0.001, infinity), rec)) {
            Ray scattered;
            Color attenuation;

            if (rec.mat->scatter(r, rec, attenuation, scattered))
                return attenuation * rayColor(scattered, depth-1, world);
            return Color(0, 0, 0);
        }

        vec3 unitDirection = unitVector(r.direction());
        double a = 0.5 * (unitDirection.y() + 1.0);
        return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
    }

};