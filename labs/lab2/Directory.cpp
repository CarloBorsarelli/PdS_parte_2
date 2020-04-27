//
// Created by paolo on 27/04/20.
//

#include <iostream>
#include <utility>
#include "Directory.h"

constexpr bool debug = true;

std::shared_ptr<Directory> Directory::root = std::shared_ptr<Directory>(nullptr); // init variabile statica

Directory::Directory(std::string name): name(std::move(name)) {
    if(debug) std::cout << "Directory @" << this << ", name: " << this->name << std::endl;
}

void Directory::ls(int indent) const {
    if(debug) std::cout << "Directory::ls" << std::endl;

    this->ls_recursive(indent, 0);
}

void Directory::ls_recursive(int indent_step, int total_indent) const {
    for(int i=0; i<total_indent; i++)
        std::cout << " ";
    std::cout << "[+] " <<this->name << std::endl;

    // ricorsivamente lavoro sulle sottocartelle
    for(const auto& subdir : this->children)
        subdir.second->ls_recursive(indent_step, total_indent+indent_step);
}

std::shared_ptr<Directory> Directory::get(std::string name) {
    if(debug) std::cout << "Directory::get, name: " << name << std::endl;

    // casi gestiti a parte, in quanto non posso metterli nell'elenco dei weak pointer
    if(!name.compare("."))
        return(std::shared_ptr<Directory>(this->self.lock()));
    if(!name.compare(".."))
        return(std::shared_ptr<Directory>(this->parent.lock()));
        //return(std::static_pointer_cast<Directory>(this->self.lock()));

    auto it = this->children.find(name);
    if(it != this->children.end()) // verifico se ho trovato elementi
        return(std::shared_ptr<Directory>(it->second));

    if(debug) std::cout << "ERROR: directory not found, name: " << name << std::endl;

    return(std::shared_ptr<Directory>(nullptr));
}

std::shared_ptr<Directory> Directory::addDirectory(std::string name) {
    if(debug) std::cout << "Directory::addDirectory" << std::endl;

    std::shared_ptr<Directory> dir = this->makeDirectory(name, this->self);

    this->children.insert_or_assign(name, dir);
    return(dir);
}

std::shared_ptr<Directory> Directory::makeDirectory(std::string name, std::weak_ptr<Directory> parent) {
    if(debug) std::cout << "Directory::makeDirectory, name: " << name << std::endl;

    std::shared_ptr<Directory> dir(new Directory(std::move(name)));
    dir->self = dir->getThis();
    dir->parent = std::move(parent);

    return(dir);
}

std::shared_ptr<Directory> Directory::getRoot() {
    if(debug) std::cout << "Directory::getRoot" << std::endl;

    if(Directory::root == nullptr)
        Directory::root = Directory::makeDirectory("/", std::shared_ptr<Directory>(nullptr));

    return(Directory::root);
}

Directory::~Directory() {
    if(debug) std::cout << "~Directory @" << this << std::endl;
}

std::shared_ptr<Directory> Directory::getThis() {
    return(shared_from_this());
}
