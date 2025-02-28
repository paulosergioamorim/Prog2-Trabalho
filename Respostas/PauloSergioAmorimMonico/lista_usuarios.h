#pragma once

#include "usuario.h"

typedef struct lista_usuarios ListaUsuarios;

ListaUsuarios *lista_usuarios_criar();

void lista_usuarios_adicionar(ListaUsuarios *listaUsuarios, Usuario *usuario);

void lista_usuarios_free(ListaUsuarios *listaUsuarios);

void lista_usuarios_print(ListaUsuarios *listaUsuarios);

Usuario *lista_usuarios_procura_por_cpf(ListaUsuarios *listaUsuarios, char *cpf);

void lista_usuarios_print_por_ranking(ListaUsuarios *listaUsuarios);

int lista_usuarios_quantidade(ListaUsuarios *listaUsuarios);

int lista_usuarios_media_idade(ListaUsuarios *listaUsuarios);