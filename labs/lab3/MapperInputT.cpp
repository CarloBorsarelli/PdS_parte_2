//
// Created by Paolo on 20/05/2020.
//

#include "MapperInputT.h"


template<typename T>
MapperInputT<T>::MapperInputT(const std::unary_function<std::string, ResultT<T>>& action) : action(action){

}

template<typename T>
ResultT<T> &MapperInputT<T>::operator()(T input) {
    return this->action(input);
}
