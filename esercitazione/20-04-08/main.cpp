#include <iostream>

class Base1{
protected:
    int b1;
    double f;
public:
    virtual int m() { return 1; }
};

class Base2{
protected:
    int b2;
public:
    virtual int n() { return 2; }
};


class Der: public Base1, public Base2 {
public:
    virtual int m() { return  11;}
    virtual int n() { return 21; }
};

int main() {
    Der *ptr = new Der();
    std::cout << "ptr: " << ptr << ", ptr->m()" << ptr->m() << ", ptr->n()" << ptr->n() << std::endl;

    Base1 *ptr1 = ptr;
    std::cout << "ptr1: " << ptr1 << ", ptr1->m()" << ptr1->m() << std::endl;

    Base2 *ptr2 = ptr; // il puntatore cambia rispetto ptr
    std::cout << "ptr2: " << ptr2 << ", ptr2->n()" << ptr2->n() << std::endl;

    Base1 b1 = static_cast<Base1>(*ptr);
    Base2 b2 = static_cast<Base2>(*ptr);

    std::cout << "b1.m()" << b1.m() << std::endl;
    std::cout << "b1.m()" << b2.n() << std::endl;

    ptr2 = ptr;

    std::cout << "static_cast<Der*>(ptr2)" << static_cast<Der*>(ptr2) << std::endl;
    std::cout << "dynamic_cast<Der*>(ptr2)" << dynamic_cast<Der*>(ptr2) << std::endl;
    // entrambe le conversioni sono lecite

    ptr2 = new Base2();
    std::cout << "static_cast<Der*>(ptr2)" << static_cast<Der*>(ptr2) << std::endl;
    std::cout << "dynamic_cast<Der*>(ptr2)" << dynamic_cast<Der*>(ptr2) << std::endl;
    // static_cast: è sempre possibile (Der è un derivato di Base2), ma restituisce un puntatore a zona di memoria non sua
    // dynamic_cast: puntatore = 0 (null) >> garanzia programma corretto

    delete ptr;
    return 0;
}
