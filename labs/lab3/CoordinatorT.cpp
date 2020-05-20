//
// Created by Paolo on 20/05/2020.
//

#include <unordered_map>
#include <map>
#include "CoordinatorT.h"


template<class MapperInputT, class ResultT>
std::vector<ResultT> CoordinatorT::map(const MapperInputT &mapper) {
    return mapper();
}

template<class ReducerInputT, class ResultT>
ResultT CoordinatorT::reduce(const ReducerInputT &reducer) {
    return reducer();
}

template<class MapperInputT, class ReducerInputT, class ResultT>
std::vector<ResultT> CoordinatorT::mapreduce(std::istream& input, const MapperInputT &mapper, const ReducerInputT &reducer) {
     auto accs = new std::map<std::string, int>();

    std::string line;
    while(std::getline(input, line)) {
        auto results = this->map(mapper(line));
        for(auto result : results){
            auto key = result->get_key();
            auto value = result->get_value();

            auto new_acc = this->reduce<>(reducer(key, value, accs[key]));
            accs[key] = new_acc;
        }
    }

    auto v = new std::vector<ResultT>();
    for(auto [key, value] : *accs)
        v.push_back(new ResultT(key, value));

    return v;
}
