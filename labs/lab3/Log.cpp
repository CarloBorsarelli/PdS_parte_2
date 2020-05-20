//
// Created by Genitori on 20/05/2020.
//

#include <regex>
#include <iostream>
#include "Log.h"


Log::Log(std::string log_string) {
    std::regex expr ("([0-9]{1,3} (.[0-9]{1,3}){3}) - - \[(~)\] \"([a-zA-Z]*) ([\\\/a-zA-Z_0-9]*) ([\\\/a-zA-Z_0-9]*) ([0-9]{3}) ([0-9]+)\"");
    std::smatch matches;
    std::regex_search(log_string, matches, expr);

    if(matches.size() >= 7) {
        this->ip = matches[0];
        this->date = matches[1];
        this->http_method = matches[2];
        this->path = matches[3];
        this->http_version = matches[4];
        this->code = matches[5];
        this->dimension = matches[6];
        std::cout << "Log(): values initialized" << std::endl;
    }
}

const std::string &Log::getIp() const {
    return ip;
}

const std::string &Log::getDate() const {
    return date;
}

const std::string &Log::getHttpMethod() const {
    return http_method;
}

const std::string &Log::getPath() const {
    return path;
}

const std::string &Log::getHttpVersion() const {
    return http_version;
}

const std::string &Log::getCode() const {
    return code;
}

const std::string &Log::getDimension() const {
    return dimension;
}
