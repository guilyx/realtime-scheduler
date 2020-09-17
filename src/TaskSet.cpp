#include "TaskSet.h"

TaskSet::TaskSet() {}

void TaskSet::register_task(Task tsk) {
    if (m_tasks.find(tsk.name) == m_tasks.end()) {
        // Task not registered, free to go
        m_tasks.insert(std::pair<const char*, Task>(tsk.name, tsk));
        ++m_number_of_tasks;
        printf("Task <%s> has been registered.\n", tsk.name);
    } else {
        // Task already registered
        std::cout << "Failed to register task: id already registered." << std::endl;
    }
}

void TaskSet::remove_task(const char* task_id) {
    if (m_tasks.find(task_id) == m_tasks.end()) {
        // Task not registered, pass
        printf("Task <%s> has not been registered, failed to remove.\n", task_id);
    } else {
        // Task already registered
        m_tasks.erase(task_id);
        --m_number_of_tasks;
        printf("Task <%s> has been removed\n", task_id);
    }   
}

std::map<const char*, Task> TaskSet::get_task_set() const {
    return m_tasks;
}

int TaskSet::get_number_of_tasks() const {
    return m_number_of_tasks;
}

void TaskSet::print_task_set() {
    printf("==Task Set==\n");
    for (auto it = m_tasks.cbegin(); it != m_tasks.cend(); ++it) {
        (it->second).print_task();
    }
    printf("============\n");
}

void TaskSet::schedule(int scheduler) {
    std::cout << "Scheduling the tasks..." << std::endl;
    bool ok;
    switch(scheduler) {
        case RATE_MONOTONIC:
            ok = this->compute_sufficient_condition(scheduler);
            if (ok) {
                this->compute_priorities(scheduler);
                std::cout << "Priorities of the task set have been computed successfully." << std::endl;
            } else {
                std::cout << "The current Task Set is not schedulable by RMS." << std::endl;
            }
            break;
        case DEADLINE_MONOTONIC:
            std::cout << "Scheduler not supported yet" << std::endl;
            break;
        case EARLIEST_DEADLINE_FIRST:
            std::cout << "Scheduler not supported yet" << std::endl;
            break;
        default:
            std::cout << "Scheduler not supported yet" << std::endl;
            break;
    }
}

void TaskSet::compute_priorities(int scheduler) {

    if (scheduler == RATE_MONOTONIC) {
        RateMonotonic rm = RateMonotonic();
        m_tasks = rm.prioritize(m_tasks);
    } else if (scheduler == DEADLINE_MONOTONIC) {
        std::cout << "Scheduler not supported yet" << std::endl;
    } else {
        std::cout << "Scheduler not supported yet" << std::endl;
    }
}

bool TaskSet::compute_sufficient_condition(int scheduler) {
    double condition;
    double processor_charge = 0;
    for (auto it = m_tasks.cbegin(); it != m_tasks.cend(); ++it) {
        processor_charge += (it->second).get_utilization();
    }
    switch(scheduler) {
        case RATE_MONOTONIC:
            condition = m_number_of_tasks*(pow(2, 1.0/m_number_of_tasks) - 1);
            if (processor_charge != 0 && processor_charge <= condition) {
                return true;
            } else {
                return false;
            }
        case DEADLINE_MONOTONIC:
            std::cout << "Scheduler not supported yet" << std::endl;
            return false;
        case EARLIEST_DEADLINE_FIRST:
            std::cout << "Scheduler not supported yet" << std::endl;
            return false;
        default:
            std::cout << "Scheduler not supported yet" << std::endl;
            return false;
    }
}
