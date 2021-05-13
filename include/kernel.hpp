#ifndef kernel_hpp
#define kernel_hpp

#include <bits/stdc++.h>
#include "escalonador.hpp"
#include "gerenciador_es.hpp"

using namespace std;

class kernel {
    private:
    /* identifica qual o modo de operacao o kernel esta
     * 0 -> inicializado, ainda nao foi alterado
     * 1 -> Escalonamento de processos
     * 2 -> Gerenciamento de Memoria
     * 3 -> Gerenciamento de E/S
     */
    escalonador esc;
    /* Simula o funcionamento de algoritmos de gerencia de disco
    */
    GerenciadorES gerenciadorES_;
    int modo_operacao;
    public:
    kernel(); // construtor
    ~kernel(); // destrutor
    // metodos GET
    escalonador get_escalonador(void);
    GerenciadorES gerenciadorES(void);
    int get_modo_operacao();
    // metodos SET
    void set_modo_operacao(int);
    void set_escalonador(escalonador);
    void setGerenciadorES(GerenciadorES);
    // metodos diversos
    void verifica_entrada(int , string);
    void verifica_modo_op(void);
    void gerencia_processos();
};


#endif