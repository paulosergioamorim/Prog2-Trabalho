#include "gerencia.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    Gerencia gerencia = criarGerencia();
    char opcao = 0;

    while (opcao != 'F')
    {
        scanf("%c%*c", &opcao);
        realizarGerencia(gerencia, opcao);
    }

    liberarGerencia(gerencia);

    return 0;
}
