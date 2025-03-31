#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "empresa.h"

struct Empresa {
    char nome[TAM_NOME_EMPRESA];
    char cnpj[TAM_CNPJ_EMPRESA];
    Data *dataInicio;
    char paisOrigem[TAM_PAIS_ORIGEM_EMPRESA];
    char ramoAtuacao[TAM_RAMO_ATUACAO_EMPRESA];
    char email[TAM_EMAIL_EMPRESA];
};

Empresa criarEmpresa(char *nome, char *cnpj, Data *dataInicio, char *paisOrigem, char *ramoAtuacao, char *email) {
    Empresa empresa = malloc(sizeof(struct Empresa));
    strcpy(empresa->nome, nome);
    strcpy(empresa->cnpj, cnpj);
    empresa->dataInicio = dataInicio;
    strcpy(empresa->paisOrigem, paisOrigem);
    strcpy(empresa->ramoAtuacao, ramoAtuacao);
    strcpy(empresa->email, email);

    return empresa;
}

Empresa lerEmpresa() {
    char nome[TAM_NOME_EMPRESA] = "";
    char cnpj[TAM_CNPJ_EMPRESA] = "";
    Data *dataInicio;
    char paisOrigem[TAM_PAIS_ORIGEM_EMPRESA] = "";
    char ramoAtuacao[TAM_RAMO_ATUACAO_EMPRESA] = "";
    char email[TAM_EMAIL_EMPRESA] = "";

    scanf("%[^\n]\n", nome);
    scanf("%[^\n]\n", cnpj);
    dataInicio = lerData();
    scanf("%[^\n]\n", paisOrigem);
    scanf("%[^\n]\n", ramoAtuacao);
    scanf("%[^\n]\n", email);

    return criarEmpresa(nome, cnpj, dataInicio, paisOrigem, ramoAtuacao, email);
}

void imprimirEmpresa(Empresa empresa) {
    printf("--------------------\n");
    printf("- Nome: %s\n", empresa->nome);
    printf("- CNPJ: %s\n", empresa->cnpj);
    printf("- Inicio da Parceria: ");
    imprimirData(empresa->dataInicio);
    printf("- Pais de Origem: %s\n", empresa->paisOrigem);
    printf("- Ramo de Atuacao: %s\n", empresa->ramoAtuacao);
    printf("- Email: %s\n", empresa->email);
}

char *getCNPJEmpresa(Empresa empresa) {
    return empresa->cnpj;
}

void liberarEmpresa(Empresa empresa) {
    liberarData(empresa->dataInicio);
    free(empresa);
}