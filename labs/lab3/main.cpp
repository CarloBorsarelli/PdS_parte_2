#include <iostream>
#include "MapperInputT.h"
#include "ReducerInputT.h"

int main() {
    auto mapper = new MapperInputT<std::string, std::string>([](auto a){nullptr});
    auto reducer = new ReducerInputT<std::string, std::string>([](auto a){nullptr});



    return 0;
}
