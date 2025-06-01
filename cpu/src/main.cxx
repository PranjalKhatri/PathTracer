#include "scenes/scene.h"
#include "all_includes.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <output_file>\n";
        return 1;
    }

    std::string lastArg(argv[1]);
    final_scene(800, 10000, 50, lastArg);

    return 0;
}
