//
// Created by paolo on 28/03/20.
//
#include <iostream>
#include <string>

std::string foo(std::string v){
    std::cout<<"&v: "<< &v <<" v: "<<v<<std::endl;
    v = v+std::to_string(1);
    return v;
}

std::string bar(std::string &v){
    std::cout<<"&v: "<< &v <<" v: "<<v<<std::endl;
    v = v+std::to_string(1);
    return v;
}

std::string bar1(std::string v){
    std::cout<<"&v: "<< &v <<std::endl; // stampo solo il puntatore > altrimenti la funzione esplode
    return "";
}

std::string& foofoo(std::string &v){
    std::cout<<"&v: "<< &v <<" v: "<<v<<std::endl;
    v = v+std::to_string(1);
    return v; // ritorno il reference di una variabile locale
}

int main_old(){
    std::string i = "5";
    std::cout<<"--- Test 1 ---"<<std::endl;
    std::cout<<"&i: "<< &i <<" i: "<<i<<std::endl;

    std::string j = foo(i);
    std::cout<<"&i: "<< &i <<" i: "<<i<<std::endl;
    std::cout<<"&j: "<< &j <<" j: "<<j<<std::endl;

    std::cout<<"--- Test 2 ---"<<std::endl;
    std::cout<<"&i: "<< &i <<" i: "<<i<<std::endl;

    // j = bar(nullptr); // non ammesso dal compilatore
    j = bar(i); // passo l'originale
    std::cout<<"&i: "<< &i <<" i: "<<i<<std::endl;
    std::cout<<"&j: "<< &j <<" j: "<<j<<std::endl;

    std::cout<<"--- Test 3 ---"<<std::endl;
    std::string *ptr = nullptr;
    // j = bar(ptr); // bloccato dal compilatore
    j = bar1(*ptr); // considerato corretto dal compilatore
    std::cout<<"&i: "<< &i <<" i: "<<i<<std::endl;
    std::cout<<"&j: "<< &j <<" j: "<<j<<std::endl;

    std::cout<<"--- Test 4 ---"<<std::endl;
    std::cout<<"&i: "<< &i <<" i: "<<i<<std::endl;
    j = foofoo(i);
    std::cout<<"&i: "<< &i <<" i: "<<i<<std::endl;
    std::cout<<"&j: "<< &j <<" j: "<<j<<std::endl; // indirizzo di una variabile locale oramai deallocata

    return 0;
}
