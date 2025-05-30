#ifndef IMAGE_H
#define IMAGE_H

#include "texture.h"
#include "external/stb/rtw_stb_image.h"

class image_texture : public texture {
   public:
    image_texture(std::string filename) : m_image(filename.c_str()) {}
    //  If we have no texture data, then return solid cyan as a debugging
    //  aid.
    color value(double u, double v, const point3& p) const override {
        if (m_image.height() <= 0) return color(0, 1, 1);
        //  Clamp input texture coordinates to [0,1] x [1,0]
        u = interval(0, 1).clamp(u);
        v = 1.0 - interval(0, 1).clamp(v);    //  Flip V to image coordinates
        auto i = static_cast<int>(u * m_image.width());
        auto j = static_cast<int>(v * m_image.height());
        auto pixel = m_image.pixel_data(i, j);
        //  auto color_scale = 1.0 / 255.0;
        return color(color_scale * pixel[0], color_scale * pixel[1],
                     color_scale * pixel[2]);
    }

   private:
    rtw_image m_image;
    static constexpr double color_scale = 1.0 / 255.0;
};

#endif
