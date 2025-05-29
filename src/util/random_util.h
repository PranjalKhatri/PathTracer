#ifndef RANDOM_UTIL_H
#define RANDOM_UTIL_H

#include <random>

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
//  Returns a random real in [min,max).
inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}
#endif
