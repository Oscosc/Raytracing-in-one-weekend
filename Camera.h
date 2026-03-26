#pragma once

#include "Hittable.h"

class Camera
{
public:
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;

    void render(const Hittable& world) {
        initialize();

        std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

        for (int j = 0; j < imageHeight; j++) {
            std::clog << "\rScanlines remaining: " << (imageHeight - j) << " " << std::flush;
            for (int i = 0; i < imageWidth; i++) {
                auto pixelCenter = pixel00Loc + (i * pixelDeltaU) + (j * pixelDeltaV);
                auto rayDirection = pixelCenter - center;
                Ray r(center, rayDirection);

                Color pixelColor = rayColor(r, world);
                writeColor(std::cout, pixelColor);
            }
        }

        std::clog << "\rDone.                 \n";
    }

private:
    int    imageHeight;
    point3 center;
    point3 pixel00Loc;
    vec3   pixelDeltaU;
    vec3   pixelDeltaV;

    void initialize() {
        imageHeight = int(imageWidth / aspectRatio);
        imageHeight = (imageHeight < 1) ? 1 : imageHeight;

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

    Color rayColor(const Ray& r, const Hittable& world) const {
        HitRecord rec;

        if (world.hit(r, Interval(0, infinity), rec)) {
            return 0.5 * (rec.normal + Color(1, 1, 1));
        }

        vec3 unitDirection = unitVector(r.direction());
        double a = 0.5 * (unitDirection.y() + 1.0);
        return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
    }

};