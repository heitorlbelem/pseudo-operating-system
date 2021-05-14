#ifndef gerenciador_mem_hpp
#define gerenciador_mem_hpp

#include <bits/stdc++.h>
using namespace std;

struct estatisticas_paginacao {
    int fifo_pf;
    int sc_pf;
    int lru_pf;
};

class gerenciador_mem {

private:
    vector<int> pages;
    int qt_frames;
    estatisticas_paginacao estatisticas;
public:
    gerenciador_mem();
    ~gerenciador_mem();
    
    estatisticas_paginacao get_estatisticas();
    void set_estatisticas(estatisticas_paginacao estat);
    
    
    void fifo();
    // segunda chance
    void sc();
    void lru();

    void le_arquivo(string);

};

int find_value(vector<pair<int, int>> elements, int current) {

    vector<int> removable_frames;

    // percorre todos os frames que estão na memória
    for(int i=0; i < elements.size(); i++) {
        pair<int, int> current_pair = elements[i];

        // se encontrar o frame que está para ser inserido, retorna -1 pois não
        // precisa remover nenhum para colocar o atual. (NÃO TEM PAGE FAULT)
        if(current_pair.first == current) {
            return -1;
        }

        // se não for o mesmo frame que quer adicionar, verifica o bit R
        // se for 0, adiciona a posição do frame na lista de valores que podem ser removidos
        if(current_pair.second == 0) {
            removable_frames.push_back(i);
        }

    }

    if(removable_frames.size() == 0)
        return 0;

    return removable_frames[0];

}


#endif //gerenciador_mem_hpp