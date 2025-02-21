#include "lista_tecnicos.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct lista_tecnicos
{
    Tecnico **tecnicos;
    int memSize;
    int count;
};

ListaTecnicos *lista_tecnicos_criar()
{
    ListaTecnicos *pListaTecnicos = malloc(sizeof(struct lista_tecnicos));
    assert(pListaTecnicos);

    pListaTecnicos->memSize = LISTA_CAPACIDADE_INICIAL;
    pListaTecnicos->count = 0;
    pListaTecnicos->tecnicos = malloc(pListaTecnicos->memSize * sizeof(Tecnico *));

    return pListaTecnicos;
}

ListaTecnicos *lista_tecnicos_adicionar(ListaTecnicos *listaTecnicos, Tecnico *tecnico)
{
    if (listaTecnicos->count + 2 == listaTecnicos->memSize)
    {
        listaTecnicos->memSize *= 2;
        listaTecnicos->tecnicos = realloc(listaTecnicos->tecnicos, listaTecnicos->memSize * sizeof(Tecnico *));
    }

    listaTecnicos->tecnicos[listaTecnicos->count] = tecnico;
    listaTecnicos->count++;

    return listaTecnicos;
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
