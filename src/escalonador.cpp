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

arquivo_saida escalonador::get_arquivo_saida()
{
    return texto_saida;
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

void escalonador::set_arquivo_saida(arquivo_saida arq)
{
    texto_saida = arq;
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
    string linha_temp;
    vector<string> arq_temp;
    arquivo_saida saida;
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
        //cout << topo_fila.chegada << " " << topo_fila.duracao << endl;
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
        linha_temp = "Rodou processo[" + to_string(processos_finalizados[i].id) + "] de [" + to_string(processos_finalizados[i].inicio_execucao) +"] ate [" + to_string(processos_finalizados[i].final_execucao) +"]" ;
        //cout << linha_temp << endl;
        arq_temp.push_back(linha_temp);
    }
    st_fifo.turnaround = st_fifo.turnaround/processos_finalizados.size();
    soma = soma/processos_finalizados.size();

    // no caso do fifo essas duas variaveis sao iguais
    st_fifo.tempo_medio_resposta = soma;
    st_fifo.tempo_medio_espera = soma;

    // atualiza estrutura de estatisticas do escalonador
    set_est_fifo(st_fifo);
    //cout << st_fifo.turnaround << " " << st_fifo.tempo_medio_resposta << " " << st_fifo.tempo_medio_espera << endl;
    // escreve o historico de execucao dos processos
    saida = get_arquivo_saida();
    saida.saida_fifo = arq_temp;
    // atualiza a estutura do escalonador
    set_arquivo_saida(saida);

}


void escalonador::sjf(void)
{
    int tempo_execucao = 0;
    processo p_temp, topo_fila;
    double soma, espera, duracao, resposta = 0;
    vector<processo> processos_finalizados;
    estatisticas_processos st_sjf;
    priority_queue<processo, vector<processo>, compare_fifo> pq;
    priority_queue<processo, vector<processo>, compare_sjf> fila_sjf;
    string linha_temp;
    vector<string> arq_temp;
    arquivo_saida saida;
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
            // verifica se o proximo processo da fila ja chegou para execucao (tempo total de execucao >= tempo de chegada do processo)
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
        // remove o processo da fila apos sua execucao
        fila_sjf.pop();
        // adiciona o tempo de execucao para o tempo total de processamento
        tempo_execucao += p_temp.duracao;
        p_temp.final_execucao = tempo_execucao;
        // adiciona o processo para a lista de processos ja finalizados
        processos_finalizados.push_back(p_temp);  

    }
    duracao = 0;
    espera = 0;
    for(int i=0; i<processos_finalizados.size(); i++) {
        espera += (processos_finalizados[i].final_execucao - processos_finalizados[i].chegada - processos_finalizados[i].duracao);
        duracao += processos_finalizados[i].final_execucao - processos_finalizados[i].chegada;
        resposta += (processos_finalizados[i].inicio_execucao - processos_finalizados[i].chegada);
        linha_temp = "Rodou processo[" + to_string(processos_finalizados[i].id) + "] de [" + to_string(processos_finalizados[i].inicio_execucao) +"] ate [" + to_string(processos_finalizados[i].final_execucao) +"]" ;
        //st_sjf.turnaround += (processos_finalizados[i].final_execucao - processos_finalizados[i].chegada);
        //cout << processos_finalizados[i].inicio_execucao << " " << processos_finalizados[i].final_execucao << endl;
        arq_temp.push_back(linha_temp);
    }
    // calculando as estatísticas do sjf
    espera = espera/processos_finalizados.size();
    duracao = duracao/processos_finalizados.size();
    resposta = resposta/processos_finalizados.size();
    st_sjf.tempo_medio_espera = espera;
    st_sjf.turnaround = duracao;
    st_sjf.tempo_medio_resposta = resposta;
    set_est_sjf(st_sjf);
    //cout << st_sjf.turnaround << " " << st_sjf.tempo_medio_resposta << " " << st_sjf.tempo_medio_espera << endl;

    // escreve o historico de execucao dos processos
    saida = get_arquivo_saida();
    saida.saida_sjf = arq_temp;
    // atualiza a estutura do escalonador
    set_arquivo_saida(saida);
    
}

