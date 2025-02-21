#include "software.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Software
{
    char nome[MAX_TAM_NOME_SOFTWARE];
    char categoria[MAX_TAM_CAT];
    int impacto;
    char motivo[MAX_TAM_MOTIVO];

    int tempoEstimado;
};

/**
 * @brief Aloca uma estrutura Software na memória e inicializa os parâmetro necessários
 * @param nome Nome do software
 * @param categoria Categoria do software
 * @param impacto Impacto do chamado
 * @param motivo Motivo da abertura do ticket
 * @return  Uma estrutura Software inicializada.
 */
Software *criaSoftware(char *nome, char *categoria, int impacto, char *motivo)
{
    Software *pSoftware = malloc(sizeof(struct Software));
    assert(pSoftware);

    strcpy(pSoftware->nome, nome);
    strcpy(pSoftware->categoria, categoria);
    pSoftware->impacto = impacto;
    strcpy(pSoftware->motivo, motivo);
    pSoftware->tempoEstimado = 0;

    return pSoftware;
}

/**
 * @brief Lê da entrada padrão um  ticket do TIPO software
 * @return  Um chamado do Tipo Software
 */
Software *lerSoftware()
{
    char nome[MAX_TAM_NOME_SOFTWARE] = "";
    char categoria[MAX_TAM_CAT] = "";
    int impacto = 0;
    char motivo[MAX_TAM_MOTIVO] = "";

    scanf("%[^\n]%*c", nome);
    scanf("%[^\n]%*c", categoria);
    scanf("%d%*c", &impacto);
    scanf("%[^\n]%*c", motivo);

    return criaSoftware(nome, categoria, impacto, motivo);
}

/**
 * @brief  Calcula o tempo estimado para resolver um ticket do tipo Software.
 * Tempo estimado depende da categoria e impacto
 * @param s  Ticket do tipo Software
 */
void setTempoEstimadoSoftware(Software *s)
{
    int tempoEstimado = 0;

    if (strcmp(s->categoria, "BUG") == 0)
        tempoEstimado += 3;

    if (strcmp(s->categoria, "OUTROS") == 0)
        tempoEstimado += 2;

    if (strcmp(s->categoria, "DUVIDA") == 0)
        tempoEstimado += 1;

    tempoEstimado += s->impacto;

    s->tempoEstimado = tempoEstimado;
}

/**
 * @brief  Retorna o tempo estimado para resolver um ticket do tipo Software.
 * @param dado  Ticket do tipo Software
 * @return  Tempo estimado para resolver um ticket do tipo Software
 */
int getTempoEstimadoSoftware(void *dado)
{
    Software *software = (Software *)dado;

    setTempoEstimadoSoftware(software);

    return software->tempoEstimado;
}

/**
 * @brief  Retorna o tipo do ticket
 * @return  'S' para Software
 */
char getTipoSoftware()
{
    return 'S';
}

/**
 * @brief  Desaloca um ticket do tipo Software da memória
 * @param s  Ticket do tipo Software
 */
void desalocaSoftware(void *s)
{
    free(s);
}

/**
 * @brief  Imprime um ticket do tipo Software
 * @param dado  Ticket do tipo Software
 */
void notificaSoftware(void *dado)
{
    /*
- Nome do software: EXCEL
- Categoria: DUVIDA
- Nível do impacto: 2
- Motivo: NAO CONSIGO ORDENAR COLUNA DE DADOS
    */
    Software *software = (Software *) dado;

    printf("- Nome do software: %s\n", software->nome);
    printf("- Categoria: %s\n", software->categoria);
    printf("- Nível do impacto: %d\n", software->impacto);
    printf("- Motibo: %s\n", software->motivo);
}