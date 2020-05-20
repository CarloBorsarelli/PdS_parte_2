//
// Created by Paolo on 19/05/2020.
//

#ifndef LAB3_RESULTT_H
#define LAB3_RESULTT_H


template<typename K, typename T>
class ResultT {
private:
    K key;
    T value;
    T acc;

public:
    T operator()(K key);
};


#endif //LAB3_RESULTT_H