void escalonador::roundrobin(int quantum)
{
    int tempo_execucao = 0;
    processo p_temp, topo_fila;
    double soma=0, espera=0, duracao=0, resposta = 0;
    vector<processo> processos_finalizados;
    estatisticas_processos st_rr;
    priority_queue<processo, vector<processo>, compare_fifo> pq;
    queue<processo> fila_rr;
    string linha_temp;
    vector<string> arq_temp;
    arquivo_saida saida;
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
     while(1) {
        while( !(pq.empty()) ) {
            // loop para tratar os processos que chegam ao longo do tempo
            topo_fila = pq.top();
            // verifica se o proximo processo da fila ja chegou para execucao (tempo total de execucao >= tempo de chegada do processo)
            if( topo_fila.chegada <= tempo_execucao ) {
                fila_rr.push(topo_fila);
                //cout << topo_fila.chegada << " " << topo_fila.duracao << endl;
                pq.pop();
            }
            else {
                // sai do loop dos elementos que estao para chegar
                break;
            }
        }
        // caso a fila esteja vazia deve encerrar o loop
        if(fila_rr.empty())
            break;

        p_temp = fila_rr.front();
        // verifica se eh o inicio da exec do processo
        if(p_temp.inicio_execucao == -1) {
            p_temp.inicio_execucao = tempo_execucao;
        }
        // remove o elemento da fila
        fila_rr.pop();
        // verifica se o processo vai executar pela duracao total do quantum
        if(p_temp.restante >= quantum) {
            linha_temp = "Rodou processo[" + to_string(p_temp.id) + "] de [" + to_string(tempo_execucao) +"] ate [" + to_string(tempo_execucao+quantum) +"]" ;
            p_temp.restante -= quantum;
            tempo_execucao += quantum;
        }
        else {
            linha_temp = "Rodou processo[" + to_string(p_temp.id) + "] de [" + to_string(tempo_execucao) +"] ate [" + to_string(tempo_execucao+p_temp.restante) +"]" ;
            tempo_execucao += p_temp.restante;
            p_temp.restante = 0;
        }
        arq_temp.push_back(linha_temp);
        // caso ja tenha executado o processo ate o fim, nao o coloca na fila de pronto novamente
        if(p_temp.restante != 0)
            fila_rr.push(p_temp);
        else {
            p_temp.final_execucao = tempo_execucao;
            // adiciona o processo aos finalizados
            processos_finalizados.push_back(p_temp);
        }
         
    }
    // gera as estatisticas
    for(int i=0; i<processos_finalizados.size(); i++) {
        espera += (processos_finalizados[i].final_execucao - processos_finalizados[i].chegada - processos_finalizados[i].duracao);
        duracao += processos_finalizados[i].final_execucao - processos_finalizados[i].chegada;
        resposta += (processos_finalizados[i].inicio_execucao - processos_finalizados[i].chegada);
        
    }
    espera = espera/processos_finalizados.size();
    duracao = duracao/processos_finalizados.size();
    resposta = resposta/processos_finalizados.size();
    st_rr.tempo_medio_espera = espera;
    st_rr.turnaround = duracao;
    st_rr.tempo_medio_resposta = resposta;
    set_est_rr(st_rr);
    // escreve o historico de execucao dos processos
    saida = get_arquivo_saida();
    saida.saida_rr = arq_temp;
    // atualiza a estutura do escalonador
    set_arquivo_saida(saida);
}

void escalonador::escreve_historico_processos()
{
    arquivo_saida historico;
    // Cria e abre o arquivo para escrita
    ofstream MyFile("historico_processos.txt");

    // Recupera a informacao sobre os arquivos
    historico = get_arquivo_saida();
    // escfrita do fifo
    MyFile << "FIFO:\n";
    for(int i=0; i<historico.saida_fifo.size(); i++)
        MyFile << historico.saida_fifo[i] << "\n";

    // escrita do sjf
    MyFile << "\nSJF:\n";
    for(int i=0; i<historico.saida_sjf.size(); i++)
        MyFile << historico.saida_sjf[i] << "\n";
    
    // escrita do round robin
    MyFile << "\nRound Robin:\n";
    for(int i=0; i<historico.saida_rr.size(); i++)
        MyFile << historico.saida_rr[i] << "\n";
    // Close the file
    MyFile.close();
}

void escalonador::mostra_estatisticas()
{
    cout << "FIFO "<<est_fifo.turnaround << " " << est_fifo.tempo_medio_resposta << " " << est_fifo.tempo_medio_espera << endl;
    cout << "SJF "<<est_sjf.turnaround << " " << est_sjf.tempo_medio_resposta << " " << est_sjf.tempo_medio_espera << endl;
    cout << "ROUND ROBIN "<<est_rr.turnaround << " " << est_rr.tempo_medio_resposta << " " << est_rr.tempo_medio_espera << endl;
}