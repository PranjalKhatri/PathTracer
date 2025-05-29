#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <memory>
#include <random>

#include "constants.h"

//  C++ Std Usings
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

//  Utility Functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}
//  Returns a random real in [0,1).
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
//  Returns a random real in [min,max).
inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}
//  Common Headers
#include "core/ray.h"
#include "math/color.h"
#include "math/vec3.h"
#include "interval.h"
#endif
