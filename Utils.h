#ifndef __UTILS_H__
#define __UTILS_H__

#define _USE_MATH_DEFINES
#include <cmath>
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#define RANDOM() (float)rand()/RAND_MAX
#define INIT_RANDOM_GEN() srand((unsigned int)time(NULL));
#else
#define RANDOM() (float)drand48()
#define INIT_RANDOM_GEN() srand48(time(NULL));
#endif

#ifdef _OPENMP
#include <omp.h>
#endif

#ifdef EXECUTION_TIME_COMPUTATION
#include <chrono> 
using namespace std::chrono; 
#endif 

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

inline
bool
power_of_two(size_t x)
{
    return !(x == 0) && !(x & (x - 1));
}

inline
void
printProgress (double percentage)
{
    int val  = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf ("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush (stdout);
}

inline
float
degrees_to_radians(float a)
{
    return a*(static_cast<float>(M_PI)/180.0f);
}

template <typename T>
T
lerp(const T& A, const T& B, float t)
{
    return (1.0f-t) * A + t * B;
}

template<typename T>
void
safe_delete(T*& ptr)
{
    if(ptr) { delete   ptr; ptr = nullptr; }
}

template <typename T>
void
safe_array_delete(T*& ptr)
{
    if(ptr) { delete[] ptr; ptr = nullptr; }
}

#endif