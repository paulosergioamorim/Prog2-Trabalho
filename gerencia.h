#pragma once

typedef struct gerencia *Gerencia;

Gerencia criarGerencia();

void realizarGerencia(Gerencia gerencia, const char opcao);

void liberarGerencia(Gerencia gerencia);