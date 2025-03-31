#include "usuario.h"
#include "constantes.h"
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

Usuario criarUsuario(char *nome, char *cpf, Data *data, char *telefone, char *genero, char *setorTrabalho)
{
    Usuario usuario = malloc(sizeof(struct usuario));

    strcpy(usuario->nome, nome);
    strcpy(usuario->cpf, cpf);
    usuario->data = data;
    strcpy(usuario->telefone, telefone);
    strcpy(usuario->genero, genero);
    strcpy(usuario->setorTrabalho, setorTrabalho);
    usuario->ticketsSolicitados = 0;

    return usuario;
}

Usuario lerUsuario()
{
    char nome[TAM_NOME] = "";
    char cpf[TAM_CPF] = "";
    Data *data = NULL;
    char telefone[TAM_TELEFONE] = "";
    char genero[15] = "";
    char setorTrabalho[15] = "";

    scanf("%[^\n]%*c", nome);
    scanf("%[^\n]%*c", cpf);
    data = lerData();
    scanf("%[^\n]%*c", telefone);
    scanf("%[^\n]%*c", genero);
    scanf("%[^\n]%*c", setorTrabalho);

    return criarUsuario(nome, cpf, data, telefone, genero, setorTrabalho);
}

int eMesmoCPFUsuario(Usuario usuario, char *cpf)
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
void imprimirUsuario(Usuario usuario)
{
    printf("--------------------\n");
    printf("- Nome: %s\n", usuario->nome);
    printf("- CPF: %s\n", usuario->cpf);
    printf("- Data de Nascimento: ");
    imprimirData(usuario->data);
    printf("- Telefone: %s\n", usuario->telefone);
    printf("- Genero: %s\n", usuario->genero);
    printf("- Setor: %s\n", usuario->setorTrabalho);
    printf("- Tickets solicitados: %d\n", usuario->ticketsSolicitados);
}

void liberarUsuario(Usuario usuario)
{
    liberarData(usuario->data);
    free(usuario);
}

char *getCPFUsuario(Usuario usuario)
{
    return usuario->cpf;
}

char *getSetorUsuario(Usuario usuario)
{
    return usuario->setorTrabalho;
}

void addSolicitacaoUsuario(Usuario usuario)
{
    usuario->ticketsSolicitados++;
}

int getSolicitacoesUsuario(Usuario usuario)
{
    return usuario->ticketsSolicitados;
}

int compararUsuarios(const void *p1, const void *p2)
{
    Usuario u1 = *(Usuario *)p1;
    Usuario u2 = *(Usuario *)p2;

    if (u2->ticketsSolicitados == u1->ticketsSolicitados)
        return strcmp(u1->nome, u2->nome);

    return u2->ticketsSolicitados - u1->ticketsSolicitados;
}

int getIdadeUsuario(Usuario usuario)
{
    Data *dataHoje = criarData(18, 02, 2025);

    int anos = getAnosDiferencaData(usuario->data, dataHoje);

    liberarData(dataHoje);

    return anos;
}
