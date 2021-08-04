#pragma once

#include <cstdlib>
#include <random>
#include <memory>
#include <limits>
#include <cmath>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants:

const double infinity = std::numeric_limits<float>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions:

inline float degrees_to_radians(float degrees) {
    return degrees * pi / 180.0;
}

inline float random_float() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline float random_float(float min, float max) {
    // Returns a random real in [min,max).
    return min + (max - min) * random_float();
}

inline float clamp(float x, float min, double max) {
    if (x < min) { return min; }
    if (x > max) { return max; }
    return x;
}
