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
    void le_arquivo(string);

};


#endif //gerenciador_mem_hpp