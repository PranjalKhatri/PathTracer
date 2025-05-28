#ifndef CAMERA_H
#define CAMERA_H

#include "util/rtweekend.h"
#include "hittable/hittable.h"

class camera {
   public:
    double aspect_ratio = 1.0;    //  Ratio of image width over height
    int image_width = 100;        //  Rendered image width in pixel count

   public:
    void render(const hittable& world) {
        initialize();

        std::cout << "P3\n"
                  << image_width << ' ' << m_image_height << "\n255\n";

        for (int j = 0; j < m_image_height; j++) {
            std::clog << "\rScanlines remaining: " << (m_image_height - j)
                      << ' ' << std::flush;

            for (int i = 0; i < image_width; i++) {
                auto pixel_center = m_pixel00_loc + (i * m_pixel_delta_u) +
                                    (j * m_pixel_delta_v);
                auto ray_direction = pixel_center - m_center;
                ray r(m_center, ray_direction);
                color pixel_color = ray_color(r, world);
                write_color(std::cout, pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";
    }

   private:
    int m_image_height;      //  Rendered image height
    point3 m_center;         //  Camera center
    point3 m_pixel00_loc;    //  Location of pixel 0, 0
    vec3 m_pixel_delta_u;    //  Offset to pixel to the right
    vec3 m_pixel_delta_v;    //  Offset to pixel below

   private:
    void initialize() {
        m_image_height = int(image_width / aspect_ratio);
        m_image_height = (m_image_height < 1) ? 1 : m_image_height;
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
