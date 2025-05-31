#include "scenes/scene.h"
#include "all_includes.h"

int main() {
    hittable_list world;

    camera cam;
    //  main_scene(world, cam);
    //  checkered_spheres(world, cam);
    //  earth(world, cam);
    //  perlin_spheres(world, cam);
    quads(world, cam);
    cam.render(world);
}
