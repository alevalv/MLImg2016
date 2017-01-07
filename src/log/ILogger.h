//
// Created by alevalv on 06/01/17.
//

#ifndef MACLEA_ILOGGER_H
#define MACLEA_ILOGGER_H

#include <string>

class ILogger
{
public:
    virtual ~ILogger() = default;
    virtual void info(std::string message) = 0;
    virtual void error(std::string message) = 0;
};

#endif //MACLEA_ILOGGER_H
