#ifndef TASK_H
#define TASK_H

#include <stdlib.h>
#include <iostream>
#include <string>

class Task {
    public:
        Task(const char* name, int offset, int period, int computation, int deadline);
        const char* name;
        int get_offset() const;
        int get_period() const;
        int get_computation() const;
        int get_deadline() const;
        int get_priority() const;
        double get_utilization() const;

        const void set_priority(int p);
        void print_task() const;

    private:
        int m_offset;
        int m_period;
        int m_computation;
        int m_deadline;
        int m_priority = 0;
        double m_utilization;
};

#endif //TASK_H