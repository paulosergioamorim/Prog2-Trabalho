#include "gerencia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char const *argv[])
{
    Gerencia gerencia = criarGerencia();
    realizarGerencia(gerencia);
    liberarGerencia(gerencia);

    return 0;
}
