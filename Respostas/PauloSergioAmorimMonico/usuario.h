#pragma once

#include "data.h"

typedef struct usuario *Usuario;

Usuario criarUsuario(char *nome, char *cpf, Data* data, char *telefone, char *genero, char *setorTrabalho);

Usuario lerUsuario();

int eMesmoCPFUsuario(Usuario usuario, char *cpf);

void imprimirUsuario(Usuario usuario);

void liberarUsuario(Usuario usuario);

char *getCPFUsuario(Usuario usuario);

char *getSetorUsuario(Usuario usuario);

void addSolicitacaoUsuario(Usuario usuario);

int getSolicitacoesUsuario(Usuario usuario);

int compararUsuarios(const void * p1, const void * p2);

int getIdadeUsuario(Usuario usuario);
