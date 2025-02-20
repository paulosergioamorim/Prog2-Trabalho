#pragma once

#include "data.h"
#include "constantes.h"

typedef struct tecnico Tecnico;

Tecnico *tecnico_criar(char *nome, char *cpf, Data* data, Genero genero, AreaAtuacao areaAtuacao, float salario, int disponibilidadeTempo);

void tecnico_free(Tecnico *tecnico);
