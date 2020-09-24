#ifndef HELPER_H
#define HELPER_H

#include <set>
#include <functional>
#include "Task.h"

static bool rateMonotonicSorter(Task tsk1, Task tsk2) {
    return tsk1.get_period() < tsk2.get_period();
}

static int gcd(int a, int b) 
{ 
    if (b == 0) 
        return a; 
    return gcd(b, a % b); 
} 

static int findlcm(int arr[]) 
{ 
    int n = sizeof(int*) / sizeof(arr[0]); 
    int ans = arr[0]; 
  
    for (int i = 1; i < n; i++) 
        ans = (((arr[i] * ans)) / 
                (gcd(arr[i], ans))); 
  
    return ans; 
} 

static void print_task_vector(std::vector<const char*> const &input) {
    std::cout << "job == ";
    int i = 0;
    for (auto elem : input) {
        if (i != input.size() - 1) {
            printf("%s(%d) ->", elem, i);
        } else {
            printf("%s(%d)\n", elem, i);
        }
        i++;
    }
}

#endif //HELPER_H