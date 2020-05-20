//
// Created by Genitori on 20/05/2020.
//

#ifndef LAB3_LOG_H
#define LAB3_LOG_H


#include <string>

class Log {
private:
    std::string ip;
    std::string date;
    std::string http_method;
    std::string path;
    std::string http_version;
    std::string code;
    std::string dimension;
public:
    Log(std::string log_string);

    [[nodiscard]] const std::string &getIp() const;
    [[nodiscard]] const std::string &getDate() const;
    [[nodiscard]] const std::string &getHttpMethod() const;
    [[nodiscard]] const std::string &getPath() const;
    [[nodiscard]] const std::string &getHttpVersion() const;
    [[nodiscard]] const std::string &getCode() const;
    [[nodiscard]] const std::string &getDimension() const;
};


#endif //LAB3_LOG_H
