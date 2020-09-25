#include "TaskSet.h"

TaskSet::TaskSet() {}

void TaskSet::register_task(Task tsk) {
    if (m_tasks.find(tsk.name) == m_tasks.end()) {
        // Task not registered, free to go
        m_tasks.insert(std::pair<const char*, Task>(tsk.name, tsk));
        ++m_number_of_tasks;
        this->compute_hyper_period();
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
        this->compute_hyper_period();
        printf("Task <%s> has been removed\n", task_id);
    }   
}

void TaskSet::compute_hyper_period() {
    int hyper_periods[m_number_of_tasks];
    int i = 0;
    for (auto const& [key, val] : m_tasks) {
        hyper_periods[i] = val.get_period();
        ++i;
    }
    m_hyper_period = findlcm(hyper_periods);
    std::vector<const char*> tempVec(m_hyper_period, "");
    m_time_table = tempVec;
}

std::map<const char*, Task> TaskSet::get_task_set() const {
    return m_tasks;
}

int TaskSet::get_number_of_tasks() const {
    return m_number_of_tasks;
}

void TaskSet::print_task_set() {
    printf("==Task Set==\n");
    printf("hyperperiod = %d\n", m_hyper_period);
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
    this->compute_time_table();
    std::cout << "Schedule successfully computed." << std::endl;
}

std::vector<const char*> TaskSet::get_time_table() const {
    return m_time_table;
}

void TaskSet::compute_time_table() {
    for (int tsk=0; tsk<m_priority_vector.size(); ++tsk) {
        std::vector<int> activations_rank;
        std::vector<int> deactivation_rank;
        for (int p=0; p<m_hyper_period; ++p) {
            int period = p*m_priority_vector[tsk].get_period() + m_priority_vector[tsk].get_offset();
            int deadline = p*m_priority_vector[tsk].get_deadline() + m_priority_vector[tsk].get_offset();
            if (period > m_hyper_period) {
                break;
            }
            activations_rank.push_back(period);
            deactivation_rank.push_back(deadline);
        }
        for (auto elem: activations_rank) {
            for (int j=0; j<m_priority_vector[tsk].get_computation(); ++j) {
                while (m_time_table[elem+j] != "") elem++;
                if (elem + j > m_hyper_period) {
                    break;
                }
                m_time_table[elem + j] = m_priority_vector[tsk].name;
            }
        }
    }
}

void TaskSet::compute_priorities(int scheduler) {
    if (scheduler == RATE_MONOTONIC) {
        RateMonotonic rm = RateMonotonic();
        m_tasks = rm.prioritize(m_tasks);
        m_priority_vector = rm.get_prioritized_tasks();
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

void TaskSet::print_schedule() const {
    printf("\n==SCHEDULE==\n");
    for ( auto &pair : m_tasks ) {
        printf("%s |", pair.first);
        for ( auto &elem : m_time_table ) {
            if (pair.first == elem) {
                printf("█");
            } else {
                printf("_");
            }
        }
        printf("\n");
    }
}