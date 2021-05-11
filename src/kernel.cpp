#include "kernel.hpp"
#include "escalonador.hpp"
// construtor
kernel::kernel() {
}
// destrutor
kernel::~kernel() {

}

void kernel::verifica_entrada(int entrada, string arquivo)
{
    switch(entrada) {
        case 1:
        {

        
        // Gerenciamento de processos
        // chamar funcao de ler arquivo de processos
            escalonador esc_temp;
            esc_temp = escalonador();
            esc_temp.le_arquivo_entrada(arquivo);
            set_escalonador(esc_temp);
            break;
        }
        case 2:
        // gerenciamento de memoria
            break;
        case 3:
        // gerenciamneto de E/S
            break;
        default:
            cout << "Tipo de arquivo incorreto!" << endl;
    }

}

escalonador kernel::get_escalonador()
{
    return esc;
}

void kernel::set_escalonador(escalonador esc_entrada)
{
    esc = esc_entrada;
    return;
}