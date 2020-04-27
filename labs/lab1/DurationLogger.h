//
// Created by paolo on 31/03/20.
//
#ifndef LAB1_DURATIONLOGGER_H
#define LAB1_DURATIONLOGGER_H

#include <iostream>
#include <string>

/*
 * classe utile per il RAII (resource acquisition is initialization)
 * */
class DurationLogger {
    std::string name;
    clock_t time;

public:
    DurationLogger(const std::string &name);
    ~DurationLogger();
};


#endif //LAB1_DURATIONLOGGER_H
