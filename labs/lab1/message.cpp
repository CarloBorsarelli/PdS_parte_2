//
// Created by paolo on 30/03/20.
//
#include <iostream>
#include <cstring>
#include "message.h"

const bool debug = false;

long Message::unique_id = 0; // init proprietà statica
int Message::cont = 0;

Message::Message(): Message{0} {
    // if constexpr(debug) std::cout << "Message::void constructor" << std::endl;
    id = -1;
}

Message::Message(int n): size{n}, id{Message::unique_id++} {
    // if constexpr(debug) std::cout << "Message::standard constructor" << std::endl;
    data = Message::mkMessage(size);
    Message::cont++;
}

std::ostream &operator<<(std::ostream &out, const Message &m) {
    // if constexpr(debug) std::cout << "Message::operator <<" << std::endl;
    out << m.to_string();
    return(out);
}

char* Message::mkMessage(int n) {
    // if constexpr(debug) std::cout << "Message::string generation" << std::endl;
    std::string vowels = "aeiou";
    std::string consonants = "bcdfghlmnpqrstvz";
    char *m = new char[n+1];
    for(int i=0; i<n; i++){
        m[i]= i%2? vowels[rand()%vowels.size()] :
        consonants[rand()%consonants.size()];
    }
    m[n] = 0 ;

    return(m);
}

Message &Message::operator=(const Message &that){
    if constexpr(debug) std::cout << "Message::operator =" << std::endl;
    if(this != &that){
        delete[] data;
        data = nullptr;
        id = that.id;
        size = that.size;
        data = new char[size];
        memcpy(data, that.data, size);
    }
    return(*this);
}

long Message::getId() const {
    return(this->id);
}

char *Message::getData() const {
    return(this->data);
}

int Message::getSize() const {
    return(this->size);
}

Message::~Message() {
    if constexpr(debug) std::cout << "Message::destructor" << std::endl;
    if(data)
        delete[] data;
    Message::cont--;
}

Message::Message(const Message &that): id{that.id}, size{that.size}, data{new char[size]}{
    if constexpr(debug) std::cout << "Message::copy constructor" << std::endl;
    std::copy(that.data, that.data, data);
}

Message::Message(Message &&that): id(-1), size{0}, data{nullptr}{
    if constexpr(debug) std::cout << "Message::move constructor" << std::endl;
    swap(*this, that);
}

std::string Message::to_string() const {
    return("[id:" + std::to_string(getId()) + "][size:" + std::to_string(getSize()) + "][data:" + getData() + "]");
}

int Message::get_cont() {
    return(Message::cont);
}

Message &Message::operator=(Message &&that) {
    if constexpr(debug) std::cout << "Message::operator = per movimento" << std::endl;
    swap(*this, that);
    return(*this);
}
