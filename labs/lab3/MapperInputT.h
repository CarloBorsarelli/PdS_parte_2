//
// Created by Paolo on 20/05/2020.
//

#ifndef LAB3_MAPPERINPUTT_H
#define LAB3_MAPPERINPUTT_H


#include <functional>
#include "ResultT.h"

template<typename K, typename T>
class MapperInputT {
private:
    std::unary_function<K, T> action;

public:
    explicit MapperInputT(std::unary_function<K, T>& action);
    ResultT<K, T>& operator()(T input);
};


#endif //LAB3_MAPPERINPUTT_H
