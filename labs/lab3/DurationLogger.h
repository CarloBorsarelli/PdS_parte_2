//
// Created by Genitori on 20/05/2020.
//

#ifndef LAB3_DURATIONLOGGER_H
#define LAB3_DURATIONLOGGER_H


#include <string>

class DurationLogger {
private:
    std::string message;
    std::chrono::system_clock::time_point start;

public:
    explicit DurationLogger(const std::string& message);
    ~DurationLogger();
};


#endif //LAB3_DURATIONLOGGER_H
