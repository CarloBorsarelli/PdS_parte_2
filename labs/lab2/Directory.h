//
// Created by paolo on 27/04/20.
//

#ifndef LAB2_DIRECTORY_H
#define LAB2_DIRECTORY_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include "Base.h"
#include "File.h"


class Directory: public std::enable_shared_from_this<Directory>, public Base {
    std::string name;
    std::weak_ptr<Directory> parent;
    std::weak_ptr<Directory> self;
    std::unordered_map<std::string, std::shared_ptr<Base>> children;

protected:
    static std::shared_ptr<Directory> root;

    explicit Directory(std::string name);
    std::shared_ptr<Directory> getThis();
    static std::shared_ptr<Directory> makeDirectory(std::string name, std::weak_ptr<Directory> parent); // named constructor

public:
    static std::shared_ptr<Directory> getRoot();
    std::shared_ptr<Directory> addDirectory(const std::string& name);
    std::shared_ptr<File> addFile(const std::string& name, uintmax_t size);
    std::shared_ptr<Base> get(const std::string& name);
    std::shared_ptr<Directory> getDir(const std::string& name);
    std::shared_ptr<File> getFile(const std::string& name);
    bool remove(const std::string& name);

    void ls(int indent=4, int total_indent=0) const override;
    int mType() const override;

    ~Directory();
};

#endif //LAB2_DIRECTORY_H
