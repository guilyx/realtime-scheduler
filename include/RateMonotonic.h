#ifndef RATE_MONOTONIC_H
#define RATE_MONOTONIC_H

#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include "Helpers.h"

class RateMonotonic {
    public:
        RateMonotonic();
        std::map<const char*, Task> prioritize(std::map<const char*, Task> tasks);
        std::vector<Task> get_prioritized_tasks() const;
        void reset_priorities();

    private:
        std::vector<Task> m_task_vector;
};

#endif //RATE_MONOTONIC_H