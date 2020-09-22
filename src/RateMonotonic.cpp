#include "RateMonotonic.h"

RateMonotonic::RateMonotonic() {}

std::map<const char*, Task> RateMonotonic::prioritize(std::map<const char*, Task> tasks) {
    int max_priority = tasks.size();
    for (auto pair : tasks) {
        m_task_vector.push_back(pair.second);
    }
    std::sort(m_task_vector.begin(), m_task_vector.end(), rateMonotonicSorter);
    for (auto elem : m_task_vector) {
        (tasks.at(elem.name)).set_priority(max_priority);
        --max_priority;
    }

    return tasks;
}

std::vector<Task> RateMonotonic::get_prioritized_tasks() const {
    return m_task_vector;
}

void RateMonotonic::reset_priorities()  {
    m_task_vector.clear();
}
