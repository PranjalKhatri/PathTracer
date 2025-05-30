#ifndef SPHERE_H
#define SPHERE_H

#include "util/rtweekend.h"
#include "hittable.h"

class sphere : public hittable {
   public:
    ///  static sphere
    sphere(const point3& center, double radius, shared_ptr<material> mat)
        : m_center1(center),
          m_radius(fmax(0, radius)),
          m_mat(mat),
          m_is_moving(false) {}
    //  Moving Sphere
    sphere(const point3& center1, const point3& center2, double radius,
           shared_ptr<material> mat)
        : m_center1(center1),
          m_radius(fmax(0, radius)),
          m_mat(mat),
          m_is_moving(true) {
        m_center_vec = center2 - center1;
    }
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        auto center = m_is_moving ? sphere_center(r.time()) : m_center1;
        vec3 oc = center - r.origin();
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
        vec3 outward_normal = (rec.hit_point - center) / m_radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat = m_mat;
        return true;
    }

   private:
    point3 m_center1;
    double m_radius;
    shared_ptr<material> m_mat;
    bool m_is_moving;
    vec3 m_center_vec;

    //  Linearly interpolate from center1 to center2 according to time,
    //  where t=0 yields center1, and t=1 yields center2.
    point3 sphere_center(double time) const {
        return m_center1 + time * m_center_vec;
    }
};
#endif
