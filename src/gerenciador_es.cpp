#include "gerenciador_es.hpp"
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <vector>
#include <cstdlib>

std::ifstream t("file.txt");

// construtor
GerenciadorES::GerenciadorES() {

}
// destrutor
GerenciadorES::~GerenciadorES() {

}

void GerenciadorES::imprimeDistanciaPercorrida(std::string nomeArquivo )
{   
    // Lendo arquivo de texto
    std::ifstream streamArquivo(nomeArquivo);
    std::string entradaLida(
        (std::istreambuf_iterator<char>(streamArquivo)),
            std::istreambuf_iterator<char>());

    // Divide números em vetores correspondentes
    std::string s = entradaLida;
    std::string delimitador = "\n";

    size_t pos = 0;
    std::vector<int> enderecosCilindrosListados;
    std::string token;
    int numero_token, ultimo_endereco_visitado;
    int distancia_fcfs, distancia_sstf, distancia_scan;
    int tamanho_disco;

    while ((pos = s.find(delimitador)) != std::string::npos) {
        token = s.substr(0, pos);
        numero_token = atoi(token.c_str());
        enderecosCilindrosListados.push_back(numero_token);
        s.erase(0, pos + delimitador.length());
    }
    numero_token = atoi(s.c_str());
    enderecosCilindrosListados.push_back(numero_token);
    tamanho_disco = enderecosCilindrosListados.at(0);
    enderecosCilindrosListados.erase(enderecosCilindrosListados.begin());
    // Calculando distancia FCFS
    distancia_fcfs = 0;
    ultimo_endereco_visitado = -1;
    for(std::vector<int>::iterator it = enderecosCilindrosListados.begin();
    it != enderecosCilindrosListados.end(); 
     ++it) {
        numero_token = *it;
        if( ultimo_endereco_visitado == -1)
        {
            ultimo_endereco_visitado = numero_token;
        } else {
            distancia_fcfs += abs(numero_token - ultimo_endereco_visitado);
            ultimo_endereco_visitado = numero_token;
        }
    }

  
    std::cout << "FCFS\t" << distancia_fcfs << std::endl;
}