#include "gerencia.h"
#include "usuario.h"
#include "list.h"

int main(int argc, char const *argv[])
{
    Gerencia gerencia = criarGerencia();
    char option = 0;
    
    while (option != 'F'){
        scanf("%c%*c", &option);
        handleOption(gerencia, option);
    } 

    liberarGerencia(gerencia);

    return 0;
}
