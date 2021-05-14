#ifndef gerenciador_memoria_hpp
#define gerenciador_memoria_hpp

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class GerenciadorMemoria {
    private: 
    int tamanhoMemoria; 

    public:
    GerenciadorMemoria();
    ~GerenciadorMemoria();

    void imprimeFaltaDePagina(std::string);
};

int fifo(std::vector<int>);

int secondChance(std::vector<int>);

int lru(std::vector<int>);


#endif