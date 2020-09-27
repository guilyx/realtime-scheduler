#include "TaskSet.h"
#include <Python.h>

int main(int argc, char *argv[]) 
{ 
    Task t1 = Task("t1", 0, 1, 12, 12);
    Task t2 = Task("t2", 0, 2, 24, 24);
    Task t3 = Task("t3", 0, 4, 24, 24);
    Task t4 = Task("t4", 0, 5, 18, 18);

    TaskSet job = TaskSet();
    job.register_task(t1);
    job.register_task(t2);
    job.register_task(t3);
    job.register_task(t4);
    // job.remove_task("t3");
    // job.remove_task("t3");
    job.print_task_set();
    job.schedule(RATE_MONOTONIC);
    job.print_statistics();
    stream_schedule_to_file(job.get_time_table(), argv[1]);
    plot_gantt_from_python(argc, argv);
    
    return 0;
}