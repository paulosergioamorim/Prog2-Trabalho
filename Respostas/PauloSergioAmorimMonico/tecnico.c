#include "tecnico.h"
#include "ticket.h"
#include "constantes.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tecnico
{
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    Data *data;
    char genero[TAM_GENERO];
    char telefone[TAM_TELEFONE];
    char areaAtuacao[TAM_AREA_ATUACAO];
    float salario;
    int disponibilidadeTempo;
    int tempoTrabalhado;
};

Tecnico *tecnico_criar(char *nome, char *cpf, Data *data, char *genero, char *telefone, char *areaAtuacao,
                       float salario, int disponibilidadeTempo)
{
    Tecnico *tecnico = malloc(sizeof(Tecnico));
    assert(tecnico);

    strcpy(tecnico->nome, nome);
    strcpy(tecnico->cpf, cpf);
    tecnico->data = data;
    strcpy(tecnico->telefone, telefone);
    strcpy(tecnico->genero, genero);
    strcpy(tecnico->areaAtuacao, areaAtuacao);
    tecnico->salario = salario;
    tecnico->disponibilidadeTempo = disponibilidadeTempo;
    tecnico->tempoTrabalhado = 0;

    return tecnico;
}

/*
HEIMERDINGER GARCIA
456.987.123-96
20/10/1945
(90)99876-1234
MASCULINO
GERAL
20
3500
*/

Tecnico *tecnico_ler()
{
    char nome[TAM_NOME] = "";
    char cpf[TAM_CPF] = "";
    Data *data = NULL;
    char telefone[TAM_TELEFONE] = "";
    char genero[TAM_GENERO] = "";
    char areaAtuacao[TAM_AREA_ATUACAO] = "";
    float salario = 0;
    int disponibilidadeTempo = 0;

    scanf("%[^\n]%*c", nome);
    scanf("%[^\n]%*c", cpf);
    data = data_ler();
    scanf("%[^\n]%*c", telefone);
    scanf("%[^\n]%*c", genero);
    scanf("%[^\n]%*c", areaAtuacao);
    scanf("%d%*c", &disponibilidadeTempo);
    scanf("%f%*c", &salario);

    return tecnico_criar(nome, cpf, data, genero, telefone, areaAtuacao, salario, disponibilidadeTempo);
}

int tecnico_e_mesmo_cpf(Tecnico *tecnico, char *cpf)
{
    return strcmp(tecnico->cpf, cpf) == 0;
}

/*
- Nome: JAYCE BARBOSA
- CPF: 854.632.894-20
- Data de Nascimento: 22/2/1990
- Telefone: (37)9938-3382
- Genero: MASCULINO
- Area de Atuacao: GERAL
- Salario: 2000.00
- Disponibilidade: 7h
- Tempo Trabalhado: 0h
*/
void tecnico_print(Tecnico *tecnico) {
    printf("- Nome: %s\n", tecnico->nome);
    printf("- CPF: %s\n", tecnico->cpf);
    printf("- Data de Nascimento: ");
    data_print(tecnico->data);
    printf("- Telefone: %s\n", tecnico->telefone);
    printf("- Genero: %s\n", tecnico->genero);
    printf("- Area de Atuacao: %s\n", tecnico->areaAtuacao);
    printf("- Salario: %.2f\n", tecnico->salario);
    printf("- Disponibilidade: %dh\n", tecnico->disponibilidadeTempo);
    printf("- Tempo Trabalhado: %dh\n", tecnico->tempoTrabalhado);
}

void tecnico_free(Tecnico *tecnico)
{
    data_free(tecnico->data);
    free(tecnico);
}

int tecnico_recupera_disponibilidade(Tecnico *tecnico) {
    return tecnico->disponibilidadeTempo;
}

void tecnico_pegar_ticket(Tecnico *tecnico, Ticket *ticket) {
    int tempoEstimado = getTempoEstimadoTicket(ticket);
    tecnico->disponibilidadeTempo -= tempoEstimado;
    tecnico->tempoTrabalhado += tempoEstimado;
    finalizaTicket(ticket);
}

int tecnico_habil_para_ticket(Tecnico *tecnico, Ticket *ticket) {
    char tipo = getTipoTicket(ticket);

    if (tipo == 'S')
        return strcmp(tecnico->areaAtuacao, "TI") == 0;

    if (strcmp(tecnico->areaAtuacao, "TI") == 0)
        return tipo == 'S';

    return strcmp(tecnico->areaAtuacao, "GERAL") == 0;
}

int tecnico_tem_disponibilidade(Tecnico *tecnico, Ticket *ticket) {
    int tempoEstimado = getTempoEstimadoTicket(ticket);

    return tecnico->disponibilidadeTempo >= tempoEstimado;
}

int qsort_compara_tecnicos(const void * p1, const void * p2) {
    Tecnico * t1 = *(Tecnico **) p1;
    Tecnico * t2 = *(Tecnico **) p2;

    return t2->tempoTrabalhado >= t1->tempoTrabalhado;
}

int tecnico_recupera_tempo_trabalhado(Tecnico *tecnico) {
    return tecnico->tempoTrabalhado;
}

Data *tecnico_recupera_data(Tecnico *tecnico) {
    return tecnico->data;
}