/*
 * L05
 * 27-03-2020
 * */
#include <iostream>
#include <string>
#include <vector>

class intArray{
    std::size_t mSize;
    int *mArray;
public:
    // costruttore
    intArray(std::size_t size=0): mSize(size), mArray(mSize? new int[mSize]:nullptr){}

    // costruttore di copia
    intArray(const intArray &that): mSize(that.mSize), mArray(mSize? new int[mSize]:nullptr){
        std::copy(that.mArray, that.mArray+mSize, mArray);
    }

    // distruttore
    ~intArray(){delete[] mArray;}

    // funzione di copia (ridefinita dopo)
    /*intArray &operator=(const intArray &that){
        if(this != &that){
            delete(mArray);
            mArray = nullptr;
            mSize = that.mSize;
            mArray = new int[mSize];
            std::copy(that.mArray, that.mArray+mSize, mArray);
        }
        return(*this);
    }*/

    // copy&swap
    friend void swap(intArray &a, intArray &b){
        std::swap(a.mSize, b.mSize);
        std::swap(a.mArray, b.mArray);
    }

    // funzione di copia
    intArray &operator=(intArray that){
        swap(*this, that);
        return(*this);
    }

    // costruttore di movimento
    intArray(intArray &&that): mSize(0), mArray(nullptr){
        swap(*this, that);
    }
};

void print_vector(const std::vector<std::string> &v){
    std::cout<<"[ ";
    for(auto s: v)
        std::cout<<s<<" ";
    std::cout<<"]"<<std::endl;
}

int main(){
    std::vector<std::string> v;
    print_vector(v);

    std::string s = "abc";
    v.push_back(s);
    print_vector(v);
    std::cout<<"prima della move: s: "<<s<<std::endl;

    v.push_back(std::move(s));
    print_vector(v);
    std::cout<<"dopo la move: s: "<<s<<std::endl;

    return(0);
}