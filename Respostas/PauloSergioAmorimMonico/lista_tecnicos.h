#pragma once

#include "tecnico.h"

typedef struct lista_tecnicos ListaTecnicos;

ListaTecnicos *lista_tecnicos_criar();

void lista_tecnicos_adicionar(ListaTecnicos *listaTecnicos, Tecnico *tecnico);

void lista_tecnicos_free(ListaTecnicos *listaTecnicos);

void lista_tecnicos_print(ListaTecnicos *listaTecnicos);

void lista_tecnicos_print_por_ranking(ListaTecnicos *listaTecnicos);

int lista_tecnicos_quantidade(ListaTecnicos *listaTecnicos);

Tecnico *lista_tecnicos_tecnico(ListaTecnicos *listaTecnicos, int i);

int lista_tecnicos_media_idade(ListaTecnicos *listaTecnicos);

int lista_tecnicos_media_trabalho(ListaTecnicos *listaTecnicos);
