//
// Created by Paolo on 20/05/2020.
//

#include "CoordinatorT.h"


template<class MapperInputT, class ResultT>
std::vector<ResultT> CoordinatorT::map(const MapperInputT &input) {
    return std::vector<ResultT>();
}

template<class ReducerInputT, class ResultT>
ResultT CoordinatorT::reduce(const ReducerInputT &input) {
    return nullptr;
}

template<class MapperInputT, class ReducerInputT, class ResultT>
ResultT CoordinatorT::mapreduce(std::istream& input, const MapperInputT &mapper, const ReducerInputT &reducer) {
    ResultT acc = new ResultT();
    acc.clear();

    std::string line;
    while(std::getline(input, line)) {
        auto results = mapper(line);
        for(auto [key, result] : results){
            auto value = reducer(key, result, acc[key]);
            acc[key] = value;
        }
    }

    return acc;
}
