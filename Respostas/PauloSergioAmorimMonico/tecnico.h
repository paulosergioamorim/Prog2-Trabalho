#pragma once

#include "constantes.h"
#include "data.h"

typedef struct tecnico Tecnico;

Tecnico *tecnico_criar(char *nome, char *cpf, Data *data, char *genero, char *telefone, char *areaAtuacao,
                       float salario, int disponibilidadeTempo);

Tecnico *tecnico_ler();

int tecnico_e_mesmo_cpf(Tecnico *tecnico, char *cpf);

void tecnico_print(Tecnico *tecnico);

void tecnico_free(Tecnico *tecnico);
