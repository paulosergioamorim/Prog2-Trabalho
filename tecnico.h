#pragma once

#include "data.h"
#include "ticket.h"

typedef struct tecnico *Tecnico;

Tecnico criarTecnico(char *nome, char *cpf, Data *data, char *genero, char *telefone, char *areaAtuacao,
                       float salario, int disponibilidadeTempo);

Tecnico lerTecnico();

int eMesmoCPFTecnico(Tecnico tecnico, char *cpf);

void imprimirTecnico(Tecnico tecnico);

void liberarTecnico(Tecnico tecnico);

int getDisponibilidadeTecnico(Tecnico tecnico);

void pegarTicketTecnico(Tecnico tecnico, Ticket *ticket);

int podePegarTicketTecnico(Tecnico tecnico, Ticket *ticket);

char *getCPFTecnico(Tecnico tecnico);

int getIdadeTecnico(Tecnico tecnico);

int getTempoTrabalhadoTecnico(Tecnico tecnico);

int compararTecnicos(const void *p1, const void *p2);

int getSalarioTecnico(Tecnico tecnico);
