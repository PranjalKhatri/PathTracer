#ifndef CAMERA_H
#define CAMERA_H

#include "util/rtweekend.h"
#include "hittable/hittable.h"

class camera {
   public:
    double aspect_ratio = 1.0;    //  Ratio of image width over height
    int image_width = 100;        //  Rendered image width in pixel count
    int samples_per_pixel =
        10;    //  Count of random samples per pixel used for anti-aliasing

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
                    pixel_color += ray_color(
                        r, world);    //  average out later while writing
                }
                write_color(std::cout, m_pixel_samples_scale * pixel_color);
            }
        }

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

   private:
    void initialize() {
        m_image_height = static_cast<int>(image_width / aspect_ratio);
        m_image_height = (m_image_height < 1) ? 1 : m_image_height;

        m_pixel_samples_scale = 1.0 / samples_per_pixel;

        m_center = point3(0, 0, 0);

        //  Determine viewport dimensions.
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width =
            viewport_height * (double(image_width) / m_image_height);

        //  Calculate the vectors across the horizontal and down the vertical
        //  viewport edges.
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        //  Calculate the horizontal and vertical delta vectors from pixel to
        //  pixel.
        m_pixel_delta_u = viewport_u / image_width;
        m_pixel_delta_v = viewport_v / m_image_height;

        //  Calculate the location of the upper left pixel.
        auto viewport_upper_left = m_center - vec3(0, 0, focal_length) -
                                   viewport_u / 2 - viewport_v / 2;

        m_pixel00_loc =
            viewport_upper_left + 0.5 * (m_pixel_delta_u + m_pixel_delta_v);
    }

    ///  @brief: Construct a camera ray originating from the origin and directed
    ///  at randomly sampled point around the pixel location i, j.
    ray get_ray(int i, int j) const {
        auto offset = sample_disk();
        auto pixel_sample = m_pixel00_loc +
                            ((i + offset.x()) * m_pixel_delta_u) +
                            ((j + offset.y()) * m_pixel_delta_v);
        auto ray_origin = m_center;
        auto ray_direction = pixel_sample - ray_origin;
        return ray(ray_origin, ray_direction);
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
    color ray_color(const ray& r, const hittable& world) const {
        hit_record rec;
        if (world.hit(r, interval(0, infinity), rec)) {
            return 0.5 * (rec.normal + color(1, 1, 1));
        }
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
};
#endif
