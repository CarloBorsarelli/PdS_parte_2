//
// Created by paolo on 28/04/20.
//

#include <iostream>
#include "File.h"


constexpr bool debug = true;

File::File(std::string name, uintmax_t size): Base(std::move(name)), size(size){
    if(debug) std::cout << "File @" << this << ", name: " << this->getName() << ", size: " << this->getSize() << std::endl;
}

uintmax_t File::getSize() const {
    return(this->size);
}

void File::ls(int indent, int total_indent) const {
    for(int i=0; i<total_indent; i++)
        std::cout << " ";
    std::cout << this->getName() << " " << this->getSize() << std::endl;
}

int File::mType() const {
    return(File_type);
}

std::shared_ptr<File> File::makeFile(std::string name, uintmax_t size) {
    std::shared_ptr<File> file(new File(name, size));

    return(file);
}

File::~File() {
    if(debug) std::cout << "~File @" << this << ", name: " << this->getName() << ", size: " << this->getSize() << std::endl;
}

