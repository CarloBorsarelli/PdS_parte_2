//
// Created by Ragazzi on 19/05/2020.
//

#include "ResultT.h"

#include <utility>


template<typename T>
ResultT<T>::ResultT(std::string key, T value) : key(std::move(key)), value(value) {
}

template<typename T>
std::string ResultT<T>::get_key() const {
    return key;
}

template<typename T>
void ResultT<T>::set_key(std::string key) {
    ResultT::key = key;
}

template<typename T>
T ResultT<T>::get_value() const {
    return value;
}

template<typename T>
void ResultT<T>::set_value(T value) {
    ResultT::value = value;
}
}

template<typename T>
ResultT<T>::~ResultT() {
    if(this->value)
        delete value;
}

