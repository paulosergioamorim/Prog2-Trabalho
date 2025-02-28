#include "usuario.h"
#include "constantes.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct usuario
{
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    Data *data;
    char genero[TAM_GENERO];
    char telefone[TAM_TELEFONE];
    char setorTrabalho[TAM_SETOR_TRABALHO];
    int ticketsSolicitados;
};

Usuario *usuario_criar(char *nome, char *cpf, Data *data, char *telefone, char *genero, char *setorTrabalho)
{
    Usuario *usuario = malloc(sizeof(Usuario));
    assert(usuario);

    strcpy(usuario->nome, nome);
    strcpy(usuario->cpf, cpf);
    usuario->data = data;
    strcpy(usuario->telefone, telefone);
    strcpy(usuario->genero, genero);
    strcpy(usuario->setorTrabalho, setorTrabalho);
    usuario->ticketsSolicitados = 0;

    return usuario;
}

Usuario *usuario_ler()
{
    char nome[TAM_NOME] = "";
    char cpf[TAM_CPF] = "";
    Data *data = NULL;
    char telefone[TAM_TELEFONE] = "";
    char genero[15] = "";
    char setorTrabalho[15] = "";

    scanf("%[^\n]%*c", nome);
    scanf("%[^\n]%*c", cpf);
    data = data_ler();
    scanf("%[^\n]%*c", telefone);
    scanf("%[^\n]%*c", genero);
    scanf("%[^\n]%*c", setorTrabalho);

    return usuario_criar(nome, cpf, data, telefone, genero, setorTrabalho);
}

int usuario_e_mesmo_cpf(Usuario *usuario, char *cpf)
{
    return strcmp(usuario->cpf, cpf) == 0;
}

/*
- Nome: TAHM KENCH
- CPF: 123.932.250-46
- Data de Nascimento: 1/9/1955
- Telefone: (34)96373-7004
- Genero: OUTROS
- Setor: RH
- Tickets solicitados: 0
*/
void usuario_print(Usuario *usuario)
{
    printf("- Nome: %s\n", usuario->nome);
    printf("- CPF: %s\n", usuario->cpf);
    printf("- Data de Nascimento: ");
    data_print(usuario->data);
    printf("- Telefone: %s\n", usuario->telefone);
    printf("- Genero: %s\n", usuario->genero);
    printf("- Setor: %s\n", usuario->setorTrabalho);
    printf("- Tickets solicitados: %d\n", usuario->ticketsSolicitados);
}

void usuario_free(Usuario *usuario)
{
    data_free(usuario->data);
    free(usuario);
}

char *usuario_recupera_cpf(Usuario *usuario)
{
    return usuario->cpf;
}

char *usuario_recupera_setor(Usuario *usuario) {
    return usuario->setorTrabalho;
}

void usuario_incrementa_solicitacoes(Usuario *usuario)
{
    usuario->ticketsSolicitados++;
}

int usuario_recupera_solicitacoes(Usuario *usuario)
{
    return usuario->ticketsSolicitados;
}

int qsort_compara_usuarios(const void *p1, const void *p2)
{
    Usuario *u1 = *(Usuario **)p1;
    Usuario *u2 = *(Usuario **)p2;

    return u2->ticketsSolicitados >= u1->ticketsSolicitados;
}

Data *usuario_recupera_data(Usuario *usuario) {
    return usuario->data;
}
