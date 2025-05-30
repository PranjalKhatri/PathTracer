#ifndef METAL_H
#define METAL_H

#include "hittable/hittable.h"
#include "material.h"

class metal : public material {
   public:
    metal(const color& albedo, double fuzz)
        : m_albedo(albedo), m_fuzz(fuzz < 1 ? fuzz : 1) {}
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,
                 ray& scattered) const override {
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        reflected = unit_vector(reflected) + (m_fuzz * random_unit_vector());
        scattered = ray(rec.hit_point, reflected, r_in.time());
        attenuation = m_albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

   private:
    color m_albedo;
    double m_fuzz;
};

#endif
