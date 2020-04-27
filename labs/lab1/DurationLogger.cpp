//
// Created by paolo on 31/03/20.
//
#include "DurationLogger.h"
#include <string>

DurationLogger::DurationLogger(const std::string &name): name(name){
    time = clock();
    std::cout << ">>>>>>>>>>>>>> starting " << name << std::endl;
}

DurationLogger::~DurationLogger(){
    std::cout << "<<<<<<<<<<<<<< ending " << name << ": " << std::to_string((clock()-time)/(double)CLOCKS_PER_SEC) <<" s" << std::endl;
}
