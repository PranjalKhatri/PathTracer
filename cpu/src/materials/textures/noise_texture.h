#ifndef NOISE_TEXTURE_H
#define NOISE_TEXTURE_H

#include "texture.h"
#include "math/noise/perlin.h"

class noise_texture : public texture {
   public:
    noise_texture() : m_scale(1.0), m_turb(1) {}

    noise_texture(double scale, int turb = 1) : m_scale(scale), m_turb(turb) {}
    color value(double u, double v, const point3& p) const override {
        return ColorConstants::WHITE * m_noise.turb(p, m_turb);
        //  return color(1, 1, 1) * 0.5 * (1.0 + m_noise.noise(m_scale * p));
    }

   private:
    perlin m_noise;
    double m_scale;
    int m_turb;
};

#endif
