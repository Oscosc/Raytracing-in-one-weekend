#include "RTWeekend.h"

#include "Camera.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Material.h"
#include "Sphere.h"

int main() {
    HittableList world;

    // Ground sphere
    auto groundMaterial = std::make_shared<Lambertian>(Color(0.5, 0.1, 0.1));
    world.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, groundMaterial));

    // Random spheres
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto chooseMat = randomDouble();
            point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

            if((center - point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphereMaterial;

                if (chooseMat < 0.8) {
                    // diffuse
                    Color albedo = Color::random() * Color::random();
                    sphereMaterial = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                } else if (chooseMat < 0.95) {
                    // metal
                    Color albedo = Color::random(0.5, 1);
                    double fuzz = randomDouble(0, 0.5);
                    sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                } else {
                    // glass
                    sphereMaterial = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

    Camera cam;

    cam.aspectRatio     = 16.0 / 9.0;
    cam.imageWidth      = 1920;
    cam.samplesPerPixel = 500;
    cam.maxDepth        = 50;

    cam.vfov     = 20;
    cam.lookFrom = point3(13, 2, 3);
    cam.lookAt   = point3(0, 0, 0);
    cam.vup      = vec3(0, 1, 0);

    cam.defocusAngle = 0.6;
    cam.focusDist    = 10.0;

    cam.render(world);
}