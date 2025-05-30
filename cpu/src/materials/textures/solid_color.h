#ifndef SOLID_COLOR_H
#define SOLID_COLOR_H

#include "texture.h"

class solid_color : public texture {
   public:
    solid_color(const color& albedo) : m_albedo(albedo) {}
    solid_color(double red, double green, double blue)
        : solid_color(color(red, green, blue)) {}
    color value(double u, double v, const point3& p) const override {
        return m_albedo;
    }

   private:
    color m_albedo;
};

#endif
