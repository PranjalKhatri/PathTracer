#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H

#include "hittable/hittable.h"
#include "materials/isotropic.h"
#include "materials/material.h"
#include "materials/textures/texture.h"

class constant_medium : public hittable {
   public:
    constant_medium(shared_ptr<hittable> boundary, double density,
                    shared_ptr<texture> tex)
        : boundary(boundary),
          neg_inv_density(-1 / density),
          phase_function(make_shared<isotropic>(tex)) {}
    constant_medium(shared_ptr<hittable> boundary, double density,
                    const color& albedo)
        : boundary(boundary),
          neg_inv_density(-1 / density),
          phase_function(make_shared<isotropic>(albedo)) {}
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        //  Print occasional samples when debugging. To enable, set enableDebug
        //  true.
        const bool enableDebug = false;
        const bool debugging = enableDebug && random_double() < 0.00001;

        hit_record rec1, rec2;
        if (!boundary->hit(r, interval::universe, rec1)) return false;
        if (!boundary->hit(r, interval(rec1.t + 0.0001, infinity), rec2))
            return false;

        if (debugging)
            std::clog << "\nt_min=" << rec1.t << ", t_max=" << rec2.t << '\n';

        if (rec1.t < ray_t.min) rec1.t = ray_t.min;
        if (rec2.t > ray_t.max) rec2.t = ray_t.max;

        if (rec1.t >= rec2.t) return false;
        if (rec1.t < 0) rec1.t = 0;

        auto ray_length = r.direction().length();
        auto distance_inside_boundary = (rec2.t - rec1.t) * ray_length;
        auto hit_distance = neg_inv_density * log(random_double());

        if (hit_distance > distance_inside_boundary) return false;
        rec.t = rec1.t + hit_distance / ray_length;
        rec.hit_point = r.at(rec.t);
        if (debugging) {
            std::clog << "hit_distance = " << hit_distance << '\n'
                      << "rec.t = " << rec.t << '\n'
                      << "rec.p = " << rec.hit_point << '\n';
        }
        rec.normal = vec3(1, 0, 0);    //  arbitrary
        rec.front_face = true;         //  also arbitrary
        rec.mat = phase_function;
        return true;
    }
    aabb bounding_box() const override { return boundary->bounding_box(); }

   private:
    shared_ptr<hittable> boundary;
    double neg_inv_density;
    shared_ptr<material> phase_function;
};
#endif
