#include "gerenciador_es.hpp"
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>

std::ifstream t("file.txt");

// construtor
GerenciadorES::GerenciadorES() {
    
}
// destrutor
GerenciadorES::~GerenciadorES() {

}

void GerenciadorES::imprimeDistanciaPercorrida(std::string nomeArquivo )
{   std::ifstream streamArquivo(nomeArquivo);
    std::string entradaLida(
        (std::istreambuf_iterator<char>(streamArquivo)),
            std::istreambuf_iterator<char>());
    std::cout << entradaLida;
}