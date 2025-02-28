#pragma once

#include "data.h"
#include "ticket.h"

typedef struct tecnico Tecnico;

Tecnico *tecnico_criar(char *nome, char *cpf, Data *data, char *genero, char *telefone, char *areaAtuacao,
                       float salario, int disponibilidadeTempo);

Tecnico *tecnico_ler();

int tecnico_e_mesmo_cpf(Tecnico *tecnico, char *cpf);

void tecnico_print(Tecnico *tecnico);

void tecnico_free(Tecnico *tecnico);

int tecnico_recupera_disponibilidade(Tecnico *tecnico);

void tecnico_pegar_ticket(Tecnico *tecnico, Ticket *ticket);

int tecnico_habil_para_ticket(Tecnico *tecnico, Ticket *ticket);

int tecnico_tem_disponibilidade(Tecnico *tecnico, Ticket *ticket);

Data *tecnico_recupera_data(Tecnico *tecnico);

int tecnico_recupera_tempo_trabalhado(Tecnico *tecnico);

int qsort_compara_tecnicos(const void *p1, const void *p2);
