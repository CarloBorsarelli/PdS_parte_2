/*
 * L06
 * 25-03-2020
 * */

#include <iostream>
#include <stdio.h>
#include <memory.h>

class Point{
private:
    int a, b;

public:
    Point(int a, int b): a(a), b(b){}
};

class CBuffer{
    int size;
    char *ptr;

public:
    CBuffer(){}

    CBuffer(int size): size(size){
        ptr = new char[size];
    }

    CBuffer* createBuffer(int size){
        return(new CBuffer(size));
    }

    CBuffer(CBuffer &&source){
        this->size = source.size;
        this->ptr = source.ptr;

        source.ptr = NULL; // IMPORTANTE riportare l'altro oggetto in uno stato sicuro
    }

    /*
     * costruttore di classe
     * ha un solo parametro (reference)
     * */
    CBuffer(const CBuffer& source):size(source.size){
        this->ptr=new char[size];
        memcpy(this->ptr, source.ptr, size);
    }

    ~CBuffer(){
        delete[] ptr;
    }
};

class NoCopy{
    int n;
    void *ptr;
public:
    NoCopy(int n, void *ptr): n(n), ptr(ptr){}

    NoCopy(NoCopy &&other): n(other.n), ptr(other.ptr){
        other.ptr = nullptr; // svuoto lo stato dell'altro oggetto
    }

    // const: metodi che non modificano lo stato interno
    int getN(): const { return n; }
    void *getPtr(): const { return ptr };

    // blocco il costruttore di copia creato in automatico
    NoCopy(const NoCopy& other) = delete; // provare a rimuovere
};

CBuffer a(32); // standard
CBuffer b{32}; // moderno
CBuffer c(a); // copia dell'oggetto

void f1(NoCopy &n){
    std::cout<<"n"<<n.getN()<<", "<<n.getPtr()<<std::endl;
}

void f2(NoCopy &n){
    std::cout<<"n"<<n.getN()<<", "<<n.getPtr()<<std::endl;
}

void f3(const NoCopy &n){ // constr, quindi posso usare solo metodi const
    std::cout<<"n"<<n.getN()<<", "<<n.getPtr()<<std::endl;
}

/*
 * per vedere il movimento
 * */
NoCopy g1(int n, void *ptr){
    return NoCopy(n, ptr); // invio direttamente l'oggetto, non lo copio
}

NoCopy g2(int n, void *ptr){
    NoCopy obj(n, ptr);
    return obj; // errore, ne faccio una copia, ma il costruttore di copia
}

int main(){
    NoCopy n1(10, (void *)128); // casting forzato
    NoCopy n2(n1); // errore, non posso copiarlo

    std::cout<<"n1"<<n1.getN()<<", "<<n1.getPtr()<<std::endl;
    std::cout<<"n2"<<n2.getN()<<", "<<n2.getPtr()<<std::endl;

    f1(n1); // errore, ne faccio una copia
    f2(&n1); // in questo caso non sto facendo copie, quindi viene accettato
    f3(&n1);

    // array dinamici
    CBuffer *listaBuffer = new CBuffer[10];
    delete[] listaBuffer;

    return 0;
}
