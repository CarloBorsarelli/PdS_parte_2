//
// Created by Paolo on 20/05/2020.
//

#ifndef LAB3_REDUCERINPUTT_H
#define LAB3_REDUCERINPUTT_H


#include <functional>
#include "ResultT.h"

template<typename K, typename T>
class ReducerInputT {
private:
    std::binary_function<K, T, T> action;

public:
    explicit ReducerInputT(std::binary_function<K, T, T>& action);
    ResultT<K, T>& operator()(T input);

};

#endif //LAB3_REDUCERINPUTT_H
