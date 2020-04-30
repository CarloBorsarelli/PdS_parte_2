//
// Created by paolo on 28/04/20.
//

#ifndef LAB2_FILE_H
#define LAB2_FILE_H


#include <cstdint>
#include <memory>
#include "Base.h"

class File: public Base {
    uintmax_t size;

protected:
    explicit File(std::string name, uintmax_t size);

public:
    [[nodiscard]] uintmax_t getSize() const;
    static std::shared_ptr<File> makeFile(std::string name, uintmax_t size);

    void ls(int indent=4, int total_indent=0) const override;
    [[nodiscard]] int mType() const override;

    ~File();
};


#endif //LAB2_FILE_H
