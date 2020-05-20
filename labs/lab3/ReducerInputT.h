//
// Created by Paolo on 20/05/2020.
//

#ifndef LAB3_REDUCERINPUTT_H
#define LAB3_REDUCERINPUTT_H


#include <functional>
#include "ResultT.h"

template<typename T, typename A>
class ReducerInputT {
    std::string key;
    T value;
    A acc;

private:
    std::binary_function<std::string, T, T> action;

public:
    explicit ReducerInputT(std::binary_function<std::string, T, T>& action);
    ResultT<T>& operator()(T input);

};

#endif //LAB3_REDUCERINPUTT_H
