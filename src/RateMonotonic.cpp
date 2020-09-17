#include "RateMonotonic.h"

RateMonotonic::RateMonotonic() {}

std::map<const char*, Task> RateMonotonic::prioritize(std::map<const char*, Task> tasks) {
    int max_priority = tasks.size();
    typedef std::function<bool(std::pair<const char*, Task>, std::pair<const char*, Task>)> Comparator;
    Comparator compFunctor = [](std::pair<const char*, Task> tsk1, std::pair<const char*, Task> tsk2) {
        return tsk1.second.get_period() < tsk2.second.get_period();
    };

    std::set<std::pair<const char*, Task>, Comparator> task_set(tasks.begin(), tasks.end(), compFunctor);
    for (auto it = task_set.cbegin(); it != task_set.cend(); it++) {
        (tasks.at(it->second.name)).set_priority(max_priority);
        --max_priority;
    }

    return tasks;
}