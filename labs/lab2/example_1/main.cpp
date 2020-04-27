#include <iostream>
#include <memory>

class D {
    std::weak_ptr<D> parent;
    std::shared_ptr<D> child;
public:
    D(std::weak_ptr<D> parent): parent(parent){
        std::cout<<"D() @ "<<this<<std::endl;
    }
    std::shared_ptr<D> addChild(){
        std::shared_ptr<D> child= std::make_shared<D>(std::shared_ptr<D> (this));
        this->child = child;
        return child;
    }
    ~D(){
        std::cout<<"~D() @ "<<this<<std::endl;
    }
};

int main(){
    std::cout << "Creating root..." << std::endl;
    D root(std::shared_ptr<D>(nullptr));

    std::cout << "Creating a new child..." << std::endl;
    std::shared_ptr<D> child = root.addChild();
    std::cout << "child @" << child << std::endl;

    std::cout << "Program end" << std::endl;
    child.reset(); // errore: elemento già rilasciato
}