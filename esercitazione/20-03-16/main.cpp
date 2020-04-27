#include <iostream>

/*
 * L03
 * 16-03-20
 * */

class Prova{
    int val;
    char *str;
public:
    Prova(): val(0), str("ciao"){ // viene inizializzata la variabile prima di accedere al corpo del costruttore
        std::cout<<"Prova() @"<<this<<std::endl;
    }
    Prova(int n): val(n), str(""){ // posso mettere anche più valori inizializzati
        std::cout<<"Prova("<<n<<") @"<<this<<std::endl;
    }

    int getVal(){
        return val;
    }

    ~Prova(){
        std::cout<<"~Prova() @"<<this<<std::endl;
    }

};

Prova p;

void f(){
    Prova p;
    p.getVal();

    return;
}

int main() {
    std::cout<<"Inizio main"<<std::endl;

    Prova p(4); //C++98, CLion aggiunger una n: più piccola per maggiore comprensione
    Prova p2{4}; //C++11, è più robusta se ridefiniamo il funzionamento degli oggetti come funzioni
    int v{54}; // vale anche per i tipi base

    std::cout<<p.getVal()<<std::endl;
    std::cout<< ::p.getVal()<<std::endl; // mi riferisco all'oggetto globale (spazio => no contesto)

    f(); // lo stack decresce dall'alto verso il basso, quindi il secondo prova avrà indirizzo più basso

    std::cout<<"Fine main"<<std::endl;

    return 0;
}
