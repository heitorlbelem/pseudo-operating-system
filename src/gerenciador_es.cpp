#include "gerenciador_es.hpp"
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <vector>

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
    int numeroToken;
    while ((pos = s.find(delimitador)) != std::string::npos) {
        token = s.substr(0, pos);
        numeroToken = atoi(token.c_str());
        enderecosCilindrosListados.push_back(numeroToken);
        s.erase(0, pos + delimitador.length());
    }
    numeroToken = atoi(s.c_str());
    enderecosCilindrosListados.push_back(numeroToken);
    std::cout << enderecosCilindrosListados.size() << std::endl;

}