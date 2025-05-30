#ifndef AABB_H
#define AABB_H

#include "util/rtweekend.h"

class aabb {
   public:
    interval x, y, z;

   public:
    //  The default AABB is empty, since intervals are empty by default.
    aabb() {}
    aabb(const interval& x, const interval& y, const interval& z)
        : x(x), y(y), z(z) {}

    ///  takes lower left and upper right corner of cuboid
    aabb(const point3& a, const point3& b) {
        x = (a[0] <= b[0]) ? interval(a[0], b[0]) : interval(b[0], a[0]);
        y = (a[1] <= b[1]) ? interval(a[1], b[1]) : interval(b[1], a[1]);
        z = (a[2] <= b[2]) ? interval(a[2], b[2]) : interval(b[2], a[2]);
    }
    //  creates a new bounding box tightly enclosing the given two bounding
    //  boxed
    aabb(const aabb& box0, const aabb& box1) {
        //  create tight interval for each axis
        x = interval(box0.x, box1.x);
        y = interval(box0.y, box1.y);
        z = interval(box0.z, box1.z);
    }

    ///  0: x, 1: y, 2: z
    const interval& axis_interval(int n) const {
        if (n == 1) return y;
        if (n == 2) return z;
        return x;
    }
    bool hit(const ray& r, interval ray_t) const {
        const point3& ray_orig = r.origin();
        const vec3& ray_dir = r.direction();
        for (int axis = 0; axis < 3; axis++) {
            const interval& ax = axis_interval(axis);
            const double adinv = 1.0 / ray_dir[axis];
            auto t0 = (ax.min - ray_orig[axis]) * adinv;
            auto t1 = (ax.max - ray_orig[axis]) * adinv;
            if (t0 < t1) {
                if (t0 > ray_t.min) ray_t.min = t0;
                if (t1 < ray_t.max) ray_t.max = t1;
            } else {
                if (t1 > ray_t.min) ray_t.min = t1;
                if (t0 < ray_t.max) ray_t.max = t0;
            }
            if (ray_t.max <= ray_t.min) return false;
        }
        return true;
    }
    //  Returns the index of the longest axis of the bounding box.
    int longest_axis() const {
        if (x.size() > y.size())
            return x.size() > z.size() ? 0 : 2;
        else
            return y.size() > z.size() ? 1 : 2;
    }
    static const aabb empty, universe;
};
inline const aabb aabb::empty =
    aabb(interval::empty, interval::empty, interval::empty);
inline const aabb aabb::universe =
    aabb(interval::universe, interval::universe, interval::universe);
#endif
