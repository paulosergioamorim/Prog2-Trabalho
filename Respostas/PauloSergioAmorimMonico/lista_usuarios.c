#include "lista_usuarios.h"
#include "constantes.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista_usuarios
{
    Usuario **usuarios;
    int size;
    int count;
};

ListaUsuarios *lista_usuarios_criar()
{
    ListaUsuarios *listaUsuarios = malloc(sizeof(ListaUsuarios));
    assert(listaUsuarios);

    listaUsuarios->size = LISTA_CAPACIDADE_INICIAL;
    listaUsuarios->count = 0;
    listaUsuarios->usuarios = malloc(listaUsuarios->size * sizeof(Usuario *));

    return listaUsuarios;
}

void lista_usuarios_adicionar(ListaUsuarios *listaUsuarios, Usuario *usuario)
{
    if (listaUsuarios->count + 1 == listaUsuarios->size)
    {
        listaUsuarios->size *= 2;
        listaUsuarios->usuarios = realloc(listaUsuarios->usuarios, listaUsuarios->size * sizeof(Usuario *));
    }

    listaUsuarios->usuarios[listaUsuarios->count] = usuario;
    listaUsuarios->count++;
}

void lista_usuarios_free(ListaUsuarios *listaUsuarios)
{
    for (int i = 0; i < listaUsuarios->count; i++)
        usuario_free(listaUsuarios->usuarios[i]);

    free(listaUsuarios->usuarios);
    free(listaUsuarios);
}

void lista_usuarios_print(ListaUsuarios *listaUsuarios)
{
    printf("----- BANCO DE USUARIOS -----\n");

    for (int i = 0; i < listaUsuarios->count; i++)
    {
        printf("--------------------\n");
        usuario_print(listaUsuarios->usuarios[i]);
    }

    printf("----------------------------\n\n");
}

Usuario *lista_usuarios_procura_por_cpf(ListaUsuarios *listaUsuarios, char *cpf)
{
    for (int i = 0; i < listaUsuarios->count; i++)
    {
        Usuario *usuario = listaUsuarios->usuarios[i];

        if (!usuario)
            continue;

        if (strcmp(usuario_recupera_cpf(usuario), cpf) == 0)
            return listaUsuarios->usuarios[i];
    }

    return NULL;
}

void lista_usuarios_print_por_ranking(ListaUsuarios *listaUsuarios)
{
    Usuario **sortedUsuarios = malloc(listaUsuarios->count * sizeof(Usuario *));
    memcpy(sortedUsuarios, listaUsuarios->usuarios, listaUsuarios->count * sizeof(Usuario *));
    qsort(sortedUsuarios, listaUsuarios->count, sizeof(Usuario *), qsort_compara_usuarios);

    printf("----- RANKING DE USUARIOS -----\n");

    for (int i = 0; i < listaUsuarios->count; i++)
    {
        printf("--------------------\n");
        usuario_print(sortedUsuarios[i]);
    }

    printf("-------------------------------\n\n");

    free(sortedUsuarios);
}

int lista_usuarios_quantidade(ListaUsuarios *listaUsuarios)
{
    return listaUsuarios->count;
}

int lista_usuarios_media_idade(ListaUsuarios *listaUsuarios)
{
    int soma = 0;
    Data *dataHoje = data_criar(18, 02, 2025);

    for (int i = 0; i < listaUsuarios->count; i++)
    {
        Data *data = usuario_recupera_data(listaUsuarios->usuarios[i]);
        int idade = data_anos_diferenca(data, dataHoje);
        soma += idade;
    }

    free(dataHoje);

    return soma / listaUsuarios->count;
}
