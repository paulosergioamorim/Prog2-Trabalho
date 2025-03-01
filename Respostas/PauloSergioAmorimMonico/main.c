#include "gerencia.h"

int main(int argc, char const *argv[])
{
    Gerencia gerencia = criarGerencia();
    realizarGerencia(gerencia);
    liberarGerencia(gerencia);

    return 0;
}
