#ifndef SPHERE_H
#define SPHERE_H

#include "util/rtweekend.h"
#include "hittable.h"

class sphere : public hittable {
   public:
    sphere(const point3& center, double radius, shared_ptr<material> mat)
        : m_center(center), m_radius(fmax(0, radius)), m_mat(mat) {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        vec3 oc = m_center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - m_radius * m_radius;
        auto discriminant = h * h - a * c;

        if (discriminant < 0) return false;

        auto sqrtd = sqrt(discriminant);
        //  Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;

        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root)) return false;
        }
        rec.t = root;
        rec.hit_point = r.at(rec.t);
        vec3 outward_normal = (rec.hit_point - m_center) / m_radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = m_mat;
        return true;
    }

   private:
    point3 m_center;
    double m_radius;
    shared_ptr<material> m_mat;
};
#endif
