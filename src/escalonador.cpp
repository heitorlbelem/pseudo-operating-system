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

estatisticas_processos escalonador::get_est_fifo()
{
    return est_fifo;
}

estatisticas_processos escalonador::get_est_sjf()
{
    return est_sjf;
}

estatisticas_processos escalonador::get_est_rr()
{
    return est_rr;
}

// metodos SET

void escalonador::set_lista_processos(vector<pair<int, int>> lista)
{
    lista_processos = lista;
    return;
}

void escalonador::set_est_fifo(estatisticas_processos est)
{
    est_fifo = est;
}

void escalonador::set_est_sjf(estatisticas_processos est)
{
    est_sjf = est;
}

void escalonador::set_est_rr(estatisticas_processos est)
{
    est_rr = est;
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
    int temp_execucao = 0;
    vector<processo> processos_finalizados;
    processo p_temp;
    estatisticas_processos st_fifo;

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
        if( topo_fila.chegada > temp_execucao)
            temp_execucao = topo_fila.chegada;
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
    st_fifo.turnaround = 0;
    double soma = 0;
    for(int i=0; i<processos_finalizados.size(); i++) {
        soma += (processos_finalizados[i].inicio_execucao - processos_finalizados[i].chegada);
        st_fifo.turnaround += (processos_finalizados[i].final_execucao - processos_finalizados[i].chegada);
        //cout << soma << endl;
        //cout << processos_finalizados[i].inicio_execucao << " " << processos_finalizados[i].chegada << endl;
    }
    st_fifo.turnaround = st_fifo.turnaround/processos_finalizados.size();
    soma = soma/processos_finalizados.size();

    // no caso do fifo essas duas variaveis sao iguais
    st_fifo.tempo_medio_resposta = soma;
    st_fifo.tempo_medio_espera = soma;

    // atualiza estrutura de estatisticas do escalonador
    set_est_fifo(st_fifo);
    cout << st_fifo.turnaround << " " << st_fifo.tempo_medio_resposta << " " << st_fifo.tempo_medio_espera << endl;

}


void escalonador::sjf(void)
{
    int tempo_execucao = 0;
    processo p_temp, topo_fila;
    double soma;
    vector<processo> processos_finalizados;
    priority_queue<processo, vector<processo>, compare_fifo> pq;
    priority_queue<processo, vector<processo>, compare_sjf> fila_sjf;
    // preenche a primeira fila de prioridade, ordenada pela ordem de chegada
    for(int i=0; i<lista_processos.size(); i++) {
        p_temp.chegada = lista_processos[i].first;
        p_temp.duracao = lista_processos[i].second;
        p_temp.restante = lista_processos[i].second;
        p_temp.inicio_execucao = -1;
        p_temp.final_execucao = 0;
        p_temp.id = i;
        pq.push(p_temp);
    }

    // uma vez preenchida essa fila, deve-se preencher a fila do sjf
    // so podem ser adicionados os processos com chegada menor ou igual ao tempo atual
    int proxima_chegada;
    while(1) {
        while( !(pq.empty()) ) {
            // loop para tratar os processos que chegam ao longo do tempo
            topo_fila = pq.top();
            if( topo_fila.chegada <= tempo_execucao ) {
                fila_sjf.push(topo_fila);
                pq.pop();
            }
            else {
                // proximo elemento a entrar na fila
                proxima_chegada = topo_fila.chegada;
                // sai do loop dos elementos que estao para chegar
                break;
            }
        }
        // caso a fila esteja vazia deve encerrar o loop
        if(fila_sjf.empty())
            break;

        p_temp = fila_sjf.top();
        // verifica se eh o inicio da exec do processo
        if(p_temp.inicio_execucao == -1) {
            p_temp.inicio_execucao = tempo_execucao;
        }
        fila_sjf.pop();
        tempo_execucao += p_temp.duracao;
        p_temp.final_execucao = tempo_execucao;
        processos_finalizados.push_back(p_temp);  

    }
    for(int i=0; i<processos_finalizados.size(); i++) {
        soma += (processos_finalizados[i].final_execucao - processos_finalizados[i].chegada - processos_finalizados[i].duracao);
        //st_fifo.turnaround += (processos_finalizados[i].final_execucao - processos_finalizados[i].chegada);
        cout << processos_finalizados[i].inicio_execucao << " " << processos_finalizados[i].final_execucao << endl;
    }
    soma = soma/processos_finalizados.size();
    cout << soma << endl;
}