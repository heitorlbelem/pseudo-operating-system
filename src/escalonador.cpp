#include "escalonador.hpp"
// construtor
escalonador::escalonador() {

}
// destrutor
escalonador::~escalonador() {

}

void escalonador::le_arquivo_entrada(string arquivo)
{
    string linha;
    int a, b;
    pair<int, int> par_temp;
    vector<pair<int, int>> lista_temp;
    ifstream MyFile(arquivo);
    // le o arquivo de entrada
    while(getline(MyFile, linha)) {
        istringstream iss(linha);
        iss >> a >> b;
        par_temp = make_pair(a, b);
        lista_temp.push_back(par_temp);

    }
    // ao final da leitura do arquivo passa a lista para o objeto
    set_lista_processos(lista_temp);
    MyFile.close();
}

vector<pair<int, int>> escalonador::get_lista_processos()
{
    return lista_processos;
}

void escalonador::set_lista_processos(vector<pair<int, int>> lista)
{
    lista_processos = lista;
    return;
}