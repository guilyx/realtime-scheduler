#ifndef HELPER_H
#define HELPER_H

#include <fstream>
#include <iostream>
#include <string.h>
#include "Task.h"

/**
 * @brief 
 * 
 * @param tsk1 
 * @param tsk2 
 * @return true 
 * @return false 
 */
static bool rateMonotonicSorter(Task tsk1, Task tsk2) {
    return tsk1.get_period() < tsk2.get_period();
}

/**
 * @brief 
 * 
 * @param a 
 * @param b 
 * @return int 
 */
static int gcd(int a, int b) 
{ 
    if (b == 0) 
        return a; 
    return gcd(b, a % b); 
} 

/**
 * @brief 
 * 
 * @param arr 
 * @return int 
 */
static int findlcm(int arr[]) 
{ 
    int n = sizeof(int*) / sizeof(arr[0]); 
    int ans = arr[0]; 
  
    for (int i = 1; i < n; i++) 
        ans = (((arr[i] * ans)) / 
                (gcd(arr[i], ans))); 
  
    return ans; 
} 

/**
 * @brief 
 * 
 * @param input 
 */
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

/**
 * @brief 
 * 
 * @param input 
 * @param filename 
 */
static void stream_schedule_to_file(std::vector<const char*> const &input, const char* filename) {
    std::ofstream myfile;
    char buf[30];
    sprintf(buf, "data/%s", filename);
    myfile.open(buf);
    for (auto elem : input) {
        myfile << elem;
        myfile << "\n";
    }
    myfile.close();
}

/**
 * @brief 
 * 
 * @param c 
 * @return wchar_t* 
 */
static wchar_t* GetWC(const char *c) {
    const size_t c_size = strlen(c) + 1;
    wchar_t* wc = new wchar_t[c_size];
    mbstowcs(wc, c, c_size);
    return wc;
}

/**
 * @brief Get the Const W C object
 * 
 * @param c 
 * @return const wchar_t* 
 */
static const wchar_t* GetConstWC(const char *c) {
    const size_t c_size = strlen(c) + 1;
    wchar_t* wc = new wchar_t[c_size];
    mbstowcs(wc, c, c_size);
    return wc;
}

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 */
static void plot_gantt_from_python(int argc, char *argv[]) {
    char buffer[50];
    sprintf(buffer, "python3 src/gantt.py --filename data/%s", argv[1]);
    int x = system(buffer);
    if (x != 0) {
        std::cout << "Failure: python script didn't execute correctly" << std::endl;
    }
}

#endif //HELPER_H
