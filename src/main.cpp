#include "TaskSet.h"
#include <Python.h>

int main(int argc, char *argv[]) 
{ 
    Task t1 = Task("t1", 0, 1, 6, 6);
    Task t2 = Task("t2", 0, 4, 8, 8);
    Task t3 = Task("t3", 0, 1, 2, 2);

    TaskSet job = TaskSet();
    job.register_task(t1);
    job.register_task(t2);
    job.register_task(t3);
    job.remove_task("t3");
    job.remove_task("t3");
    job.print_task_set();
    job.schedule(RATE_MONOTONIC);
    stream_schedule_to_file(job.get_time_table(), argv[1]);
    plot_gantt_from_python(argc, argv);
    
    return 0;
}