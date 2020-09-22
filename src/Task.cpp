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

bool Task::get_ready() const {
    return m_ready;
}

const void Task::set_ready(bool r) {
    m_ready = r;
}

int Task::get_execution_time() const {
    return m_execution_time;
}

const void Task::set_execution_time(int ex_t) {
    m_execution_time = ex_t;
}

int Task::get_arrival_time() const {
    return m_arrival_time;
}

const void Task::set_arrival_time(int at) {
    m_arrival_time = at;
}

int Task::get_absolute_deadline() const {
    return m_absolute_deadline;
}

const void Task::set_absolute_deadline(int ad) {
    m_absolute_deadline = ad;
}


void Task::print_task() const {
    if (m_priority == 0) {
        printf("%s: {O = %d, C = %d, T = %d, D = %d}\n", this->name, m_offset, m_computation, m_period, m_deadline);
    } else {
        printf("%s: {O = %d, C = %d, T = %d, D = %d, Prio = %d}\n", this->name, m_offset, m_computation, m_period, m_deadline, m_priority);
    }
}
