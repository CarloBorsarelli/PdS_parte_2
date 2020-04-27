#include <iostream>
#include <vector>
#include <string>
#include <memory>

/*
L08
24-04-2020
*/

/*
template<typename T>
const T& my_max(const T& t1, const T& t2){
	return(t1 < t2 ? t1:t2);
}

int i = my_max(4, 5);

std::string s1 = "alpha";
std::string s2 = "beta";
std::string s3 = my_max(s1, s2);

int j = my_max<double>(i, 7.2);
 */

template<typename T>
class Accum{
    T total;
public:
    Accum(T t): total(t) { }
    T operator+=(const T& t) {
        return total = total+t;
    }
    T value() { return total; }
};

int f1(){
    Accum<int> a1{0};
    a1 += 5;
    a1 += 7;
    a1 += 23;

    return(a1.value());
}

std::wstring f2(){
    Accum<std::wstring> a1{L""};
    a1 += L"alpha";
    a1 += L"beta";
    a1 += L"gamma";

    return(a1.value());
}

int main_old() {
    /* con int */
    std::vector<int> v;

    for(int i=0; i<10; i++)
        v.push_back(i*i);

    for(int i=0; i<20; i++)
        v.push_back(i);
    std::cout << "v contiene " << v.size() << " elementi" << std::endl;

    /*
    std::cout << "alla posizione 50 c'è il valore " << v[50] << std::endl;
    std::cout << "alla posizione 2999 c'è il valore " << v[2999] << std::endl;
     */

    for(int i=0; i<20; i++)
        v.push_back(i);
    std::cout << "v contiene " << v.size() << " elementi" << std::endl;


    v.clear(); // rimuovo tutti gli elementi

    /* con string */
    std::vector<std::string> v2;
    for(int i=0; i<10; i++) {
        v2.push_back("s" + std::to_string(i * i));
    }

    for(int i=0; i<20; i++){}

    /*
     * con bool
     * ma posso ottimizzarlo
     */
    std::vector<bool> v3;

    for(int i=0; i<10; i++) {
        v3.push_back(false);
    }

    return 0;
}
