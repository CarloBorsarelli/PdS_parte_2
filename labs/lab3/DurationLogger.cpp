//
// Created by Genitori on 20/05/2020.
//

#include <iostream>
#include <chrono>
#include "DurationLogger.h"

DurationLogger::DurationLogger(const std::string &message) {
    this->message = message;
    this->start = std::chrono::system_clock::now();
    std::cout << ">>>>>>>>>>>>>> starting " << this->message << std::endl;
}

DurationLogger::~DurationLogger() {
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - this->start;
    std::cout << "<<<<<<<<<<<<<<< ending " << this->message << ": " << elapsed_seconds.count() << " sec" << std::endl;
}
