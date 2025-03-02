#pragma once

typedef struct gerencia *Gerencia;

Gerencia criarGerencia();

void handleOption(Gerencia gerencia, const char option);

void liberarGerencia(Gerencia gerencia);