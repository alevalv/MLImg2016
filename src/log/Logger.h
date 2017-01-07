//
// Created by alevalv on 06/01/17.
//

#ifndef MACLEA_LOGGER_H
#define MACLEA_LOGGER_H


#include <memory>
#include "LoggerCont.h"
#include "ILogger.h"

class Logger
{
    static const std::string VERBOSE;
    static LoggerCont container;
public:
    static ILogger* getLogger();
};


#endif //MACLEA_LOGGER_H
