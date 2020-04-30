//
// Created by paolo on 27/04/20.
//

#include <iostream>
#include <utility>
#include "Directory.h"

constexpr bool debug = true;

std::shared_ptr<Directory> Directory::root = std::shared_ptr<Directory>(nullptr); // init variabile statica

Directory::Directory(std::string name): Base(std::move(name)) {
    if(debug) std::cout << "Directory @" << this << ", name: " << this->getName() << std::endl;
}

void Directory::ls(int indent, int total_indent) const {
    // if(debug) std::cout << "Directory::ls" << std::endl;

    for(int i=0; i<total_indent; i++)
        std::cout << " ";
    std::cout << "[+] " << this->getName() << std::endl;

    // ricorsivamente suoi sotto elementi
    for(const auto& child : this->children)
        child.second->ls(indent, total_indent+indent);
}

std::shared_ptr<Base> Directory::get(const std::string& name) {
    if(debug) std::cout << "Directory::get, name: " << name << std::endl;

    // casi gestiti a parte, in quanto non posso metterli nell'elenco dei weak pointer
    if(name == ("."))
        return(std::dynamic_pointer_cast<Base>(std::shared_ptr<Directory>(this->self.lock())));
    if(name == (".."))
        return(std::dynamic_pointer_cast<Base>(std::shared_ptr<Directory>(this->parent.lock())));
        //return(std::static_pointer_cast<Directory>(this->self.lock()));

    auto it = this->children.find(name);
    if(it != this->children.end()) // verifico se ho trovato elementi
        return(std::dynamic_pointer_cast<Base>(it->second));

    if(debug) std::cout << "Directory::get, ERROR: directory not found, name: " << name << std::endl;

    return(std::shared_ptr<Base>(nullptr));
}

std::shared_ptr<Directory> Directory::addDirectory(const std::string& name) {
    if(debug) std::cout << "Directory::addDirectory" << std::endl;

    // verifico se non esiste ancora una cartella con quel nome nella cartella attuale
    auto it = this->children.find(name);
    if(it != this->children.end() && it->second->mType() == Directory_type)
        return(std::dynamic_pointer_cast<Directory>(it->second)); // se esiste già, restituisco quella esistente

    // creo la cartella
    std::shared_ptr<Directory> dir = Directory::makeDirectory(name, this->self);
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
    if(debug) std::cout << "~Directory @" << this << ", name: " << this->getName() << std::endl;
}

std::shared_ptr<Directory> Directory::getThis() {
    return(shared_from_this());
}

std::shared_ptr<Directory> Directory::getDir(const std::string &name) {
    return(std::static_pointer_cast<Directory>(this->get(name)));
}

std::shared_ptr<File> Directory::addFile(const std::string &name, uintmax_t size) {
    if(debug) std::cout << "Directory::addFile, name: " << name << ", size: " << size << std::endl;

    // verifico se non esiste ancora un file con quel nome nella cartella attuale
    auto it = this->children.find(name);
    if(it != this->children.end() && it->second->mType() == File_type)
        return(std::dynamic_pointer_cast<File>(it->second)); // se esiste già restituisco quello esistente

    // creo un file
    std::shared_ptr<File> file = File::makeFile(name, size); // Directory::makeDirectory(name, this->self);
    this->children.insert_or_assign(name, file);

    return(file);
}

std::shared_ptr<File> Directory::getFile(const std::string &name) {
    return(std::dynamic_pointer_cast<File>(this->get(name)));
}

bool Directory::remove(const std::string &name) {
    if(debug) std::cout << "Directory::remove, name: " << name << std::endl;

    if(name == (".") || name == (".."))
        return(false);

    auto item = this->get(name);

    // verifico se se esiste
    if(item == nullptr) return(false);
    if(debug) std::cout << "Directory::remove, object found!" << std::endl;

    // rimuovo
    this->children.extract(item->getName()); // rimuovo dalla mappa
    item.reset(); // distruggo l'oggetto originale >> in automatico si distruggono gli eventuali sotto oggetti

    return(true);
}

int Directory::mType() const {
    return(Directory_type);
}
