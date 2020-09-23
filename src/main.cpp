#include "TaskSet.h"

int main() 
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
}