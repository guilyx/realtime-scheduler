#include "DeadlineMonotonic.h"

/**
 * @brief Construct a new Deadline Monotonic:: Deadline Monotonic object
 * 
 */
DeadlineMonotonic::DeadlineMonotonic() {}

/**
 * @brief Compute priority according to the DM policy
 * 
 * @param tasks 
 * @return std::map<const char*, Task> 
 */
std::map<const char*, Task> DeadlineMonotonic::prioritize(std::map<const char*, Task> tasks) {
    int max_priority = tasks.size();
    for (auto pair : tasks) {
        m_task_vector.push_back(pair.second);
    }
    std::sort(m_task_vector.begin(), m_task_vector.end(), deadlineMonotonicSorter);
    for (auto elem : m_task_vector) {
        (tasks.at(elem.name)).set_priority(max_priority);
        --max_priority;
    }

    return tasks;
}

/**
 * @brief Prioritized tasks structure getter
 * 
 * @return std::vector<Task> 
 */
std::vector<Task> DeadlineMonotonic::get_prioritized_tasks() const {
    return m_task_vector;
}

/**
 * @brief Reset priorities by clearing the structure
 * 
 */
void DeadlineMonotonic::reset_priorities()  {
    m_task_vector.clear();
}

bool DeadlineMonotonic::compute_sufficient_condition(int ntasks, double charge) {
    double condition = ntasks*(pow(2, 1.0/ntasks) - 1);
    if (charge != 0 && charge <= condition) {
        return true;
    } 
    return false;
}
