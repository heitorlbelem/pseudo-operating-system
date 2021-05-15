#include "gerenciador_mem.hpp"

void reset_bit_R(vector<pair<int, int>> &elements) {
    for(int i=0; i<elements.size(); i++) {
        elements[i].second = 0; 
    }
}

int find_sc(vector<pair<int, int>> &elements, int current) {

    vector<int> removable_frames;
    // percorre todos os frames que estão na memória
    for(int i=0; i < elements.size(); i++) {

        // se encontrar o frame que está para ser inserido, retorna -1 pois não
        // precisa remover nenhum para colocar o atual. (NÃO TEM PAGE FAULT)
        if(elements[i].first == current) {
            elements[i].second = 2;
            return -1;
        }
        elements[i].second--;
        // se não for o mesmo frame que quer adicionar, verifica o bit R
        // se for 0, adiciona a posição do frame na lista de valores que podem ser removidos
        if(elements[i].second == 0) {
            removable_frames.push_back(i);
        }

    }

    if(removable_frames.size() == 0)
        return 0;

    return removable_frames[0];

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
    int found = -1;
    int max_references = 0;
    vector<pair<int,int>> frames;
    estatisticas_paginacao estat;

    for(int i=0; i < pages.size(); i++) {
        int current_page = pages[i];

        // procura a página atual na memória
        found = find_sc(frames, current_page);

        // se a memoria estiver cheia, remove o frame mais antigo
        if(frames.size() == qt_frames){
            if (found != -1) {
                page_fault++;
                frames.erase(frames.begin() + found);
                frames.push_back(make_pair(current_page, 2));
            }
        }
        // se ainda tiver espaço livre na memória
        else {
            // se não encontrou a página na memória, incrementa o page fault e adiciona a página nova na memória
            if(found != -1) {
                page_fault++;
                frames.push_back(make_pair(current_page, 2));
            }
        }

        
    }

    estat = get_estatisticas();
    estat.sc_pf = page_fault;
    set_estatisticas(estat);

}

