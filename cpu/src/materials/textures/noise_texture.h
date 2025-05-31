#ifndef NOISE_TEXTURE_H
#define NOISE_TEXTURE_H

#include "texture.h"
#include "math/noise/perlin.h"

class noise_texture : public texture {
   public:
    noise_texture() {}
    color value(double u, double v, const point3& p) const override {
        return color(1, 1, 1) * m_noise.noise(p);
    }

   private:
    perlin m_noise;
};

#endif
