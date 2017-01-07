//
// Created by alevalv on 06/01/17.
//

#include "Benchmark.h"

using namespace std;

void Benchmark::start()
{
    startTime = chrono::system_clock::now();
}

double Benchmark::end()
{
    endTime = chrono::system_clock::now();
    elapsedTime = (endTime - startTime).count();

    return elapsedTime;
}

std::string Benchmark::getCurrentTimeAndDate()
{
    time_t time = chrono::system_clock::to_time_t(chrono::system_clock::now());
    return ctime(&time);
}

std::string Benchmark::getElapsedTime()
{
    string output = "Elapsed time: ";
    output+=to_string(elapsedTime/1000000);
    output+="\n";

    return output;
}




