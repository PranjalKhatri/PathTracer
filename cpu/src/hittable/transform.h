#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "hittable.h"

///@brief: create a new object of traslate type, the newly created object has
///  its bounding box at the specified position(adding offset) and checks the
///  hit ray using hit method of original object
class translate : public hittable {
   public:
    //@brief: initialized the bbox of this object to offset+bbox(object)
    translate(shared_ptr<hittable> object, const vec3& offset)
        : m_object(object), m_offset(offset) {
        m_bbox = object->bounding_box() + offset;
    }
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        //  Move the ray backwards by the offset
        ray offset_r(r.origin() - m_offset, r.direction(), r.time());
        //  Determine whether an intersection exists along the offset ray (and
        //  if so, where)
        if (!m_object->hit(offset_r, ray_t, rec)) return false;
        //  Move the intersection point forwards by the offset
        rec.hit_point += m_offset;
        return true;
    }

    aabb bounding_box() const override { return m_bbox; }

   private:
    shared_ptr<hittable> m_object;
    vec3 m_offset;
    aabb m_bbox;
};

///------------------------ROTATION-------------------------
///@brief: helper class for rotation around y axis
class rotate_y : public hittable {
   public:
    //  @brief: rotates [object] around [y]-axis by angle in degrees
    rotate_y(shared_ptr<hittable> object, double angle) : object(object) {
        auto radians = degrees_to_radians(angle);
        sin_theta = sin(radians);
        cos_theta = cos(radians);
        bbox = object->bounding_box();
        point3 min(infinity, infinity, infinity);
        point3 max(-infinity, -infinity, -infinity);
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    auto x = i * bbox.x.max + (1 - i) * bbox.x.min;
                    auto y = j * bbox.y.max + (1 - j) * bbox.y.min;
                    auto z = k * bbox.z.max + (1 - k) * bbox.z.min;
                    auto newx = cos_theta * x + sin_theta * z;
                    auto newz = -sin_theta * x + cos_theta * z;
                    vec3 tester(newx, y, newz);
                    for (int c = 0; c < 3; c++) {
                        min[c] = fmin(min[c], tester[c]);
                        max[c] = fmax(max[c], tester[c]);
                    }
                }
            }
        }
        bbox = aabb(min, max);
    }
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        //  Change the ray from world space to object space
        auto origin = r.origin();
        auto direction = r.direction();
        //  rotating by theta
        origin[0] = cos_theta * r.origin()[0] - sin_theta * r.origin()[2];
        origin[2] = sin_theta * r.origin()[0] + cos_theta * r.origin()[2];
        direction[0] =
            cos_theta * r.direction()[0] - sin_theta * r.direction()[2];
        direction[2] =
            sin_theta * r.direction()[0] + cos_theta * r.direction()[2];
        ray rotated_r(origin, direction, r.time());
        //  Determine whether an intersection exists in object space (and if so,
        //  where)
        if (!object->hit(rotated_r, ray_t, rec)) return false;
        //  Change the intersection point from object space to world space
        //  rotating by -theta
        auto hit_point = rec.hit_point;
        hit_point[0] =
            cos_theta * rec.hit_point[0] + sin_theta * rec.hit_point[2];
        hit_point[2] =
            -sin_theta * rec.hit_point[0] + cos_theta * rec.hit_point[2];
        //  Change the normal from object space to world space
        auto normal = rec.normal;
        normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
        normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];
        rec.hit_point = hit_point;
        rec.normal = normal;
        return true;
    }
    aabb bounding_box() const override { return bbox; }

   private:
    shared_ptr<hittable> object;
    double sin_theta;
    double cos_theta;
    aabb bbox;
};
#endif
