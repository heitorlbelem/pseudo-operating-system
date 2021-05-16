#ifndef kernel_hpp
#define kernel_hpp

#include <bits/stdc++.h>
#include "escalonador.hpp"
#include "gerenciador_es.hpp"
#include "gerenciador_mem.hpp"

using namespace std;

class kernel {
    private:
    /* identifica qual o modo de operacao o kernel esta
     * 0 -> inicializado, ainda nao foi alterado
     * 1 -> Escalonamento de processos
     * 2 -> Gerenciamento de Memoria
     * 3 -> Gerenciamento de E/S
     */
    int modo_operacao;
    escalonador esc;
    gerenciador_mem g_memoria;
    /* Simula o funcionamento de algoritmos de gerencia de disco
    */
    GerenciadorES gerenciadorES_;

    public:
    kernel(); // construtor
    ~kernel(); // destrutor
    
    // metodos GET
    int get_modo_operacao();
    escalonador get_escalonador(void);
    GerenciadorES gerenciadorES(void);
    gerenciador_mem get_gerenciador_mem(void);
    
    // metodos SET
    void set_modo_operacao(int);
    void set_escalonador(escalonador);
    void setGerenciadorES(GerenciadorES);
    void set_gerenciador_mem(gerenciador_mem);

    // metodos diversos
    void verifica_entrada(int , string);
    void verifica_modo_op(void);
    void gerencia_processos(void);
    void gerencia_memoria(void);
    void gerencia_es(void);
};


#endif