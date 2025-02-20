#pragma once

#include "tecnico.h"

typedef struct lista_tecnicos ListaTecnicos;

ListaTecnicos *lista_tecnicos_criar();

ListaTecnicos *lista_tecnicos_adicionar(ListaTecnicos *listaTecnicos, Tecnico *tecnico);

void *lista_tecnicos_free(ListaTecnicos *listaTecnicos);

void lista_tecnicos_print(ListaTecnicos *listaTecnicos);
