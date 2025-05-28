#ifndef HITTABLE_H
#define HITTABLE_H

#include "core/ray.h"

class hit_record {
   public:
    point3 p;
    vec3 normal;
    double t;
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
    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax,
                     hit_record& rec) const = 0;
    virtual ~hittable() = default;
};

#endif
