#ifndef RANDOM_UTIL_H
#define RANDOM_UTIL_H

#include <random>

using std::fabs;

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
//  Returns a random real in [min,max).
inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}
//  Returns a random integer in [min,max].
inline int random_int(int min, int max) {
    return int(random_double(min, max + 1));
}
#endif
