#include <iostream>
#include <fstream>
#include "MapperInputT.h"
#include "ReducerInputT.h"
#include "Log.h"
#include "DurationLogger.h"
#include "CoordinatorT.h"

int main() {
    std::ifstream input;
    input.open("example.txt");

    {
        auto timer = new DurationLogger("requests grouped by IP");
        CoordinatorT coord;
        MapperInputT<std::string, int> mapper {[](std::string line) {
            Log log {line};
            ResultT<std::string, int> result {log.getIp(), 1};

            auto v = new std::vector<ResultT<std::string, int>>();
            v->push_back(result);

            return v;
        }};
        ReducerInputT<std::string, int> reducer {[](std::string key, int value, int acc) {
            return acc + value;
        }};

        coord.mapreduce<MapperInputT, ReducerInputT>(input, mapper, reducer);
    }
    input.seekg(0, std::ios::beg);



    input.close();

    return 0;
}
