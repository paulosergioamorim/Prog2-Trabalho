#pragma once

#include "data.h"
#include "constantes.h"

typedef struct usuario Usuario;

Usuario *usuario_criar(char *nome, char *cpf, Data* data, char *telefone, Genero genero, SetorTrabalho setorTrabalho);

int usuario_e_mesmo_cpf(Usuario *usuario, char *cpf);

void usuario_free(Usuario *usuario);
