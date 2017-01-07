//
// Created by alevalv on 06/01/17.
//

#include "Logger.h"

const std::string Logger::VERBOSE = "VERBOSE";

LoggerCont Logger::container = LoggerCont();

ILogger* Logger::getLogger()
{
    char* value = std::getenv(VERBOSE.c_str());
    if (value != NULL && value == std::to_string(1))
    {
        return &container.normalLogger;
    }
    else
    {
        return &container.noLogger;
    }
}
