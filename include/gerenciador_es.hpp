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
    void imprimeDistanciaPercorrida(std::string);
};

int calculaDistanciaPercorrida(std::vector<int>);
void ordenaSSTF(std::vector<int>& , std::vector<int>);
#endif