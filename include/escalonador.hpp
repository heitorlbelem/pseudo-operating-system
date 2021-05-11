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

    // metodos diversos
    void fifo();
    
};

struct processo {
    int chegada;
    int duracao;
    int inicio_execucao;
    int final_execucao;
    int id;
};

struct estatisticas_processos {
    int turnaround;
    double tempo_medio_resposta;
    double tempo_medio_espera;
};

struct compare_fifo {
    bool operator()(processo const& p1, processo const& p2)
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        return p1.chegada > p2.chegada;
    }
};



#endif