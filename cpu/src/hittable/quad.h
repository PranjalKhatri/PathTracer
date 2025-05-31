#ifndef QUAD_H
#define QUAD_H

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
        return false;    //  To be implemented
    }

   private:
    point3 Q;                    //  one vertex of quad
    vec3 u, v;                   //  vector to adjacent vertices of Q
    shared_ptr<material> mat;    //  materail
    aabb bbox;
    vec3 normal;    //  normal to quad (uXv)
    double D;       //  v.n=D
};
#endif
