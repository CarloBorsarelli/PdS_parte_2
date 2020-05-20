//
// Created by Paolo on 20/05/2020.
//

#ifndef LAB3_COORDINATORT_H
#define LAB3_COORDINATORT_H


#include <vector>
#include <istream>

class CoordinatorT {

public:
    template<class MapperInputT, class ResultT>
    std::vector<ResultT> map(const MapperInputT& input);

    template<class ReducerInputT, class ResultT>
    ResultT reduce(const ReducerInputT& input);

    template<class MapperInputT, class ReducerInputT, class ResultT>
    ResultT mapreduce(std::istream& input, const MapperInputT& mapper, const ReducerInputT& reducer);
};


#endif //LAB3_COORDINATORT_H
