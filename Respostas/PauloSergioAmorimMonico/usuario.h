#pragma once

#include "data.h"
#include "constantes.h"

typedef struct usuario Usuario;

Usuario *usuario_criar(char *nome, char *cpf, Data* data, char *telefone, char *genero, char *setorTrabalho);

Usuario *usuario_ler();

int usuario_e_mesmo_cpf(Usuario *usuario, char *cpf);

void usuario_print(Usuario *usuario);

void usuario_free(Usuario *usuario);
