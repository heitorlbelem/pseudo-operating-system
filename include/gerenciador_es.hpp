#ifndef gerenciador_es_hpp
#define gerenciador_es_hpp
/* 
Neste módulo a equipe deve escrever um programa para simular o funcionamento dos principais algoritmos
de escalonamento de disco estudados na disciplina. Os algoritmos de escalonamento de disco a serem
implementados são os seguintes:
• FCFS (First Come, First Serve);
• SSF (ou SSTF – braço inicialmente para baixo);
• SCAN.
O programa deverá ler da entrada padrão um conjunto de número inteiros, no qual o primeiro número
representa a quantidade de cilindros no disco, o segundo número representa o cilindro sobre o qual a cabeça
de leitura do disco está inicialmente posicionada, e os demais representam uma sequência de requisições de
acesso a serem atendidas, sempre um número por linha.
O programa deverá imprimir na saída o número total de cilindros percorridos pela cabeça de leitura para
atender todas as requisições solicitadas utilizando cada um dos algoritmos. 
*/
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class GerenciadorES {
    
    private:
    int tamanhoDisco;
    public:
    GerenciadorES(); // construtor
    ~GerenciadorES(); // destrutor

    /* 
        Lê um arquivo no caminho de entrada com endereços de cilindros
        Imprime na tela distâncias percorridas com diferentes algoritmos.
    */
    void imprimeDistanciaPercorrida(std::string);
};

/*
    Percorre um vector de inteiros calculando a distancia entre cada endereço
    adjascente e retorna o total percorrido.
*/
int calculaDistanciaPercorrida(std::vector<int>);

/*
    Ordena sempre a requisição que precisar do menor
    deslocamento do braço, de forma a minimizar o tempo de seek
*/
void ordenaSSTF(std::vector<int>&, std::vector<int>);

/*
    Ordena continuamente para frente e para trás,
    atendendo aos pedidos na direção da movimentação de uma
    extremidade para a outra.
*/
void ordenaSCAN(std::vector<int>&, std::vector<int>);
#endif