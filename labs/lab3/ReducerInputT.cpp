//
// Created by Paolo on 20/05/2020.
//

#include "ReducerInputT.h"


template<typename K, typename T>
ReducerInputT<K, T>::ReducerInputT(std::binary_function<K, T, T>& action) : action(action) {
}

template<typename K, typename T>
ResultT<K, T> &ReducerInputT<K, T>::operator()(T input) {
    return this->action(input);
}
