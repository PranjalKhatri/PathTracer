#ifndef CAMERA_H
#define CAMERA_H

#include "util/rtweekend.h"
#include "hittable/hittable.h"
#include "materials/material.h"

class camera {
   public:
    double aspect_ratio = 1.0;    //  Ratio of image width over height
    int image_width = 100;        //  Rendered image width in pixel count
    int samples_per_pixel =
        10;    //  Count of random samples per pixel used for anti-aliasing
    int max_depth = 10;    //  Maximum number of ray bounces into scene

    double vfov = 90;                     //  vertical view angle(field of view)
    point3 lookfrom = point3(0, 0, 0);    //  Point camera is looking from
    point3 lookat = point3(0, 0, -1);     //  Point camera is looking at
    vec3 vup = vec3(0, 1, 0);             //  Camera-relative "up" direction
    double defocus_angle = 0;    //  Variation angle of rays through each pixel
    double focus_dist =
        10;    //  Distance from camera lookfrom point to plane of perfect focus
   public:
    void render(const hittable& world) {
        initialize();

        std::cout << "P3\n"
                  << image_width << ' ' << m_image_height << "\n255\n";

        for (int j = 0; j < m_image_height; j++) {
            std::clog << "\rScanlines remaining: " << (m_image_height - j)
                      << ' ' << std::flush;

            for (int i = 0; i < image_width; i++) {
                color pixel_color{0, 0, 0};
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(i, j);
                    pixel_color +=
                        ray_color(r, max_depth,
                                  world);    //  average out later while writing
                }
                write_color(std::cout, m_pixel_samples_scale * pixel_color);
            }
        }
        std::cout.flush();
        std::clog << "\rDone.                 \n";
    }

   private:
    int m_image_height;    //  Rendered image height
    double
        m_pixel_samples_scale;    //  Color scale factor for a sum of pixel
                                  //  samples (avoid division multiple times )
    point3 m_center;              //  Camera center
    point3 m_pixel00_loc;         //  Location of pixel 0, 0
    vec3 m_pixel_delta_u;         //  Offset to pixel to the right
    vec3 m_pixel_delta_v;         //  Offset to pixel below
    //  u is camera right,v is camera up and w is opposite to look from
    vec3 u, v, w;             //  Camera frame basis vectors
    vec3 m_defocus_disk_u;    //  Defocus disk horizontal radius
    vec3 m_defocus_disk_v;    //  Defocus disk vertical radius
   private:
    void initialize() {
        m_image_height = static_cast<int>(image_width / aspect_ratio);
        m_image_height = (m_image_height < 1) ? 1 : m_image_height;

        m_pixel_samples_scale = 1.0 / samples_per_pixel;

        m_center = lookfrom;

        //  Determine viewport dimensions.
        //  auto focal_length = (lookfrom - lookat).length();
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta / 2);
        auto viewport_height = 2 * h * focus_dist;
        auto viewport_width =
            viewport_height * (double(image_width) / m_image_height);

        //  Calculate the u,v,w unit basis vectors for the camera coordinate
        //  frame.
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        //  Calculate the vectors across the horizontal and down the vertical
        //  viewport edges.
        vec3 viewport_u =
            viewport_width * u;    //  Vector across viewport horizontal edge
        vec3 viewport_v =
            viewport_height * -v;    //  Vector down viewport vertical edge

        //  Calculate the horizontal and vertical delta vectors from pixel to
        //  pixel.
        m_pixel_delta_u = viewport_u / image_width;
        m_pixel_delta_v = viewport_v / m_image_height;

        //  Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            m_center - (focus_dist * w) - viewport_u / 2 - viewport_v / 2;
        m_pixel00_loc =
            viewport_upper_left + 0.5 * (m_pixel_delta_u + m_pixel_delta_v);

        //  Calculate the camera defocus disk basis vectors.
        auto defocus_radius =
            focus_dist * tan(degrees_to_radians(defocus_angle / 2));
        m_defocus_disk_u = u * defocus_radius;
        m_defocus_disk_v = v * defocus_radius;
    }

    ///  @brief: Construct a camera ray originating from the defocus disk and
    ///  directed at a randomly
    //  sampled point around the pixel location i, j.
    ray get_ray(int i, int j) const {
        auto offset = sample_square();
        auto pixel_sample = m_pixel00_loc +
                            ((i + offset.x()) * m_pixel_delta_u) +
                            ((j + offset.y()) * m_pixel_delta_v);
        auto ray_origin = (defocus_angle <= 0) ? m_center
                                               : defocus_disk_sample();
        auto ray_direction = pixel_sample - ray_origin;
        auto ray_time = random_double();
        return ray(ray_origin, ray_direction, ray_time);
    }
    ///  @brief: Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5]
    ///  unit square
    vec3 sample_square() const {
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }
    //  Returns a random point in the unit (radius 0.5) disk centered at the
    //  origin.
    vec3 sample_disk(double radius = 1.0) const {
        return radius * random_in_unit_disk();
    }
    point3 defocus_disk_sample() const {
        //  Returns a random point in the camera defocus disk.
        auto p = random_in_unit_disk();
        return m_center + (p[0] * m_defocus_disk_u) + (p[1] * m_defocus_disk_v);
    }
    color ray_color(const ray& r, int depth, const hittable& world) const {
        //  exceeding the bounce limit
        if (depth <= 0) return ColorConstants::BLACK;
        hit_record rec;
        //  0.001 is to avoid shado acne
        if (world.hit(r, interval(0.001, infinity), rec)) {
            ray scattered;
            color attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_color(scattered, depth - 1, world);
            return ColorConstants::BLACK;
        }
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
};
#endif
