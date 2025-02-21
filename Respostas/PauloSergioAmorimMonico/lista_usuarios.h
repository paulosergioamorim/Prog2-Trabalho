#pragma once

#include "usuario.h"

typedef struct lista_usuarios ListaUsuarios;

ListaUsuarios *lista_usuarios_criar();

ListaUsuarios *lista_usuarios_adicionar(ListaUsuarios *listaUsuarios, Usuario *usuario);

void lista_usuarios_free(ListaUsuarios *listaUsuarios);

void lista_usuarios_print(ListaUsuarios *listaUsuarios);
