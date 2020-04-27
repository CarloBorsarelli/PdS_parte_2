//
// Created by paolo on 28/03/20.
//

class Buffer{
    int size;
    int *vet;
    int maxPos = 0;

public:
    Buffer(int size): size(size){
        vet = new int[size];
    }

    int getSize() const {return size;}

    bool getData(int pos, int &val){
        if(pos<0 || pos>=maxPos)
            return(false);
        val = vet[pos];
        return(true);
    }

    // aggiungere

    ~Buffer(){
        delete(vet);
    }

};
