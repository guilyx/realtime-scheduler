#ifndef RATE_MONOTONIC_H
#define RATE_MONOTONIC_H

#include <functional>
#include <cmath>
#include <set>
#include <map>
#include "Task.h"

class RateMonotonic {
    public:
        RateMonotonic();
        std::map<const char*, Task> prioritize(std::map<const char*, Task> tasks);
};

#endif //RATE_MONOTONIC_H