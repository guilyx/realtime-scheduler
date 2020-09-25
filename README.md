# Real-Time Scheduler

A C++ implementation of a scheduling simulator

## Overview

This scheduling simulator is as of now capable of computing schedulability, feasibility of Rate Monotonic Scheduler, as well as compute the schedule and plot it as a Gantt Chart.

```
├── CMakeLists.txt
├── data
│   ├── hello
│   └── rms_test_toto
├── include
│   ├── Helpers.h
│   ├── RateMonotonic.h
│   ├── Simulator.h
│   ├── Task.h
│   └── TaskSet.h
├── LICENSE
├── README.md
└── src
    ├── gantt.py
    ├── main.cpp
    ├── RateMonotonic.cpp
    ├── Simulator.cpp
    ├── Task.cpp
    └── TaskSet.cpp
```

## Architecture

```cpp
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
```

A Task has specifications such as offset, computation time, period and deadline. 
A Task can be registered or removed from a Task Set, which can compute its feasibility/schedulability and the schedule resulted from the chosen Scheduling Algorithm.

## Run

Always run from the root of the project.

1. Build the project : 
```
$ mkdir build
$ cd build/ 
$ cmake ..
$ make
$ cd ..
```

2. Run the project : `./rt_sched "filename"

3. Python script documentation :

```
$ python src/gantt.py --help
usage: gantt.py [-h] [--filename FILENAME]

Real-Time tasks Gantt plotter from data file

optional arguments:
  -h, --help           show this help message and exit
  --filename FILENAME  Register the path to the schedule description file
```
