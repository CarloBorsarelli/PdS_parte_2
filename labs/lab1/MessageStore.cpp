//
// Created by paolo on 31/03/20.
//

#include <tuple>
#include "MessageStore.h"

const bool debug = false;

MessageStore::MessageStore(int n): dim{n}, n{n}, valid_items{0}{
    messages = new Message[dim];
}

MessageStore::~MessageStore() {
    delete[] messages;
}

void MessageStore::buffer_realloc(){
    if constexpr(debug) std::cout << "MessageStore::buffer_realloc, new size:" << std::to_string(dim+n) << std::endl;

    auto *new_buffer = new Message[dim+n];
    for(int i=0; i<dim; i++) // copia del contenuto attuale
        new_buffer[i] = std::move(messages[i]);
    dim += n;

    delete[] messages;
    messages = new_buffer;
}

void MessageStore::add(Message &m) {
    if(m.getId() < 0) return;

    int i;
    for(i=0; i<dim; i++){
        if(messages[i].getId() == m.getId()) {
            messages[i] = std::move(m); // sostituizione del duplicatore
            return;
        }
    }

    for(i =0; i<dim; i++)
        if(messages[i].getId() < 0) break; // ricerca della prima cella libera
    if(i == dim)
        buffer_realloc();

    messages[i] = m; // copia
    valid_items++;
}

std::optional<Message> MessageStore::get(long id) {
    for(int i=0; i<n; i++)
        if(messages[i].getId() == id)
            return(messages[i]);
    return(std::nullopt);
}

bool MessageStore::remove(long id) {
    if constexpr(debug) std::cout << "MessageStore::remove" << std::endl;

    for(int i=0; i<dim; i++) {
        if (messages[i].getId() == id) {
            messages[i] = std::move(Message{}); // sovrascrivo con un oggetto vuoto >> libero la cella
            valid_items--;
            return(true);
        }
    }
    return(false);
}

std::tuple<int, int> MessageStore::stats() {
    int valid_items = 0, void_items = 0;
    for(int i=0; i<dim; i++){
        if(messages[i].getId() < 0) void_items++;
        else valid_items++;
    }
    return(std::make_tuple(valid_items, void_items));
}

void MessageStore::compact() {
    if constexpr(debug) std::cout << "MessageStore::compact" << std::endl;

    int new_dim = (valid_items/n)*n;
    Message *new_buffer = new Message[new_dim];
    for(int i=0, k=0; i<dim; i++) {
        if (messages[i].getId() >= 0)
            new_buffer[k++] = std::move(messages[i]); // copia per movimento
    }

    delete[] messages;
    messages = new_buffer;
    dim = new_dim;
}

int MessageStore::get_dim() const {
    return(dim);
}

int MessageStore::get_valid_items() const {
    return(valid_items);
}
