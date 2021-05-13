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
    distancia_fcfs = calculaDistanciaPercorrida(enderecosCilindrosListados);

    // Ordenando endereços como SSFT
    ordenaSSTF(enderecosSSTF, enderecosCilindrosListados);

    // Calculando distancia SSFT
    distancia_sstf = calculaDistanciaPercorrida(enderecosSSTF);
    
    std::cout << "SSTF\t" << distancia_sstf << std::endl;
    std::cout << "FCFS\t" << distancia_fcfs << std::endl;
}


/*
    Percorre um vector de inteiros calculando a distancia entre cada endereço
    adjascente e retorna o total percorrido.
*/
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

/*
    Ordena sempre a requisição que precisar do menor
    deslocamento do braço, de forma a minimizar o tempo de seek
*/
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