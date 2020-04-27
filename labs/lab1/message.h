//
// Created by paolo on 30/03/20.
//
#ifndef LAB1_MESSAGE_H
#define LAB1_MESSAGE_H

#include <iostream>
#include <string>

class Message{
    static long unique_id;
    static int cont;
    long id;
    char *data;
    int size;

private:
    // funzione per creare un messaggio
    static char *mkMessage(int n);

    // swap
    friend void swap(Message &a, Message &b){
        std::swap(a.id, b.id);
        std::swap(a.data, b.data);
        std::swap(a.size, b.size);
    }

public:
    //costruttore vuoto
    Message();

    //costruttore standard
    Message(int n);
    // ATTENZIONE: mettendo un valore di default (eg. n = 0) il compilatore non capisce più quale costruttore richiamare (quello senza parametri o quello con un parametro, ma con un valore di default?)

    // construttore di copia
    Message(const Message& that);

    // construttore di movimento
    Message(Message&& that);

    // operatore =
    Message &operator=(const Message &that);

    // operatore = per movimento
    Message &operator=(Message &&that);

    // getters
    [[nodiscard]] long getId() const;
    [[nodiscard]] char *getData() const;
    [[nodiscard]] int getSize() const;

    [[nodiscard]] std::string to_string() const;

    //distruttore
    ~Message();

    static int get_cont();
};

// operator <<
std::ostream &operator<<(std::ostream &out, const Message &m);

#endif //LAB1_MESSAGE_H
