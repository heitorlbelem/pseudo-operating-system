#ifndef escalonador_hpp
#define escalonador_hpp

#include <bits/stdc++.h>

using namespace std;
class escalonador {
    private:
        vector<pair<int, int>> lista_processos;
    public:
    escalonador(); // construtor
    ~escalonador(); // destrutor

    void set_lista_processos(vector<pair<int, int>>);
    vector<pair<int, int>> get_lista_processos(void);
    void le_arquivo_entrada(string);
    
};



#endif