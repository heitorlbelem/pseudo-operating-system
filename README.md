# Pseudo-SO
## Especificação
O trabalho de implementação da disciplina de SO, a ser desenvolvido em grupo com quatro (04) //
componentes, compreenderá as seguintes fases:
*  Estudo teórico relacionado ao assunto do trabalho;
*  Apresentação da solução teórica dada ao problema;
*  Implementação da solução proposta;
*  Apresentação e explicação detalhada do código-fonte implementado;
*  Relatório explicando o processo de construção e o uso da aplicação.

Implementação de um pseudo-SO multiprogramado, composto por um __Gerenciador de Processos__,
por um __Gerenciador de Memória__ e por um __Gerenciador de Entrada/Saída__.
1. __O gerenciador de processos__
deve ser capaz de aplicar o algoritmo de escalonamento definido por meio de parâmetro pelo usuário do SO.
2. O __gerenciador de memória__ deve garantir que um processo não acesse as regiões de memória de um outro
processo, e que o algoritmo de substituição de página seja adequadamente usado. 
3. __O gerenciador de
entrada/saída__ deve ser responsável por administrar o algoritmo especificado para a busca em disco. Cada
módulo será testado de acordo com as especificações determinadas abaixo. Além disso, o pseudo-SO deve
receber como parâmetro um inteiro e um arquivo texto, por exemplo $ 1 processes.txt. O inteiro determina
qual módulo deve ser ativado (no exemplo dado significa que será ativado o módulo de processos, pois foi o
inteiro 1), e o arquivo texto (com extensão .txt) repassa os dados de entrada necessários para a execução do
módulo escolhido. Os detalhes para a implementação desse pseudo-SO são descritos nas próximas seções.

Mais informações disponíveis no [documento de especificação](docs/especificacao.pdf)
## Autores
- Heitor
- Gabriel Bessa
- Thiago
- Vinicius

## Para executar

Estando na pasta src/. Digite:
```bash
make
```
Depois seguindo a especificação:
_Para um dado arquivo texto de entrada teste.txt dentro da pasta src/_

1. Para executar o teste para a gerência de processos:
```bash
./so 1 teste.txt
```

2. Para executar o teste para a gerência de memória:
```bash
./so 2 teste.txt
```

3. Para executar o teste para a gerência de Entrada/Saída:
```bash
./so 3 teste.txt
```
