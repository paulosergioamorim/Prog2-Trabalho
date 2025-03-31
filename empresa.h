#pragma once

#include "data.h"

#define TAM_NOME_EMPRESA 80
#define TAM_CNPJ_EMPRESA sizeof("00.000.000/0000-00")
#define TAM_PAIS_ORIGEM_EMPRESA 30
#define TAM_RAMO_ATUACAO_EMPRESA 30
#define TAM_EMAIL_EMPRESA 50

typedef struct Empresa *Empresa;

Empresa criarEmpresa(char *nome, char *cnpj, Data *dataInicio, char *paisOrigem, char *ramoAtuacao, char *email);

Empresa lerEmpresa();

void imprimirEmpresa(Empresa empresa);

char *getCNPJEmpresa(Empresa empresa);

void liberarEmpresa(Empresa empresa);