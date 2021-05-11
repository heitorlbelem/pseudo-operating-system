#include "escalonador.hpp"
// construtor
escalonador::escalonador() {

}
// destrutor
escalonador::~escalonador() {

}

// metodos GET

vector<pair<int, int>> escalonador::get_lista_processos()
{
    return lista_processos;
}

// metodos SET

void escalonador::set_lista_processos(vector<pair<int, int>> lista)
{
    lista_processos = lista;
    return;
}

// metodos diversos

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

void escalonador::fifo()
{
    int tempo_espera = 0;
    int temp_execucao = 0;
    vector<processo> processos_finalizados;
    processo p_temp;
    estatisticas_processos est_fifo;

    // definindo a estrutura de dados que vai ordenar por ordem de chegada
    // nao importando a duracao do processo
    queue<processo> pq;
    //priority_queue<processo, vector<processo>, compare_fifo> pq;
    processo topo_fila;
    // insere os elementos na fila para serem escalonados
    for(int i=0; i<lista_processos.size(); i++) {
        p_temp.chegada = lista_processos[i].first;
        p_temp.duracao = lista_processos[i].second;
        p_temp.inicio_execucao = 0;
        p_temp.final_execucao = 0;
        p_temp.id = i;
        pq.push(p_temp);
    }

    while( !(pq.empty()) ) {
        topo_fila = pq.front();
        cout << topo_fila.chegada << " " << topo_fila.duracao << endl;
        // atualiza o tmepo do inicio da execucao do processo
        topo_fila.inicio_execucao = temp_execucao;
        // executa o processo
        temp_execucao += topo_fila.duracao;
        // atualiza o tempo de termino
        topo_fila.final_execucao = temp_execucao;
        pq.pop();
        processos_finalizados.push_back(topo_fila);
    }

    // calculo das estatisticas
    est_fifo.turnaround = temp_execucao;
    double soma = 0;
    for(int i=0; i<processos_finalizados.size(); i++) {
        soma += (processos_finalizados[i].inicio_execucao - processos_finalizados[i].chegada);
        //cout << soma << endl;
        //cout << processos_finalizados[i].inicio_execucao << " " << processos_finalizados[i].chegada << endl;
    }
    soma = soma/processos_finalizados.size();

    // no caso do fifo essas duas variaveis sao iguais
    est_fifo.tempo_medio_resposta = soma;
    est_fifo.tempo_medio_espera = soma;

    // atualiza estrutura de estatisticas do escalonador

    cout << est_fifo.turnaround << " " << est_fifo.tempo_medio_resposta << " " << est_fifo.tempo_medio_espera << endl;

}