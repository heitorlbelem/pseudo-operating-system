#ifndef kernel_hpp
#define kernel_hpp

#include <bits/stdc++.h>
#include "escalonador.hpp"
using namespace std;

class kernel {
    private:
    escalonador esc;
    public:
    kernel(); // construtor
    ~kernel(); // destrutor
    escalonador get_escalonador(void);
    void set_escalonador(escalonador);
    void verifica_entrada(int , string);
};


#endif