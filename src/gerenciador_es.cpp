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
    std::vector<int> enderecosCilindrosListados, enderecosTemporarios;
    std::vector<int> enderecosSSTF;
    std::string token;
    int numero_token, ultimo_endereco_visitado, ultima_distancia_medida;
    int endereco_menor_distancia;
    int distancia_fcfs, distancia_sstf, distancia_scan, distancia_medida;
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

    // Ordenando endereços como SSFT
    std::vector<int>::iterator ultimo_iterador_escolhido;
    enderecosTemporarios = enderecosCilindrosListados;
    enderecosTemporarios.erase(enderecosTemporarios.begin());

    numero_token = *enderecosCilindrosListados.begin();
    enderecosSSTF.push_back(numero_token);

    for(std::size_t i=1; i < enderecosCilindrosListados.size(); ++i) {
        ultima_distancia_medida = tamanho_disco+1;
        endereco_menor_distancia = -1;

        for(std::vector<int>::iterator it_endereco_comparado = enderecosTemporarios.begin();
            it_endereco_comparado != enderecosTemporarios.end(); 
            ++it_endereco_comparado) {
            distancia_medida = abs(*it_endereco_comparado - numero_token);
            if(distancia_medida != 0 && ultima_distancia_medida > distancia_medida)
            {   
                ultimo_iterador_escolhido = it_endereco_comparado;
                endereco_menor_distancia = *it_endereco_comparado;
                ultima_distancia_medida = distancia_medida;
            }
        }
        enderecosTemporarios.erase(ultimo_iterador_escolhido);
        if(endereco_menor_distancia > -1)
        {
            numero_token = endereco_menor_distancia;
            enderecosSSTF.push_back(endereco_menor_distancia);
        }
        std::cout << "SSTF\t" << endereco_menor_distancia << std::endl;
    }

    // Calculando distancia SSFT
    distancia_sstf = 0;
    ultimo_endereco_visitado = -1;
    for(std::vector<int>::iterator it = enderecosSSTF.begin();
    it != enderecosSSTF.end(); 
     ++it) {
        numero_token = *it;
        if( ultimo_endereco_visitado == -1)
        {
            ultimo_endereco_visitado = numero_token;
        } else {
            distancia_sstf += abs(numero_token - ultimo_endereco_visitado);
            ultimo_endereco_visitado = numero_token;
        }
    }
    
    std::cout << "SSTF\t" << distancia_sstf << std::endl;
    std::cout << "FCFS\t" << distancia_fcfs << std::endl;
}