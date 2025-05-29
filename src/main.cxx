#include "util/rtweekend.h"

#include "core/camera.h"
#include "hittable/hittable.h"
#include "hittable/hittable_list.h"
#include "materials/lambertian.h"
#include "hittable/sphere.h"

int main() {
    hittable_list world;

    auto mat_lamb_green = make_shared<lambertian>(ColorConstants::GREEN);

    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5, mat_lamb_green));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, mat_lamb_green));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(world);
}
