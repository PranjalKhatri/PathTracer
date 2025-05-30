#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "hittable/hittable.h"
#include "material.h"

#include "textures/texture.h"
#include "materials/textures/solid_color.h"

class lambertian : public material {
   public:
    lambertian(const color& albedo) : m_tex(make_shared<solid_color>(albedo)) {}
    lambertian(shared_ptr<texture> tex) : m_tex(tex) {}
    //  TODO: test with reflectance R
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,
                 ray& scattered) const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        //  Catch degenerate scatter direction
        if (scatter_direction.near_zero()) scatter_direction = rec.normal;
        scattered = ray(rec.hit_point, scatter_direction, r_in.time());
        attenuation = m_tex->value(rec.u, rec.v, rec.hit_point);
        return true;
    }

   private:
    //  color m_albedo;
    shared_ptr<texture> m_tex;
};

#endif
