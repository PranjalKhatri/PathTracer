#ifndef MATERIAL_H
#define MATERIAL_H

#include "util/rtweekend.h"

class hit_record;

class material {
   public:
    virtual ~material() = default;
    virtual bool scatter(const ray& r_in, const hit_record& rec,
                         color& attenuation, ray& scattered) const {
        return false;
    }
    virtual color emitted(double u, double v, const point3& p) const {
        return ColorConstants::BLACK;
    }
};
#endif
