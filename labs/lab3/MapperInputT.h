//
// Created by Paolo on 20/05/2020.
//

#ifndef LAB3_MAPPERINPUTT_H
#define LAB3_MAPPERINPUTT_H


#include <functional>
#include "ResultT.h"

template<typename T>
class MapperInputT {
private:
    std::unary_function<ResultT<T>, T> action;

public:
    explicit MapperInputT(const std::unary_function<std::string, ResultT<T>>& action);
    ResultT<T>& operator()(T input);
};


#endif //LAB3_MAPPERINPUTT_H
