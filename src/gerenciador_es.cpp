#include "gerenciador_es.hpp"
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <bits/stdc++.h>
#include <algorithm>

std::ifstream t("file.txt");

// construtor
GerenciadorES::GerenciadorES() {

}
// destrutor
GerenciadorES::~GerenciadorES() {

}

void GerenciadorES::imprimeDistanciaPercorrida(std::string nome_arquivo )
{   
    // Lendo arquivo de texto
    std::ifstream stream_arquivo(nome_arquivo);
    std::string entrada_lida(
        (std::istreambuf_iterator<char>(stream_arquivo)),
            std::istreambuf_iterator<char>());

    // Divide números em vetores correspondentes
    std::string s = entrada_lida;
    std::string delimitador = "\n";

    size_t pos = 0;
    std::vector<int> enderecos_cilindros_listados;
    std::vector<int> enderecos_sstf, enderecos_scan;
    std::string palavra_temporaria;
    int numero_temporario;
    int distancia_fcfs, distancia_sstf, distancia_scan;
    int tamanho_disco;

    while ((pos = s.find(delimitador)) != std::string::npos) {
        palavra_temporaria = s.substr(0, pos);
        numero_temporario = atoi(palavra_temporaria.c_str());
        enderecos_cilindros_listados.push_back(numero_temporario);
        s.erase(0, pos + delimitador.length());
    }
    numero_temporario = atoi(s.c_str());
    enderecos_cilindros_listados.push_back(numero_temporario);

    tamanho_disco = enderecos_cilindros_listados.at(0);
    enderecos_cilindros_listados.erase(enderecos_cilindros_listados.begin());

    // Calculando distancia FCFS
    distancia_fcfs = calculaDistanciaPercorrida(enderecos_cilindros_listados);

    // Ordenando endereços como SSFT
    ordenaSSTF(enderecos_sstf, enderecos_cilindros_listados);

    // Calculando distancia SSFT
    distancia_sstf = calculaDistanciaPercorrida(enderecos_sstf);

    // Ordenando endereços como SCAN
    ordenaSCAN(enderecos_scan, enderecos_cilindros_listados);

    // Calculando distancia SSFT
    distancia_scan = calculaDistanciaPercorrida(enderecos_scan);
    
    std::cout << "FCFS\t" << distancia_fcfs << std::endl;
    std::cout << "SSTF\t" << distancia_sstf << std::endl;
    std::cout << "SCAN\t" << distancia_scan << std::endl;
}


int calculaDistanciaPercorrida(std::vector<int> vector_caminho_percorrido)
{
    int distancia_percorrida = 0;
    int endereco_cilindro_atual;
    int ultimo_endereco_visitado = -1;

    for(std::vector<int>::iterator it = vector_caminho_percorrido.begin();
        it != vector_caminho_percorrido.end(); 
        ++it) {
        endereco_cilindro_atual = *it;
        if( ultimo_endereco_visitado == -1)
        {
            ultimo_endereco_visitado = endereco_cilindro_atual;
        } else {
            distancia_percorrida += abs(endereco_cilindro_atual - ultimo_endereco_visitado);
            ultimo_endereco_visitado = endereco_cilindro_atual;
        }
    }
    return distancia_percorrida;

}


void ordenaSSTF(std::vector<int>& vector_ordenado, std::vector<int> vector_entrada )
{   
    int ultimo_endereco_avaliado, ultima_distancia_medida, endereco_menor_distancia;
    int distancia_medida;
    std::vector<int>::iterator ultimo_iterador_escolhido;
    std::vector<int> vector_enderecos_temporario;

    vector_enderecos_temporario = vector_entrada;
    vector_enderecos_temporario.erase(vector_enderecos_temporario.begin());

    ultimo_endereco_avaliado = *vector_entrada.begin();
    vector_ordenado.push_back(ultimo_endereco_avaliado);

    for(std::size_t i=1; i < vector_entrada.size(); ++i) {
        ultima_distancia_medida = -1;
        endereco_menor_distancia = -1;

        for(std::vector<int>::iterator it_endereco_comparado = vector_enderecos_temporario.begin();
            it_endereco_comparado != vector_enderecos_temporario.end(); 
            ++it_endereco_comparado) {
            distancia_medida = abs(*it_endereco_comparado - ultimo_endereco_avaliado);
            if(ultima_distancia_medida > distancia_medida || ultima_distancia_medida == -1)
            {   
                ultimo_iterador_escolhido = it_endereco_comparado;
                endereco_menor_distancia = *it_endereco_comparado;
                ultima_distancia_medida = distancia_medida;
            }
        }
        vector_enderecos_temporario.erase(ultimo_iterador_escolhido);
        ultimo_endereco_avaliado = endereco_menor_distancia;
        vector_ordenado.push_back(endereco_menor_distancia);
    }
}


void ordenaSCAN(std::vector<int>& vector_ordenado, std::vector<int> vector_entrada )
{
    std::vector<int>::iterator it_endereco_inicial;
    int endereco_inicial = *vector_entrada.begin();

    sort(vector_entrada.begin(), vector_entrada.end());
    it_endereco_inicial = find(vector_entrada.begin(), vector_entrada.end(), endereco_inicial)+1;
    sort(vector_entrada.begin(), it_endereco_inicial, std::greater<int>());
    vector_entrada.insert(it_endereco_inicial, 0);
    vector_ordenado = vector_entrada;
}