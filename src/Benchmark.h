//
// Created by alevalv on 06/01/17.
//

#ifndef MACLEA_BENCHMARK_H
#define MACLEA_BENCHMARK_H


#include <chrono>
#include <string>

class Benchmark
{
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
    double elapsedTime = 0;
public:
    void start();
    double end();
    std::string getElapsedTime();
    static std::string getCurrentTimeAndDate();
};


#endif //MACLEA_BENCHMARK_H
