#include "gerenciador_mem.hpp"


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

        // se memoria estiver cheia remove o frame mais antigo
        if(frames.size() == qt_frames){
            it_verificador = find(frames.begin(), frames.end(), current_page);
            if(it_verificador == frames.end()) {
                frames.pop_front();
                page_fault++;
                frames.push_back(current_page);
            }
        }
        // se ainda tiver memória livre, coloca acrescenta o contador de page_fault e adiciona o frame na memória
        else {
            page_fault++;
            frames.push_back(current_page);
        }
    }

    estat = get_estatisticas();
    estat.fifo_pf = page_fault;
    set_estatisticas(estat);
}

void gerenciador_mem::sc() {

    int page_fault = 0;
    vector<pair<int,int>> frames;
    deque<pair<int,int>>::iterator it_verificador;
    estatisticas_paginacao estat;
    int found = -1;

    for(int i=0; i < pages.size(); i++) {
        int current_page = pages[i];

        // se memoria estiver cheia remove o frame mais antigo
        if(frames.size() == qt_frames){
            found = find_value(frames, current_page);
            if (found != -1) {
                page_fault ++;
                frames.erase(frames.begin() + found);
            }
        }
        // se ainda tiver memória livre, acrescenta o contador de page_fault e adiciona o frame na memória
        else {
            page_fault++;
            frames.push_back(make_pair(current_page,0));
        }
    }

}