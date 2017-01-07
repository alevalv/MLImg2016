//
// Created by alevalv on 06/01/17.
//

#ifndef MACLEA_LOGGERCONT_H
#define MACLEA_LOGGERCONT_H

#include <memory>
#include "ILogger.h"

struct LoggerCont
{
    class NoLogger : public ILogger
    {
        void info(std::string message);
        void error(std::string message);
    };
    class NormalLogger : public ILogger
    {
        void info(std::string message);
        void error(std::string message);
    };
public:
    NoLogger noLogger;
    NormalLogger  normalLogger;
};


#endif //MACLEA_LOGGERCONT_H
