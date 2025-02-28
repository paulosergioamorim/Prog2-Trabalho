#include "manutencao.h"
#include "constantes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Estrutura de um Ticket Manutencao contendo os parametros especificos de um ticket do tipo Manutencao
 */
struct Manutencao
{
    char nome[MAX_TAM_NOME_MANUTENCAO];
    char estado[MAX_TAM_NOME_MANUTENCAO];
    char local[MAX_TAM_LOCAL_MANUTENCAO];
    char setor[TAM_SETOR_TRABALHO];
    int tempoEstimado;
};

Manutencao *criaManutencao(char *nome, char *estado, char *local)
{
    Manutencao *manutencao = malloc(sizeof(Manutencao));

    strcpy(manutencao->nome, nome);
    strcpy(manutencao->estado, estado);
    strcpy(manutencao->local, local);
    strcpy(manutencao->setor, "");
    manutencao->tempoEstimado = 0;

    return manutencao;
}

/**
 * @brief Lê da entrada padrão um  ticket do TIPO Manutencao
 * @return  Um chamado do Tipo Manutencao
 */
Manutencao *lerManutencao()
{
    char nome[MAX_TAM_NOME_MANUTENCAO] = "";
    char estado[MAX_TAM_NOME_MANUTENCAO] = "";
    char local[MAX_TAM_LOCAL_MANUTENCAO] = "";

    scanf("%[^\n]%*c", nome);
    scanf("%[^\n]%*c", estado);
    scanf("%[^\n]%*c", local);

    return criaManutencao(nome, estado, local);
}

/**
 * @brief  Calcula o tempo estimado para resolver um ticket do tipo Manutencao.
 * Tempo estimado depende da categoria e impacto
 * @param s  Ticket do tipo Manutencao
 */
void setTempoEstimadoManutencao(Manutencao *manutencao)
{
    if (strcmp(manutencao->estado, "BOM") == 0)
        manutencao->tempoEstimado = 1;

    else if (strcmp(manutencao->estado, "REGULAR") == 0)
        manutencao->tempoEstimado = 2;

    else if (strcmp(manutencao->estado, "RUIM") == 0)
        manutencao->tempoEstimado = 3;

    if (strcmp(manutencao->setor, "RH") == 0)
        manutencao->tempoEstimado *= 2;

    else if (strcmp(manutencao->setor, "FINANCEIRO") == 0)
        manutencao->tempoEstimado *= 3;
}

void setSetor(Manutencao *manutencao, char *setor)
{
    strcpy(manutencao->setor, setor);
}

/**
 * @brief  Retorna o tempo estimado para resolver um ticket do tipo Manutencao.
 * @param dado  Ticket do tipo Manutencao
 * @return  Tempo estimado para resolver um ticket do tipo Manutencao
 */
int getTempoEstimadoManutencao(void *dado)
{
    Manutencao *manutencao = (Manutencao *)dado;
    setTempoEstimadoManutencao(manutencao);

    return manutencao->tempoEstimado;
}

/**
 * @brief  Retorna o tipo do ticket
 * @return  'M' para Manutencao
 */
char getTipoManutencao()
{
    return 'M';
}

/**
 * @brief  Desaloca um ticket do tipo Manutencao da memória
 * @param s  Ticket do tipo Manutencao
 */
void desalocaManutencao(void *s)
{
    free(s);
    s = NULL;
}

/**
 * @brief  Imprime um ticket do tipo Manutencao
 * @param dado  Ticket do tipo Manutencao
 */
void notificaManutencao(void *dado)
{
    /*
- Tipo: Manutencao
- Nome do item: PORTA DE ENTRADA
- Estado de conservacao: RUIM
- Local: SALA 22 CT-7
- Tempo estimado: 6h
    */
    Manutencao *manutencao = (Manutencao *)dado;

    printf("- Tipo: Manutencao\n");
    printf("- Nome do item: %s\n", manutencao->nome);
    printf("- Estado de conservacao: %s\n", manutencao->estado);
    printf("- Local: %s\n", manutencao->local);
    printf("- Tempo estimado: %dh\n", manutencao->tempoEstimado);
}
