#include "Task.h"

Task::Task(const char* name, int offset, int computation, int period, int deadline) {
    this->name = name;
    m_computation = computation;
    m_deadline = deadline;
    m_offset = offset;
    m_period = period;
    m_utilization = double(computation)/double(period);
}

int Task::get_offset() const {
    return m_offset;
}

int Task::get_period() const {
    return m_period;
}

int Task::get_computation() const {
    return m_computation;
}

int Task::get_deadline() const {
    return m_deadline;
}

double Task::get_utilization() const {
    return m_utilization;
}

int Task::get_priority() const {
    return m_priority;
}

const void Task::set_priority(int p) {
    m_priority = p;
}

void Task::print_task() const {
    if (m_priority == 0) {
        printf("%s: {O = %d, C = %d, T = %d, D = %d}\n", this->name, m_offset, m_computation, m_period, m_deadline);
    } else {
        printf("%s: {O = %d, C = %d, T = %d, D = %d, Prio = %d}\n", this->name, m_offset, m_computation, m_period, m_deadline, m_priority);
    }
}
