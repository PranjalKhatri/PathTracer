#ifndef INTERVAL_H
#define INTERVAL_H

#include "constants.h"

class interval {
   public:
    double min, max;

   public:
    interval()
        : min(+infinity), max(-infinity) {}    //  Default interval is empty
    interval(double min, double max) : min(min), max(max) {}
    double size() const { return max - min; }
    bool contains(double x) const { return min <= x && x <= max; }
    bool surrounds(double x) const { return min < x && x < max; }
    double clamp(double x) const {
        if (x < min) x = min;
        if (x > max) x = max;
        return x;
    }
    ///@brief : expands interval by delta/2 in both directions
    interval expand(double delta) const {
        auto padding = delta / 2;
        return interval(min - padding, max + padding);
    }
    static const interval empty, universe;
};
inline const interval interval::empty = interval(+infinity, -infinity);
inline const interval interval::universe = interval(-infinity, +infinity);
#endif
