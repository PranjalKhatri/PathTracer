#include "scenes/scene.h"

int main() {
    hittable_list world;

    camera cam;
    main_scene(world, cam);
    cam.render(world);
}
