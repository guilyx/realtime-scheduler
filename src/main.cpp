#include "TaskSet.h"
#include <Python.h>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <signal.h>

volatile sig_atomic_t stop;

void inthand(int signum) {
    stop = 1;
}

int main(int argc, char *argv[]) 
{ 
    int state = 0;
    TaskSet ts = TaskSet();
    signal(SIGINT, inthand);
    std::string q;

    while (!stop) {
        switch(state) {
            case 0:
                while (1) {
                    std::cout << "Please register a task..."  << std::endl;
                    char* tname = new char[25];
                    int offset, wcet, period, deadline;
                    std::cout << "Enter task name --> ";
                    std::cin >> tname;
                    
                    std::cout << "Enter task offset --> ";
                    std::cin >> offset;
                    
                    std::cout << "Enter task worst case execution time --> ";
                    std::cin >> wcet;
                    
                    std::cout << "Enter task period --> ";
                    std::cin >> period;
                    
                    std::cout << "Enter task deadline --> ";
                    std::cin >> deadline;
                    
                    ts.register_task(Task(tname, offset, wcet, period, deadline));

                    std::cout << "Do you want to register another task ? y/n/exit ";
                    std::cin >> q;
                    
                    if (q.compare("n") == 0) {
                        state = 1;
                        break;
                    } else if (q.compare("y") == 0) {
                        // nothing to do
                    } else if (q.compare("exit") == 0) {
                        state = 6;
                        break;
                    }  else {
                        state = 100;
                        break;
                    }
                }
                break;

            case(1):
                while(1) {

                    std::cout << "Do you want to remove a task ? y/n/exit ";
                    std::cin >> q;
                    
                    if (q.compare("y") == 0) {
                        char* rm_tname;
                        std::cout << "Enter task name to remove --> ";
                        std::cin >> rm_tname;
                        
                        ts.remove_task(rm_tname);
                    } else if (q.compare("exit") == 0) {
                        state = 6;
                        break;
                    } else if (q.compare("n") == 0) {
                        state = 2;
                        break;
                    } else {
                        state = 100;
                        break;
                    }
                }
                break;

            case(2):
                std::cout << "Do you want to print your task state ? y/n/exit ";
                std::cin >> q;
                
                if (q.compare("y") == 0) {
                    ts.print_task_set();
                } else if (q.compare("exit") == 0) {
                    state = 6;
                    break;
                } else if (q.compare("n") == 0) {
                    state = 3;
                    break;
                } else {
                    state = 100;
                    break;
                }

            case(3):
                std::cout << "Enter the scheduler you want to use (rm, dm, edf, exit) --> ";
                std::cin >> q;
                
                if (q == "rm") {
                    ts.schedule(RATE_MONOTONIC);
                    state = 4;
                } else if (q == "dm") {
                    ts.schedule(DEADLINE_MONOTONIC);
                    state = 4;
                } else if (q == "edf") {
                    ts.schedule(EARLIEST_DEADLINE_FIRST);
                    state = 3;
                    std::cout << "Choose rm" << std::endl;
                } else if (q.compare("exit") == 0) {
                    state = 6;
                } else {
                    state = 100;
                }
                break;
            
            case(4):
                std::cout << "Print statistics (deadline misses, average response time, average waiting time...) ? y/n ";
                std::cin >> q;
                
                if (q.compare("y") == 0) {
                    ts.print_statistics();
                    state = 5;
                    break;
                } else if (q.compare("exit") == 0) {
                    state = 6;
                    break;
                } else if (q.compare("n") == 0) {
                    state = 5;
                    break;
                } else {
                    state = 100;
                    break;
                }
            
            case(5): 
                std::cout << "Plot schedule ? y/n ";
                std::cin >> q;
                
                if (q.compare("y") == 0) {
                    stream_schedule_to_file(ts.get_time_table(), argv[1]);
                    plot_gantt_from_python(argc, argv);
                    state = 6;
                    break;
                } else if (q.compare("n") == 0) {
                    state = 6;
                    break;
                } else {
                    state = 100;
                    break;
                }
            case(6):
                std::cout << "Restart a new simulation ? y/n ";
                std::cin >> q;
                
                if (q.compare("y") == 0) {
                    ts = TaskSet();
                    state = 0;
                    break;
                } else if (q.compare("n") == 0) {
                    exit(EXIT_SUCCESS);
                } else {
                    state = 100;
                    break;
                }
            default:
                std::cout << "Unreachable state !" << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    return 0;
}