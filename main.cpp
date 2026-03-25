#include "RTWeekend.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"


Color rayColor(const Ray& r, const Hittable& world) {
    HitRecord rec;
    if (world.hit(r, Interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + Color(1, 1, 1));
    }

    vec3 unitDirection = unitVector(r.direction());
    double a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main()
{
    // Image ----------------------------------------------------------------------------
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;
    int imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    // World ----------------------------------------------------------------------------
    HittableList world;
    world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

    // Camera ---------------------------------------------------------------------------
    double focalLength = 1.0;
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
    point3 cameraCenter = point3(0, 0, 0);
    
    vec3 viewportU = vec3(viewportWidth, 0, 0);
    vec3 viewportV = vec3(0, -viewportHeight, 0);

    vec3 pixelDeltaU = viewportU / imageWidth;
    vec3 pixelDeltaV = viewportV / imageHeight;

    vec3 viewportUpperLeft = cameraCenter
        - vec3(0, 0, focalLength) - viewportU/2 - viewportV/2;

    point3 pixel00Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    // Rendering ------------------------------------------------------------------------
    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << " " << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            auto pixelCenter = pixel00Loc + (i * pixelDeltaU) + (j * pixelDeltaV);
            auto rayDirection = pixelCenter - cameraCenter;
            Ray r(cameraCenter, rayDirection);

            Color pixelColor = rayColor(r, world);
            writeColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                 \n";
}