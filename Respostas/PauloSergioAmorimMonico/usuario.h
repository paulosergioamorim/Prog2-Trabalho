#pragma once

#include "data.h"

typedef struct usuario *Usuario;

Usuario usuario_criar(char *nome, char *cpf, Data* data, char *telefone, char *genero, char *setorTrabalho);

Usuario usuario_ler();

int usuario_e_mesmo_cpf(Usuario usuario, char *cpf);

void usuario_print(Usuario usuario);

void usuario_free(Usuario usuario);

char *usuario_recupera_cpf(Usuario usuario);

char *usuario_recupera_setor(Usuario usuario);

void usuario_incrementa_solicitacoes(Usuario usuario);

int usuario_recupera_solicitacoes(Usuario usuario);

int qsort_compara_usuarios(const void * p1, const void * p2);

int usuario_recupera_idade(Usuario usuario);