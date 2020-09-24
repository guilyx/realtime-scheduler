#ifndef TASK_SET_H
#define TASK_SET_H

#include "RateMonotonic.h"
#include "vector"

#define RATE_MONOTONIC          0
#define DEADLINE_MONOTONIC      1
#define EARLIEST_DEADLINE_FIRST 2

class TaskSet {
    public:
        TaskSet();
        void register_task(Task tsk);
        void remove_task(const char* task_id);
        std::map<const char*, Task> get_task_set() const;
        void print_task_set();
        void schedule(int scheduler);
        int get_number_of_tasks() const;
        std::vector<const char*> get_time_table() const;
        void print_schedule() const;
    private:
        std::map<const char*, Task> m_tasks;
        std::vector<const char*> m_time_table;
        std::vector<Task> m_priority_vector;
        int m_number_of_tasks = 0;
        int m_hyper_period;
        void compute_priorities(int scheduler);
        void compute_time_table();
        bool compute_sufficient_condition(int scheduler);
        void compute_hyper_period();
};

#endif // TaskSet
