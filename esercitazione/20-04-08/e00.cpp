//
// Created by paolo on 08/04/20.
//

#include <iostream>

class C{
public:
    virtual int m() {return 1;}
    virtual int n() {return 2;}
    int p() {return 3;}
};

int main_old(){
    C *c1 = new C();
    //C& c2 = c1;

    int i = c1->m();
    i = c1->m(); // MOV ulteriore: recupero il puntatore alla V-Table
    i = c1->n();
    i = c1->p(); // la V-Table rimane finch ho 1 metodo virtual

    return 0;
}