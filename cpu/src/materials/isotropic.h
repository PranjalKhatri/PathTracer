#ifndef ISOTROPIC_H
#define ISOTROPIC_H

#include "hittable/hittable.h"
#include "material.h"
#include "textures/solid_color.h"

class isotropic : public material {
   public:
    isotropic(const color& albedo) : tex(make_shared<solid_color>(albedo)) {}
    isotropic(shared_ptr<texture> tex) : tex(tex) {}
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,
                 ray& scattered) const override {
        scattered = ray(rec.hit_point, random_unit_vector(), r_in.time());
        attenuation = tex->value(rec.u, rec.v, rec.hit_point);
        return true;
    }

   private:
    shared_ptr<texture> tex;
};

#endif
