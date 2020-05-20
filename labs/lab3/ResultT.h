//
// Created by Paolo on 19/05/2020.
//

#ifndef LAB3_RESULTT_H
#define LAB3_RESULTT_H


#include <unordered_map>

template<typename T>
class ResultT {
private:
    std::string key;
    T value;

public:
    ResultT(std::string key, T value);

    [[nodiscard]] std::string get_key() const;
    void set_key(std::string key);
    T get_value() const;
    void set_value(T value);

    ~ResultT();
};


#endif //LAB3_RESULTT_H
