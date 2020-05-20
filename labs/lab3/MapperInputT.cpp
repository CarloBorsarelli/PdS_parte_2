//
// Created by Paolo on 20/05/2020.
//

#include "MapperInputT.h"


template<typename K, typename T>
MapperInputT<K, T>::MapperInputT(std::unary_function<K, T> &action) : action(action){

}

template<typename K, typename T>
ResultT<K, T> &MapperInputT<K, T>::operator()(T input) {
    return this->action(input);
}
