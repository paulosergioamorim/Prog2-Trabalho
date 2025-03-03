#include "gerencia.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    Gerencia gerencia = criarGerencia();
    char option = 0;

    while (option != 'F')
    {
        scanf("%c%*c", &option);
        handleOption(gerencia, option);
    }

    liberarGerencia(gerencia);

    return 0;
}
