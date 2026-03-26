#include "RTWeekend.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"

int main() {
    HittableList world;

    world.add(std::make_shared<Sphere>(point3(0,0,-1), 0.5));
    world.add(std::make_shared<Sphere>(point3(0,-100.5,-1), 100));

    Camera cam;

    cam.aspectRatio     = 16.0 / 9.0;
    cam.imageWidth      = 400;
    cam.samplesPerPixel = 100;

    cam.render(world);
}