#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include "constants.h"
#include <memory>

//  C++ Std Usings
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

//  Utility Functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

//  Common Headers
#include "core/ray.h"
#include "math/color.h"
#include "math/vec3.h"
#include "interval.h"
#endif
