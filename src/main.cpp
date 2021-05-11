#include <bits/stdc++.h>
#include "kernel.hpp"

int main(int argc, char* argv[]) {
	kernel k;
	escalonador esc_1;
	// teste master
	if(argc != 3) {
		printf("Parametros de entrada incorretos!\n");
		return 0;
	}
	// inicializa o kernel
	k = kernel();
	k.verifica_entrada(atoi(argv[1]), argv[2]);
	// verificar qual processo deve ser executado
	return 0;
}
