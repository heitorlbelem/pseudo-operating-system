#include "gerenciador_mem.hpp"

int find_sc(vector<pair<int, int>> &elements, int current) {

    pair<int, int> aux;
    // percorre todos os frames que estão na memória
    for(int i=0; i < elements.size(); i++) {

        // se encontrar a página na memória, atualiza o contador de referencias (bit R),
        // remove o elemento da atual posição e coloca no final da fila
        if(elements[i].first == current) {
            aux = make_pair(elements[i].first, 2);
            elements.erase(elements.begin());
            elements.push_back(aux);
            return -1;
        }

        // se não achar, decrementa o contador de referências (bit R) e reinsere a página
        // no final da fila
        if(elements[i].second > 0){
            elements[i].second--;
            aux = elements[i];
            elements.erase(elements.begin());
            elements.push_back(aux);
        }
    }

    return 0;

}

int find_lru(vector<pair<int,int>> &elements, int current) {
    
    int min, min_pos = 0;
    if(elements.size() > 0) {
        min = elements[0].second;
    }

    for(int i=0; i<elements.size(); i++) {
        // se achou a página, incrementa o contador de referencias dela e retorna
        if(elements[i].first == current) {
            elements[i].second++;
            return -1;
        }
        // se não achar, faz a comparação 1 a 1 ate achar a página que contem o menor numero de referencias
        // e então retorna a posição dela
        if(elements[i].second < min) {
            min = elements[i].second;
            min_pos = i;
        }
    }
    
    return min_pos;
}

gerenciador_mem::gerenciador_mem(){}

gerenciador_mem::~gerenciador_mem(){}

estatisticas_paginacao gerenciador_mem::get_estatisticas(){
    return this->estatisticas;
}

void gerenciador_mem::set_estatisticas(estatisticas_paginacao estat){
    this->estatisticas = estat;
}

void gerenciador_mem::le_arquivo(string in_file) {
    
    string line;

    ifstream file(in_file);

    int count = 0;
    int cur_page = -1;
    while(getline(file, line)) {
        istringstream iss(line);

        if(count == 0) {
            iss >> qt_frames;
        }
        else { 
            iss >> cur_page;
            pages.push_back(cur_page);
        }

        count++;
    }
    file.close();
}

void gerenciador_mem::fifo() {

    deque<int> frames;
    int page_fault = 0;
    deque<int>::iterator it_verificador;
    estatisticas_paginacao estat;

    for(int i=0; i < pages.size(); i++) {
        int current_page = pages[i];

        // procura a página na memória
        it_verificador = find(frames.begin(), frames.end(), current_page);

        // se memoria estiver cheia:
        if(frames.size() == qt_frames){
            // verifica se a página que quer inserir já está carregada em memória, 
            // se não tiver, remove o frame mais antigo, incrementa o contador de page fault e insere a nova
            // página, caso contrário, não faz nada
            if(it_verificador == frames.end()) {
                frames.pop_front();
                page_fault++;
                frames.push_back(current_page);
            }
        }
        // se ainda tiver memória livre:
        else {
            // verifica se a página já esta carregada na memória, se não estiver, incrementa o page_fault e 
            // adiciona a nova página na memória, caso contrário, não faz nada
            if(it_verificador == frames.end()) {
                page_fault++;
                frames.push_back(current_page);
            }
        }
    }

    estat = get_estatisticas();
    estat.fifo_pf = page_fault;
    set_estatisticas(estat);
}

void gerenciador_mem::sc() {

    int page_fault = 0;
    int found;
    vector<pair<int,int>> frames;
    estatisticas_paginacao estat;

    for(int i=0; i < pages.size(); i++) {
        int current_page = pages[i];

        // procura a página atual na memória
        found = find_sc(frames, current_page);

        // se a memoria estiver cheia, remove o frame mais antigo
        if(frames.size() == qt_frames){
            // se não achou a página na memória, incrementa page fault, remove frame antigo e adiciona o novo
            if (found != -1) {
                page_fault++;
                frames.erase(frames.begin() + found);
                frames.push_back(make_pair(current_page, 0));
            }
        }
        // se ainda tiver espaço livre na memória
        else {
            // se não encontrou a página na memória, incrementa o page fault e adiciona a página nova na memória
            if(found != -1) {
                page_fault++;
                frames.push_back(make_pair(current_page, 0));
            }
        }

        
    }

    estat = get_estatisticas();
    estat.sc_pf = page_fault;
    set_estatisticas(estat);

}

void gerenciador_mem::lru() {
    estatisticas_paginacao estat;
    int page_fault = 0;
    int current_page;
    int found;

    vector<pair<int,int>> frames;

    for(int i=0; i<pages.size(); i++) {
        current_page = pages[i];

        found = find_lru(frames, current_page);
        // se ainda houver espaço na memória
        if(frames.size() < qt_frames) {
            // se não achar a pagina, adiciona a atual e incrementa o contador de page fault
            if(found != -1) {
                page_fault++;
                frames.push_back(make_pair(current_page, 0));
            }
        }
        // se a memória estiver cheia
        else {
            // se não achar a página atual na memória
            if(found != -1) {
                // incrementa contador de page fault, remove a página que tem o menor numero de referencias e adiciona a página atual no seu lugar.
                page_fault++;
                frames.erase(frames.begin() + found);
                frames.push_back(make_pair(current_page, 0));
            }
        }
    }

    estat = get_estatisticas();
    estat.lru_pf = page_fault;
    set_estatisticas(estat);
}

