#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <memory>

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
//  Common Headers
#include "random_util.h"
#include "core/ray.h"
#include "math/color.h"
#include "math/vec3.h"
#include "interval.h"
#endif
