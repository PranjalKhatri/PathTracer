#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "hittable/hittable.h"
#include "material.h"

class lambertian : public material {
   public:
    lambertian(const color& albedo) : m_albedo(albedo) {}
    //  TODO: test with reflectance R
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,
                 ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        //  Catch degenerate scatter direction
        if (scatter_direction.near_zero()) scatter_direction = rec.normal;
        scattered = ray(rec.hit_point, scatter_direction, r_in.time());
        attenuation = m_albedo;
        return true;
    }

   private:
    color m_albedo;
};

#endif
