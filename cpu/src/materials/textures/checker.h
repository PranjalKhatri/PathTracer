#ifndef CHECKER_H
#define CHECKER_H

#include "texture.h"
#include "materials/textures/solid_color.h"

class checker_texture : public texture {
   public:
    ///  @brief: takes the scale of the checker texture and the texture to
    ///  display at even /odd positions( floor(x)+floor(y)+floor(z)) parity is
    ///  used
    checker_texture(double scale, shared_ptr<texture> even,
                    shared_ptr<texture> odd)
        : m_inv_scale(1.0 / scale), m_even(even), m_odd(odd) {}

    //@brief: used color to create solid textures
    checker_texture(double scale, const color& c1, const color& c2)
        : m_inv_scale(1.0 / scale),
          m_even(make_shared<solid_color>(c1)),
          m_odd(make_shared<solid_color>(c2)) {}

    color value(double u, double v, const point3& p) const override {
        auto xInteger = static_cast<int>(std::floor(m_inv_scale * p.x()));
        auto yInteger = static_cast<int>(std::floor(m_inv_scale * p.y()));
        auto zInteger = static_cast<int>(std::floor(m_inv_scale * p.z()));
        bool isEven = (xInteger + yInteger + zInteger) % 2 == 0;
        return isEven ? m_even->value(u, v, p) : m_odd->value(u, v, p);
    }

   private:
    double m_inv_scale;
    shared_ptr<texture> m_even;
    shared_ptr<texture> m_odd;
};

#endif
