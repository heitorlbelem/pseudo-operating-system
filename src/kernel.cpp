#include "kernel.hpp"
#include "escalonador.hpp"
// construtor
kernel::kernel() {
    set_modo_operacao(0);
}
// destrutor
kernel::~kernel() {

}

// metodos GET
escalonador kernel::get_escalonador()
{
    return esc;
}
int kernel::get_modo_operacao()
{
    return modo_operacao;
}

// metodos SET

void kernel::set_escalonador(escalonador esc_entrada)
{
    esc = esc_entrada;
    return;
}

void kernel::set_modo_operacao(int modo_op)
{
    modo_operacao = modo_op;
}


// metodos diversos

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
            set_modo_operacao(1);
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

void kernel::verifica_modo_op(void)
{
    switch(modo_operacao) {
        case 1:
            gerencia_processos();
            break;
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

void kernel::gerencia_processos()
{
    // FIFO
    esc.fifo();

    // SJF
    esc.sjf();
    // escreve arquivo de saida
    esc.escreve_historico_processos();

}