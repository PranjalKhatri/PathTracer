#ifndef QUAD_H
#define QUAD_H

#include "hittable/hittable_list.h"
#include "util/rtweekend.h"
#include "hittable.h"

///@brief: prallelograms
class quad : public hittable {
   public:
    ///@brief: takes the starting point3, and the vector to its adjacent points
    quad(const point3& Q, const vec3& u, const vec3& v,
         shared_ptr<material> mat)
        : Q(Q), u(u), v(v), mat(mat) {
        auto n = cross(u, v);
        normal = unit_vector(n);
        w = n / dot(n, n);
        D = dot(normal, Q);

        set_bounding_box();
    }
    //  Compute the bounding box of all four vertices.
    virtual void set_bounding_box() {
        auto bbox_diagonal1 = aabb(Q, Q + u + v);
        auto bbox_diagonal2 = aabb(Q + u, Q + v);
        bbox = aabb(bbox_diagonal1, bbox_diagonal2);
    }
    aabb bounding_box() const override { return bbox; }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        auto denom = dot(normal, r.direction());
        //  No hit if the ray is parallel to the plane.
        if (fabs(denom) < 1e-8) return false;
        //  Return false if the hit point parameter t is outside the ray
        //  interval.
        auto t = (D - dot(normal, r.origin())) / denom;
        if (!ray_t.contains(t)) return false;
        //  Determine the hit point lies within the planar shape using its plane
        //  coordinates.
        auto intersection = r.at(t);
        vec3 planar_hitpt_vector = intersection - Q;
        auto alpha = dot(w, cross(planar_hitpt_vector, v));
        auto beta = dot(w, cross(u, planar_hitpt_vector));
        if (!is_interior(alpha, beta, rec)) return false;
        //  Ray hits the 2D shape; set the rest of the hit record and return
        //  true
        rec.t = t;
        rec.hit_point = intersection;
        rec.mat = mat;
        rec.set_face_normal(r, normal);
        return true;
    }
    //  Given the hit point in plane coordinates, return false if it is
    //  outside the primitive, otherwise set the hit record UV coordinates
    //  and return true.
    virtual bool is_interior(double a, double b, hit_record& rec) const {
        interval unit_interval = interval(0, 1);
        if (!unit_interval.contains(a) || !unit_interval.contains(b))
            return false;
        rec.u = a;
        rec.v = b;
        return true;
    }

   private:
    point3 Q;                    //  one vertex of quad
    vec3 u, v;                   //  vector to adjacent vertices of Q
    vec3 w;                      //  n/(n.(uXv))
    shared_ptr<material> mat;    //  materail
    aabb bbox;
    vec3 normal;    //  normal to quad (uXv)
    double D;       //  v.n=D
};

//  Returns the 3D box (six sides) that contains the two opposite vertices a
//  & b.
inline shared_ptr<hittable_list> box(const point3& a, const point3& b,
                                     shared_ptr<material> mat) {
    auto sides = make_shared<hittable_list>();
    //  Construct the two opposite vertices with the minimum and maximum
    //  coordinates.
    auto min =
        point3(fmin(a.x(), b.x()), fmin(a.y(), b.y()), fmin(a.z(), b.z()));
    auto max =
        point3(fmax(a.x(), b.x()), fmax(a.y(), b.y()), fmax(a.z(), b.z()));
    auto dx = vec3(max.x() - min.x(), 0, 0);
    auto dy = vec3(0, max.y() - min.y(), 0);
    auto dz = vec3(0, 0, max.z() - min.z());
    sides->add(make_shared<quad>(point3(min.x(), min.y(), max.z()), dx, dy,
                                 mat));    //  front
    sides->add(make_shared<quad>(point3(max.x(), min.y(), max.z()), -dz, dy,
                                 mat));    //  right
    sides->add(make_shared<quad>(point3(max.x(), min.y(), min.z()), -dx, dy,
                                 mat));    //  back
    sides->add(make_shared<quad>(point3(min.x(), min.y(), min.z()), dz, dy,
                                 mat));    //  left
    sides->add(make_shared<quad>(point3(min.x(), max.y(), max.z()), dx, -dz,
                                 mat));    //  top
    sides->add(make_shared<quad>(point3(min.x(), min.y(), min.z()), dx, dz,
                                 mat));    //  bottom
    return sides;
}
#endif
//  TODO: Add triagles,rings,disks...
