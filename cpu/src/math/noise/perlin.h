#ifndef PERLIN_H
#define PERLIN_H

#include "util/rtweekend.h"

///  pseudo perlin noice
///@source : https://www.youtube.com/watch?v=kCIaHqb60Cw
class perlin {
   public:
    perlin() {
        randfloat = new double[s_point_count];
        for (int i = 0; i < s_point_count; i++) {
            randfloat[i] = random_double();
        }
        perm_x = perlin_generate_perm();
        perm_y = perlin_generate_perm();
        perm_z = perlin_generate_perm();
    }
    ~perlin() {
        delete[] randfloat;
        delete[] perm_x;
        delete[] perm_y;
        delete[] perm_z;
    }
    double noise(const point3& p) const {
        auto u = p.x() - floor(p.x());
        auto v = p.y() - floor(p.y());
        auto w = p.z() - floor(p.z());

        //  hermite smoothing to get rid of mach artifacts
        u = u * u * (3 - 2 * u);
        v = v * v * (3 - 2 * v);
        w = w * w * (3 - 2 * w);

        auto i = int(floor(p.x()));
        auto j = int(floor(p.y()));
        auto k = int(floor(p.z()));
        double c[2][2][2];
        for (int di = 0; di < 2; di++)
            for (int dj = 0; dj < 2; dj++)
                for (int dk = 0; dk < 2; dk++)
                    c[di][dj][dk] = randfloat[perm_x[(i + di) & 255] ^
                                              perm_y[(j + dj) & 255] ^
                                              perm_z[(k + dk) & 255]];
        return trilinear_interp(c, u, v, w);
    }

   private:
    static const int s_point_count = 256;
    double* randfloat;
    int* perm_x;
    int* perm_y;
    int* perm_z;
    static int* perlin_generate_perm() {
        auto p = new int[s_point_count];
        for (int i = 0; i < s_point_count; i++) p[i] = i;
        permute(p, s_point_count);
        return p;
    }
    static void permute(int* p, int n) {
        for (int i = n - 1; i > 0; i--) {
            int target = random_int(0, i);
            int tmp = p[i];
            p[i] = p[target];
            p[target] = tmp;
        }
    }
    static double trilinear_interp(double c[2][2][2], double u, double v,
                                   double w) {
        auto accum = 0.0;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++)
                    accum += (i * u + (1 - i) * (1 - u)) *
                             (j * v + (1 - j) * (1 - v)) *
                             (k * w + (1 - k) * (1 - w)) * c[i][j][k];
        return accum;
    }
};
#endif
