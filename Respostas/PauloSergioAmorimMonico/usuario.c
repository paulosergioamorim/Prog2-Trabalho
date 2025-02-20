#include "usuario.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "constantes.h"

struct usuario {
    char nome[TAM_MAX_NOME];
    char cpf[TAM_CPF];
    Data *data;
    Genero genero;
    char telefone[TAM_TELEFONE];
    SetorTrabalho setorTrabalho;
};

Usuario *usuario_criar(char *nome, char *cpf, Data *data, char *telefone, Genero genero, SetorTrabalho setorTrabalho) {
    Usuario *pUsuario = malloc(sizeof(struct usuario));
    assert(pUsuario);

    strcpy(pUsuario->nome, nome);
    strcpy(pUsuario->cpf, cpf);
    pUsuario->data = data;
    strcpy(pUsuario->telefone, telefone);
    pUsuario->genero = genero;
    pUsuario->setorTrabalho = setorTrabalho;

    return pUsuario;
}

void usuario_free(Usuario *usuario) {
    data_free(usuario->data);
    free(usuario);
}
