#include "lista_tecnicos.h"
#include "constantes.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista_tecnicos
{
    Tecnico **tecnicos;
    int size;
    int count;
};

ListaTecnicos *lista_tecnicos_criar()
{
    ListaTecnicos *listaTecnicos = malloc(sizeof(ListaTecnicos));
    assert(listaTecnicos);

    listaTecnicos->size = LISTA_CAPACIDADE_INICIAL;
    listaTecnicos->count = 0;
    listaTecnicos->tecnicos = malloc(listaTecnicos->size * sizeof(Tecnico *));

    return listaTecnicos;
}

void lista_tecnicos_adicionar(ListaTecnicos *listaTecnicos, Tecnico *tecnico)
{
    if (listaTecnicos->count + 1 == listaTecnicos->size)
    {
        listaTecnicos->size *= 2;
        listaTecnicos->tecnicos = realloc(listaTecnicos->tecnicos, listaTecnicos->size * sizeof(Tecnico *));
    }

    listaTecnicos->tecnicos[listaTecnicos->count] = tecnico;
    listaTecnicos->count++;
}

void lista_tecnicos_free(ListaTecnicos *listaTecnicos)
{
    for (int i = 0; i < listaTecnicos->count; i++)
        tecnico_free(listaTecnicos->tecnicos[i]);

    free(listaTecnicos->tecnicos);
    free(listaTecnicos);
}

void lista_tecnicos_print(ListaTecnicos *listaTecnicos)
{
    printf("----- BANCO DE TECNICOS -----\n");

    for (int i = 0; i < listaTecnicos->count; i++)
    {
        printf("--------------------\n");
        tecnico_print(listaTecnicos->tecnicos[i]);
    }

    printf("----------------------------\n\n");
}

int lista_tecnicos_quantidade(ListaTecnicos *listaTecnicos) {
    return listaTecnicos->count;
}

Tecnico *lista_tecnicos_tecnico(ListaTecnicos *listaTecnicos, int i) {
    return listaTecnicos->tecnicos[i];
}

void lista_tecnicos_print_por_ranking(ListaTecnicos *listaTecnicos) {
    Tecnico **sortedTecnicos = malloc(listaTecnicos->count * sizeof(Tecnico *));
    memcpy(sortedTecnicos, listaTecnicos->tecnicos, listaTecnicos->count * sizeof(Tecnico *));
    qsort(sortedTecnicos, listaTecnicos->count, sizeof(Tecnico *), qsort_compara_tecnicos);

    printf("----- RANKING DE TECNICOS -----\n");

    for (int i = 0; i < listaTecnicos->count; i++)
    {
        printf("--------------------\n");
        tecnico_print(sortedTecnicos[i]);
    }

    printf("-------------------------------\n\n");

    free(sortedTecnicos);
}

int lista_tecnicos_media_idade(ListaTecnicos *listaTecnicos) {
    int soma = 0;
    Data *dataHoje = data_criar(18, 02, 2025);

    for (int i = 0; i < listaTecnicos->count; i++)
    {
        Data *data = tecnico_recupera_data(listaTecnicos->tecnicos[i]);
        int idade = data_anos_diferenca(data, dataHoje);
        soma += idade;
    }

    free(dataHoje);

    return soma / listaTecnicos->count;
}

int lista_tecnicos_media_trabalho(ListaTecnicos *listaTecnicos) {
    int soma = 0;

    for (int i = 0; i < listaTecnicos->count; i++)
        soma += tecnico_recupera_tempo_trabalhado(listaTecnicos->tecnicos[i]);

    return soma / listaTecnicos->count;
}