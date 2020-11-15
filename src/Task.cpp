#include "Task.h"

/**
 * @brief Construct a new Task:: Task object
 * 
 * @param name 
 * @param offset 
 * @param computation 
 * @param period 
 * @param deadline 
 */
Task::Task(const char* name, int offset, int computation, int period, int deadline) {
    this->name = name;
    m_computation = computation;
    m_deadline = deadline;
    m_offset = offset;
    m_period = period;
    m_utilization = double(computation)/double(period);
    m_ch = double(computation)/double(deadline);
}

/**
 * @brief get task offset
 * 
 * @return int 
 */
int Task::get_offset() const {
    return m_offset;
}

/**
 * @brief get task period
 * 
 * @return int 
 */
int Task::get_period() const {
    return m_period;
}

/**
 * @brief get task wcet
 * 
 * @return int 
 */
int Task::get_computation() const {
    return m_computation;
}

/**
 * @brief get deadline
 * 
 * @return int 
 */
int Task::get_deadline() const {
    return m_deadline;
}

/**
 * @brief get utilization factor
 * 
 * @return double 
 */
double Task::get_utilization() const {
    return m_utilization;
}

/**
 * @brief get ch factor
 * 
 * @return double 
 */
double Task::get_ch() const {
    return m_ch;
}

/**
 * @brief get priority
 * 
 * @return int 
 */
int Task::get_priority() const {
    return m_priority;
}

/**
 * @brief set priority
 * 
 * @param p 
 */
const void Task::set_priority(int p) {
    m_priority = p;
}

/**
 * @brief get ready state
 * 
 * @return true 
 * @return false 
 */
bool Task::get_ready() const {
    return m_ready;
}

/**
 * @brief set ready state
 * 
 * @param r 
 */
const void Task::set_ready(bool r) {
    m_ready = r;
}

/**
 * @brief get execution time
 * 
 * @return int 
 */
int Task::get_execution_time() const {
    return m_execution_time;
}

/**
 * @brief set execution time
 * 
 * @param ex_t 
 */
const void Task::set_execution_time(int ex_t) {
    m_execution_time = ex_t;
}

/**
 * @brief get arrival time
 * 
 * @return int 
 */
int Task::get_arrival_time() const {
    return m_arrival_time;
}

/**
 * @brief set arrival time
 * 
 * @param at 
 */
const void Task::set_arrival_time(int at) {
    m_arrival_time = at;
}

/**
 * @brief get absolute deadline
 * 
 * @return int 
 */
int Task::get_absolute_deadline() const {
    return m_absolute_deadline;
}

/**
 * @brief set absolute deadline
 * 
 * @param ad 
 */
const void Task::set_absolute_deadline(int ad) {
    m_absolute_deadline = ad;
}

/**
 * @brief task structure printer
 * 
 */
void Task::print_task() const {
    if (m_priority == 0) {
        printf("%s: {O = %d, C = %d, T = %d, D = %d}\n", this->name, m_offset, m_computation, m_period, m_deadline);
    } else {
        printf("%s: {O = %d, C = %d, T = %d, D = %d, Prio = %d}\n", this->name, m_offset, m_computation, m_period, m_deadline, m_priority);
    }
}

/**
 * @brief get statistics
 * 
 * @return TaskStatistics 
 */
TaskStatistics Task::get_statistics() const {
    return m_statistics;
}

/**
 * @brief set average response time
 * 
 * @param art 
 */
const void Task::set_average_response_time(double art) {
    m_statistics.average_response_time = art;
}

/**
 * @brief set average waiting time
 * 
 * @param awt 
 */
const void Task::set_average_waiting_time(double awt) {
    m_statistics.average_wait_time = awt;
}

/**
 * @brief set deadline missed
 * 
 * @param dm 
 */
const void Task::set_deadlines_missed(int dm) {
    m_statistics.deadlines_missed = dm;
}

/**
 * @brief set time of the first deadline missed
 * 
 * @param fdmt 
 */
const void Task::set_first_deadline_missed_t(int fdmt) {
    m_statistics.first_deadline_missed_t = fdmt;
}

/**
 * @brief set average time by which task missed deadlines
 * 
 * @param dmat 
 */
const void Task::set_deadline_missed_average_t(double dmat) {
    m_statistics.average_missed_deadline_t = dmat;
}

/**
 * @brief task statistics printer
 * 
 */
void Task::pretty_print_statistics() const {
    printf("%sTASK <%s> STATISTICS : {\n\tAverage Response Time: %.2f\n\tAverage Wait Time: %.2f\n\t%sDeadline missed: %d\n\tTime of first missed deadline: %d\n%s}%s\n", 
           BOLDWHITE, this->name, m_statistics.average_response_time, m_statistics.average_wait_time, BOLDRED, m_statistics.deadlines_missed, m_statistics.first_deadline_missed_t, RESET, RESET/*, m_statistics.average_missed_deadline_t*/);
}
