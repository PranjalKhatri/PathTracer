#ifndef NOISE_TEXTURE_H
#define NOISE_TEXTURE_H

#include "texture.h"
#include "math/noise/perlin.h"

class noise_texture : public texture {
   public:
    noise_texture() : m_scale(1.0) {}

    noise_texture(double scale) : m_scale(scale) {}
    color value(double u, double v, const point3& p) const override {
        return color(1, 1, 1) * 0.5 * (1.0 + m_noise.noise(m_scale * p));
    }

   private:
    perlin m_noise;
    double m_scale;
};

#endif
