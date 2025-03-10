#include "outros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Estrutura de um Ticket Outros contendo os parametros especificos de um ticket do tipo Outros
 */
struct Outros
{
    char descricao[OUTROS_DESCRICAO];
    char local[OUTROS_LOCAL];
    int nivelDificuldade;
    int tempoEstimado;
};

Outros *criaOutros(char *descricao, char *local, int nivelDificuldade)
{
    Outros *outros = malloc(sizeof(Outros));

    strcpy(outros->descricao, descricao);
    strcpy(outros->local, local);
    outros->nivelDificuldade = nivelDificuldade;
    outros->tempoEstimado = 0;

    return outros;
}

/**
 * @brief Lê da entrada padrão um  ticket do TIPO Outros
 * @return  Um chamado do Tipo Outros
 */
Outros *lerOutros()
{
    /*
    RECOLHER COBRA QUE APARECEU NA ENTRADA DO PREDIO (descrição)
PASSARELA DE ENTRADA (local)
5 (dificuldade estimada pelo usuário
    */
    char descricao[OUTROS_DESCRICAO] = "";
    char local[OUTROS_LOCAL] = "";
    int nivelDificuldade = 0;

    scanf("%[^\n]%*c", descricao);
    scanf("%[^\n]%*c", local);
    scanf("%d%*c", &nivelDificuldade);

    return criaOutros(descricao, local, nivelDificuldade);
}

/**
 * @brief  Calcula o tempo estimado para resolver um ticket do tipo Outros.
 * Tempo estimado depende da categoria e impacto
 * @param s  Ticket do tipo Outros
 */
void setTempoEstimadoOutros(Outros *outros)
{
    outros->tempoEstimado = outros->nivelDificuldade;
}

/**
 * @brief  Retorna o tempo estimado para resolver um ticket do tipo Outros.
 * @param dado  Ticket do tipo Outros
 * @return  Tempo estimado para resolver um ticket do tipo Outros
 */
int getTempoEstimadoOutros(void *dado)
{
    Outros *outros = (Outros *)dado;

    return outros->tempoEstimado;
}

/**
 * @brief  Retorna o tipo do ticket
 * @return  'O' para Outros
 */
char getTipoOutros()
{
    return 'O';
}

/**
 * @brief  Desaloca um ticket do tipo Outros da memória
 * @param s  Ticket do tipo Outros
 */
void desalocaOutros(void *s)
{
    free(s);
}

/**
 * @brief  Imprime um ticket do tipo Outros
 * @param dado  Ticket do tipo Outros
 */
void notificaOutros(void *dado)
{
    Outros *outros = (Outros *)dado;
    printf("- Tipo: Outros\n");
    printf("- Descricao: %s\n", outros->descricao);
    printf("- Local: %s\n", outros->local);
    printf("- Nivel de Dificuldade: %d\n", outros->nivelDificuldade);
    printf("- Tempo Estimado: %dh\n", outros->tempoEstimado);
}
