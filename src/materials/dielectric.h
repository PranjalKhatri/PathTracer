#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "hittable/hittable.h"
#include "material.h"

class dielectric : public material {
   public:
    dielectric(double refraction_index)
        : m_refraction_index(refraction_index) {}
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,
                 ray& scattered) const override {
        attenuation = color(1.0, 1.0, 1.0);
        double ri = rec.front_face ? (1.0 / m_refraction_index)
                                   : m_refraction_index;
        vec3 unit_direction = unit_vector(r_in.direction());
        vec3 refracted = refract(unit_direction, rec.normal, ri);
        scattered = ray(rec.hit_point, refracted);
        return true;
    }

   private:
    //  Refractive index in vacuum or air, or the ratio of the material's
    //  refractive index over the refractive index of the enclosing media
    double m_refraction_index;
};

#endif
