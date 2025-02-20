#include "lista_usuarios.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

struct lista_usuarios
{
    Usuario **usuarios;
    int memSize;
    int count;
};

ListaUsuarios *lista_usuarios_criar()
{
    ListaUsuarios *pListaUsuarios = malloc(sizeof(struct lista_usuarios));
    assert(pListaUsuarios);

    pListaUsuarios->memSize = LISTA_CAPACIDADE_INICIAL;
    pListaUsuarios->count = 0;
    pListaUsuarios->usuarios = malloc(pListaUsuarios->memSize * sizeof(Usuario *));

    return pListaUsuarios;
}

ListaUsuarios *lista_usuarios_adicionar(ListaUsuarios *listaUsuarios, Usuario *usuario)
{
    if (listaUsuarios->count + 2 == listaUsuarios->memSize)
    {
        listaUsuarios->memSize *= 2;
        listaUsuarios->usuarios = realloc(listaUsuarios->usuarios, listaUsuarios->memSize * sizeof(Usuario *));
    }

    listaUsuarios->usuarios[listaUsuarios->count] = usuario;
    listaUsuarios->count++;

    return listaUsuarios;
}

void *lista_usuarios_free(ListaUsuarios *listaUsuarios)
{
    for (int i = 0; i < listaUsuarios->count; i++)
        usuario_free(listaUsuarios->usuarios[i]);

    free(listaUsuarios->usuarios);
    free(listaUsuarios);
}

void lista_usuarios_print(ListaUsuarios *listaUsuarios) {
    printf("----- BANCO DE USUARIOS -----\n");

    for (int i = 0; i < listaUsuarios->count; i++)
    {
        printf("--------------------\n");
        usuario_print(listaUsuarios->usuarios[i]);
    }
    
    printf("----------------------------\n\n");
}