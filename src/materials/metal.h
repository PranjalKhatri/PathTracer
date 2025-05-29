#ifndef METAL_H
#define METAL_H

#include "hittable/hittable.h"
#include "material.h"

class metal : public material {
   public:
    metal(const color& albedo) : m_albedo(albedo) {}
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,
                 ray& scattered)const override {
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        scattered = ray(rec.hit_point, reflected);
        attenuation = m_albedo;
        return true;
    }

   private:
    color m_albedo;
};

#endif
