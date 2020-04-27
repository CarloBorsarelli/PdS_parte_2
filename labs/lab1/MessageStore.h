//
// Created by paolo on 31/03/20.
//

#ifndef LAB1_MESSAGESTORE_H
#define LAB1_MESSAGESTORE_H

#include <optional>
#include "message.h"

class MessageStore {
    Message *messages;
    int dim;
    int n;
    int valid_items;

public:
    explicit MessageStore(int n);
    ~MessageStore();
    void add(Message &m);
    std::optional<Message> get(long id);
    bool remove(long id);
    std::tuple<int, int> stats();
    void compact();

    void buffer_realloc();
    [[nodiscard]] int get_dim() const;
    [[nodiscard]] int get_valid_items() const;
};


#endif //LAB1_MESSAGESTORE_H
