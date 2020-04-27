#include <string>
#include <sstream> // per creare stringhe con operatore <<
#include <iostream>
#include <utility>
#include <memory>

/*
 * L09
 * 24-04-2020
 */

template<typename T>
class Base{
    Base() {
        std::cout << "Constructor " << typeid(T).name() << " @" << this << std::endl;
    }

    friend T;
public:
    ~Base() {
        std::cout << "Destructor " << typeid(T).name() << " @" << this << std::endl;
    }

    std::string to_string() const {
        return static_cast<const T&>(*this).to_string_second(); // dipende dall'istanziazione
    }
};

class Persona: public Base<Persona>{
    std::string nome;
    std::string cognome;
public:
    Persona(std::string n, std::string c): nome(std::move(n)), cognome(std::move(c)) {
        std::cout << "Person(" << nome << ", " << cognome << ")" << std::endl;
    }

    ~Persona() {
        nome.clear();
        cognome.clear();
    }

    std::string to_string_second() const { // definizione locale
        return nome + " " + cognome;
    }
};

class Buffer: public Base<Buffer> {
public:
    std::string to_string_second() const {
        std::ostringstream oss;
        oss << "Buffer @" << this;
        return oss.

        str();
    }
};

template <typename T>
void print_info(const Base<T>& base) {
    std::cout << base.to_string() << std::endl;
}

Persona *create_persona(std::string n, std::string c){
    return new Persona{n, c};
}

std::unique_ptr<Persona> create_persona_unique_ptr(std::string n, std::string c){
    return std::unique_ptr<Persona>(new Persona{n, c});
}

std::shared_ptr<Persona> create_persona_share_ptr(std::string n, std::string c){
    // return std::shared_ptr<Persona>(new Persona{n, c});
    return std::make_shared<Persona>(n, c);
}

int main() {
    Persona p{"Mario", "Rossi"};
    // std::cout << p1.to_string() << std::endl;
    print_info(p);

    Buffer b;
    // std::cout << b.to_string() << std::endl;
    print_info(b);

    /* Smart pointer */

    /*
     * creazione di un oggetto con new
     * devo gestire il distruttore a mano
     * spesso: creo e distruggo oggetti in punti diversi
     */
    Persona* p1 = create_persona("Mario", "Rossi");
    std::cout << "sizeof(Persona): " << sizeof(Persona) << std::endl;
    std::cout << "sizeof(Persona *): " << sizeof(Persona *) << std::endl; // molto più leggero
    Persona* p2 = p1;

    print_info(*p1);
    print_info(*p2);

    delete(p1);

    /*  */

    // print_info(*p2); // leggo della memoria già rilasciata
    // ATTENZIONE: essendo un programma molto semplice, la memoria può essere rilasciata ma non ancora ri-occupata, quindi diventa accessibile

    std::unique_ptr<Persona> p3 = create_persona_unique_ptr("Mario", "Rossi");
    std::cout << "sizeof(Persona): " << sizeof(Persona) << std::endl;
    std::cout << "sizeof(Persona *): " << sizeof(Persona *) << std::endl;
    std::cout << "sizeof(std::unique_ptr): " << sizeof(p3) << std::endl;

    print_info(*p3);

    // std::unique_ptr<Persona> p4 = p3; // non è valido, non è copiabile >> errore di compilazione
    std::unique_ptr<Persona> p4 = std::move(p3); // il puntatore può essere trasferito, mette null in p1

    // con gli smart pointer il blocco viene in automatico rilasciato quando si esce dallo scope

    /* Shared pointer */

    /*
     * pesa il doppio (16 byte)
     * puntatore interno + blocco di controllo
     * per gestire quanti puntatori ho all'oggetto originale
     * */
    std::shared_ptr<Persona> p5 = create_persona_share_ptr("Mario", "Rossi");
    std::cout << "sizeof(Persona): " << sizeof(Persona) << std::endl;
    std::cout << "sizeof(Persona *): " << sizeof(Persona *) << std::endl;
    std::cout << "sizeof(std::shared_ptr): " << sizeof(p5) << std::endl;
    std::shared_ptr<Persona> p6 = p5; // la copia è ammessa

    p5.reset(); // perdo il controllo dell'oggetto
    p6.reset(); // non avendo altri shared pointer, l'oggetto originale viene distrutto

    return 0;
}
