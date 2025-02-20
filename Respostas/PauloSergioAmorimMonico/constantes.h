#pragma once

#define TAM_MAX_NOME 101
#define TAM_CPF 15
#define TAM_TELEFONE 15

typedef enum {
    MASCULINO,
    FEMININO,
    OUTROS
} Genero;

typedef enum {
    RH,
    FINANCEIRO,
    PED,
    VENDAS,
    MARKETING
} SetorTrabalho;

typedef enum {
    GERAL,
    TI
} AreaAtuacao;
