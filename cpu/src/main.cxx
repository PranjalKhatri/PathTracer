#include "scenes/scene.h"

int main() {
    hittable_list world;

    camera cam;
    //  main_scene(world, cam);
    //  checkered_spheres(world, cam);
    earth(world, cam);
    cam.render(world);
}
