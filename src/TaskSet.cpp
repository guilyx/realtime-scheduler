#include "TaskSet.h"

TaskSet::TaskSet() {}

void TaskSet::register_task(Task tsk) {
    if (m_tasks.find(tsk.name) == m_tasks.end()) {
        // Task not registered, free to go
        m_tasks.insert(std::pair<const char*, Task>(tsk.name, tsk));
        ++m_number_of_tasks;
        this->compute_hyper_period();
        printf("%sTask <%s> has been registered.\n%s", BOLDGREEN, tsk.name, RESET);
    } else {
        std::cout << BOLDRED << "Failed to register task: id already registered." << RESET << std::endl;
    }
}

void TaskSet::remove_task(const char* task_id) {
    if (m_tasks.find(task_id) == m_tasks.end()) {
        printf("%sTask <%s> has not been registered, failed to remove.\n%s", BOLDRED, task_id, RESET);
    } else {
        m_tasks.erase(task_id);
        --m_number_of_tasks;
        this->compute_hyper_period();
        printf("%sTask <%s> has been removed\n%s", BOLDGREEN, task_id, RESET);
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
    printf("%s=======================\n", BOLDWHITE);
    printf("TASK SET {\n");
    printf("%s\thyperperiod = %d\n", BOLDBLUE, m_hyper_period);
    for (auto it = m_tasks.cbegin(); it != m_tasks.cend(); ++it) {
        printf("\t");
        (it->second).print_task();
    }
    printf("%s}\n=======================\n%s", RESET, RESET);
}

void TaskSet::schedule(int scheduler) {
    std::cout << BOLDYELLOW << "Scheduling the tasks..." << RESET << std::endl;
    bool ok;
    switch(scheduler) {
        case RATE_MONOTONIC:
            ok = this->compute_sufficient_condition(scheduler);
            if (ok) {
                this->compute_priorities(scheduler);
                std::cout << BOLDGREEN << "Priorities of the task set have been computed successfully." << RESET << std::endl;
            } else {
                int yn;
                std::cout << BOLDRED << "The current Task Set is not schedulable by RMS. Do you still want to schedule it with RMS ? 1/0 --- " << RESET; 
                std::cin >> yn;
                if (yn == 1) {
                    this->compute_priorities(scheduler);
                    m_hyper_period = m_hyper_period*3;
                    std::vector<const char*> tempVec(m_hyper_period, "");
                    m_time_table = tempVec;
                } else exit(1);
            }
            this->compute_time_table();
            std::cout << BOLDGREEN << "Schedule successfully computed." << RESET << std::endl;
            break;
        case DEADLINE_MONOTONIC:
            std::cout << BOLDRED << "Scheduler not supported yet" << RESET << std::endl;
            break;
        case EARLIEST_DEADLINE_FIRST:
            std::cout << BOLDRED << "Scheduler not supported yet" << RESET << std::endl;
            break;
        default:
            std::cout << BOLDRED << "Scheduler not supported yet" << RESET << std::endl;
            break;
    }
}

std::vector<const char*> TaskSet::get_time_table() const {
    return m_time_table;
}

void TaskSet::compute_time_table() {
    for (int tsk=0; tsk<m_priority_vector.size(); ++tsk) {
        std::vector<int> response_time;
        std::vector<int> waiting_time;
        std::vector<int> activations_rank;
        std::vector<int> deactivation_rank;
        for (int p=0; p<m_hyper_period; ++p) {
            int period = p*m_priority_vector[tsk].get_period() + m_priority_vector[tsk].get_offset();
            int deadline = (p+1)*m_priority_vector[tsk].get_deadline() + m_priority_vector[tsk].get_offset();
            if (period > m_hyper_period) {
                break;
            }
            activations_rank.push_back(period);
            deactivation_rank.push_back(deadline);
        }
        int i = 0;
        for (auto elem: activations_rank) {
            response_time.push_back(0);
            waiting_time.push_back(0);
            int init_activation = elem;
            bool mutual_excl = false;
            for (int j=0; j<m_priority_vector[tsk].get_computation(); ++j) {
                while (m_time_table[elem+j] != "") elem++;
                if (elem + j > m_hyper_period) {
                    response_time.pop_back();
                    waiting_time.pop_back();
                    break;
                }
                if (j == 0) {
                    waiting_time[i] = elem - init_activation;
                    if (waiting_time[i] > m_priority_vector[tsk].get_deadline() && !mutual_excl) {
                        m_tasks.at(m_priority_vector[tsk].name).set_deadlines_missed(m_tasks.at(m_priority_vector[tsk].name).get_statistics().deadlines_missed + 1);
                        if (m_tasks.at(m_priority_vector[tsk].name).get_statistics().deadlines_missed == 1) {
                            m_tasks.at(m_priority_vector[tsk].name).set_first_deadline_missed_t(deactivation_rank[i]);
                        }
                        mutual_excl = true;
                    }
                }
                if (j == (m_priority_vector[tsk].get_computation() - 1)) {
                    response_time[i] = elem + j - init_activation + 1;
                    if (response_time[i] > m_priority_vector[tsk].get_deadline() && !mutual_excl) {
                        m_tasks.at(m_priority_vector[tsk].name).set_deadlines_missed(m_tasks.at(m_priority_vector[tsk].name).get_statistics().deadlines_missed + 1);
                        if (m_tasks.at(m_priority_vector[tsk].name).get_statistics().deadlines_missed == 1) {
                            m_tasks.at(m_priority_vector[tsk].name).set_first_deadline_missed_t(deactivation_rank[i]);
                        }
                        mutual_excl = true;
                    }
                }
                m_time_table[elem + j] = m_priority_vector[tsk].name;
            }
            ++i;
        }
        if (response_time.size() != 0) {
            double art = std::accumulate(response_time.begin(), response_time.end(), 0) / response_time.size();
            m_tasks.at(m_priority_vector[tsk].name).set_average_response_time(art);
        }
        if (waiting_time.size() != 0) {
            double awt = std::accumulate(waiting_time.begin(), waiting_time.end(), 0) / waiting_time.size();
            m_tasks.at(m_priority_vector[tsk].name).set_average_waiting_time(awt);
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

void TaskSet::print_statistics() const {
    printf("%s=======================%s\n", BOLDBLUE, RESET);
    for (auto &pair : m_tasks) {
        pair.second.pretty_print_statistics();
    }
    printf("%s=======================%s\n", BOLDBLUE, RESET);
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

