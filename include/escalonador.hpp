#ifndef escalonador_hpp
#define escalonador_hpp

#include <bits/stdc++.h>

using namespace std;

struct processo {
    int chegada;
    int duracao;
    int inicio_execucao;
    int final_execucao;
    int id;
    int restante;
};

struct estatisticas_processos {
    double turnaround;
    double tempo_medio_resposta;
    double tempo_medio_espera;
};

class escalonador {
    private:
        vector<pair<int, int>> lista_processos;
        estatisticas_processos est_fifo;
        estatisticas_processos est_sjf;
        estatisticas_processos est_rr;
    public:
    escalonador(); // construtor
    ~escalonador(); // destrutor
    // metodos GET
    vector<pair<int, int>> get_lista_processos(void);
    estatisticas_processos get_est_fifo();
    estatisticas_processos get_est_sjf();
    estatisticas_processos get_est_rr();

    // metodos SET
    void set_lista_processos(vector<pair<int, int>>);
    void set_est_fifo(estatisticas_processos);
    void set_est_sjf(estatisticas_processos);
    void set_est_rr(estatisticas_processos);
    // metodos diversos
    void fifo();
    void le_arquivo_entrada(string);
    void sjf(void);
    void sjf_preemptivo(void);
    
};

struct compare_fifo {
    bool operator()(processo const& p1, processo const& p2)
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        return p1.chegada > p2.chegada;
    }
};

struct compare_sjf {
    bool operator()(processo const& p1, processo const& p2)
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        return p1.duracao > p2.duracao;
    }
};



#endif