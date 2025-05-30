#ifndef HITTABLE_H
#define HITTABLE_H

#include "util/rtweekend.h"

class material;

class hit_record {
   public:
    point3 hit_point;
    vec3 normal;    //  unit normal vector
    double t;
    bool front_face;
    shared_ptr<material> mat;    //  set by the object called by ray color

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        //  Sets the hit record normal vector.
        //  NOTE: the parameter `outward_normal` is assumed to have unit length.
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
   public:
    /*
     * @param r ray to consider
     * @param ray_tmin,ray_tmax range of the hit points to consider in time
     * @param rec hit record to store the hit object info like normal,t,hit
     * point
     * @return bool whether or not the ray hits anything in the specified time
     * interval
     */
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
    virtual ~hittable() = default;
};

#endif
