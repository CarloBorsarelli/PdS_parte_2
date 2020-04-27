//
// Created by paolo on 27/04/20.
//

#ifndef LAB2_DIRECTORY_H
#define LAB2_DIRECTORY_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>


class Directory: public std::enable_shared_from_this<Directory>{
    std::string name;
    std::weak_ptr<Directory> parent;
    std::weak_ptr<Directory> self;
    std::unordered_map<std::string, std::shared_ptr<Directory>> children;

protected:
    static std::shared_ptr<Directory> root;

    explicit Directory(std::string name);
    void ls_recursive(int indent_step, int total_indent) const;
    std::shared_ptr<Directory> getThis();

public:
    void ls(int indent=4) const;
    std::shared_ptr<Directory> get(std::string name);

    std::shared_ptr<Directory> addDirectory(std::string name);

    static std::shared_ptr<Directory> makeDirectory(std::string name, std::weak_ptr<Directory> parent); // named constructor
    static std::shared_ptr<Directory> getRoot();

    ~Directory();
};

#endif //LAB2_DIRECTORY_H
