//
// Created by paolo on 28/03/20.
//
#include <iostream>
#include <string>

class Test{
public:
    int v;
    Test(int v): v(v){}
    Test(const Test &other): v(other.v){ // costruttore di copia
        std::cout<<"copying "<<&other<<" into "<<this<<std::endl;
    }
    Test(Test &&other): v(other.v){ // costruttore di movimento
        std::cout<<"moving "<<&other<<" into "<<this<<std::endl;
        other.v = 0;
    }
};

Test foo(Test v){
    std::cout<<"&v: "<< &v <<" v: "<< v.v <<std::endl;
    v.v += 1;
    return(v); // il contenuto viene mosso nell'oggetto di destinazione (costruttore di movimento)

    // non avessi il costruttore di movimento: verrebbe usato il costruttore di copia
}

std::string foofoo(std::string v){
    std::cout<<"&v: "<< &v <<" v: "<< v <<std::endl;
    v += std::to_string(1);
    return(v); // il contenuto viene mosso nell'oggetto di destinazione (costruttore di movimento)

    // non avessi il costruttore di movimento: verrebbe usato il costruttore di copia
}

Test bar(Test &&v){
    std::cout<<"&v: "<< &v <<" v: "<< v.v <<std::endl;
    v.v += 1;
    return(v);
}

int main(){
    Test i = {5};
    std::cout<<"--- Test 1 ---"<<std::endl;
    std::cout<<"&i: "<< &i <<" i: "<< i.v <<std::endl;

    Test j = foo(i); // i viene copiato (costruttore di copia)
    std::cout<<"&i: "<< &i <<" i: "<< i.v <<std::endl;
    std::cout<<"&j: "<< &j <<" j: "<< j.v <<std::endl;

    Test x = bar(std::move(i));
    std::cout<<"&i: "<< &i <<" i: "<< i.v <<std::endl;
    std::cout<<"&x: "<< &x <<" x: "<< x.v <<std::endl;

    // analogo con le stringhe (più chiaro)
    std::string k{"abc"};
    std::cout<<"&k: "<< &k <<" k: "<< k <<std::endl;
    std::string w = foofoo(k);
    std::cout<<"&k: "<< &k <<" k: "<< k <<std::endl;
    std::cout<<"&w: "<< &w <<" w: "<< w <<std::endl;

    return 0;
}