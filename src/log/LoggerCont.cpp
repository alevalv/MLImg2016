//
// Created by alevalv on 06/01/17.
//

#include <cstdlib>
#include <iostream>
#include "LoggerCont.h"

void LoggerCont::NoLogger::info(std::string message)
{
    //should do nothing
}

void LoggerCont::NoLogger::error(std::string message)
{
    //should do nothing
}

void LoggerCont::NormalLogger::info(std::string message)
{
    std::cout<<message+"\n";
}

void LoggerCont::NormalLogger::error(std::string message)
{
    std::cerr<<message+"\n";
}
