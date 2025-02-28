#pragma once

typedef struct gerencia *Gerencia;

Gerencia criarGerencia();

void realizarGerencia(Gerencia gerencia);

void liberarGerencia(Gerencia gerencia);