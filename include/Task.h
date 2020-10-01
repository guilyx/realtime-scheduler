#ifndef TASK_H
#define TASK_H

#define RESET       "\033[0m"
#define BLACK       "\033[30m"      /* Black */
#define RED         "\033[31m"      /* Red */
#define GREEN       "\033[32m"      /* Green */
#define YELLOW      "\033[33m"      /* Yellow */
#define BLUE        "\033[34m"      /* Blue */
#define MAGENTA     "\033[35m"      /* Magenta */
#define CYAN        "\033[36m"      /* Cyan */
#define WHITE       "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#include <stdlib.h>
#include <iostream>
#include <string>
typedef struct {
    double average_response_time;
    double average_wait_time;
    int deadlines_missed = 0;
    int first_deadline_missed_t = 0;
    double average_missed_deadline_t = 0;
} TaskStatistics;

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

        bool get_ready() const;
        const void set_ready(bool r);
        int get_execution_time() const;
        const void set_execution_time(int ex_t);

        int get_arrival_time() const;
        const void set_arrival_time(int at);

        int get_absolute_deadline() const;
        const void set_absolute_deadline(int ad);

        const void set_priority(int p);
        void print_task() const;

        TaskStatistics get_statistics() const;
        const void set_average_response_time(double art);
        const void set_average_waiting_time(double awt);
        const void set_deadlines_missed(int dm);
        const void set_first_deadline_missed_t(int fdmt);
        const void set_deadline_missed_average_t(double dmat);

        void pretty_print_statistics() const;

    private:
        int m_offset;
        int m_period;
        int m_computation;
        int m_deadline;
        int m_priority = 0;
        bool m_ready = false;
        int m_execution_time;
        int m_absolute_deadline;
        int m_arrival_time;
        double m_utilization;
        TaskStatistics m_statistics;
};

#endif //TASK_H