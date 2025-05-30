#ifndef COLOR_H
#define COLOR_H

#include "util/interval.h"
#include "vec3.h"
//(r,g,b): r,g,b E [0,1]
using color = vec3;

struct ColorConstants {
    static constexpr vec3 BLACK{0.0, 0.0, 0.0};
    static constexpr vec3 WHITE{1.0, 1.0, 1.0};
    static constexpr vec3 RED{1.0, 0.0, 0.0};
    static constexpr vec3 GREEN{0.0, 1.0, 0.0};
    static constexpr vec3 BLUE{0.0, 0.0, 1.0};
};
inline double linear_to_gamma(double linear_component) {
    if (linear_component > 0) return sqrt(linear_component);
    return 0.0;
}
inline void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    //  linear to gamma tranform for gamma 2
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);
    //  Translate the [0,1] component values to the byte range [0,255].
    static const interval intensity(0.000, 0.999);
    int rbyte = static_cast<int>(256 * intensity.clamp(r));
    int gbyte = static_cast<int>(256 * intensity.clamp(g));
    int bbyte = static_cast<int>(256 * intensity.clamp(b));
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif
