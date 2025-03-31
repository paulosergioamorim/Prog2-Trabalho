#include "tecnico.h"
#include "constantes.h"
#include "ticket.h"
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

Tecnico criarTecnico(char *nome, char *cpf, Data *data, char *genero, char *telefone, char *areaAtuacao, float salario,
                      int disponibilidadeTempo)
{
    Tecnico tecnico = malloc(sizeof(struct tecnico));

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

Tecnico lerTecnico()
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
    data = lerData();
    scanf("%[^\n]%*c", telefone);
    scanf("%[^\n]%*c", genero);
    scanf("%[^\n]%*c", areaAtuacao);
    scanf("%d%*c", &disponibilidadeTempo);
    scanf("%f%*c", &salario);

    return criarTecnico(nome, cpf, data, genero, telefone, areaAtuacao, salario, disponibilidadeTempo);
}

int eMesmoCPFTecnico(Tecnico tecnico, char *cpf)
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
void imprimirTecnico(Tecnico tecnico)
{
    printf("--------------------\n");
    printf("- Nome: %s\n", tecnico->nome);
    printf("- CPF: %s\n", tecnico->cpf);
    printf("- Data de Nascimento: ");
    imprimirData(tecnico->data);
    printf("- Telefone: %s\n", tecnico->telefone);
    printf("- Genero: %s\n", tecnico->genero);
    printf("- Area de Atuacao: %s\n", tecnico->areaAtuacao);
    printf("- Salario: %.2f\n", tecnico->salario);
    printf("- Disponibilidade: %dh\n", tecnico->disponibilidadeTempo);
    printf("- Tempo Trabalhado: %dh\n", tecnico->tempoTrabalhado);
}

void liberarTecnico(Tecnico tecnico)
{
    liberarData(tecnico->data);
    free(tecnico);
}

int getDisponibilidadeTecnico(Tecnico tecnico)
{
    return tecnico->disponibilidadeTempo;
}

void pegarTicketTecnico(Tecnico tecnico, Ticket *ticket)
{
    int tempoEstimado = getTempoEstimadoTicket(ticket);
    tecnico->disponibilidadeTempo -= tempoEstimado;
    tecnico->tempoTrabalhado += tempoEstimado;
    finalizaTicket(ticket);
}

int podePegarTicketTecnico(Tecnico tecnico, Ticket *ticket)
{
    if (tecnico->disponibilidadeTempo < getTempoEstimadoTicket(ticket))
        return 0;

    char tipo = getTipoTicket(ticket);

    if (tipo == 'H')
        return strcmp(tecnico->areaAtuacao, "ENGENHEIRO") == 0;

    if (tipo == 'S') 
        return strcmp(tecnico->areaAtuacao, "TI") == 0;

    if (strcmp(tecnico->areaAtuacao, "TI") == 0)
        return tipo == 'S';

    return 1;
}

int compararTecnicos(const void *p1, const void *p2)
{
    Tecnico t1 = *(Tecnico *)p1;
    Tecnico t2 = *(Tecnico *)p2;

    if (t2->tempoTrabalhado == t1->tempoTrabalhado)
        return strcmp(t1->nome, t2->nome);

    return t2->tempoTrabalhado - t1->tempoTrabalhado;
}

int getTempoTrabalhadoTecnico(Tecnico tecnico)
{
    return tecnico->tempoTrabalhado;
}

int getIdadeTecnico(Tecnico tecnico)
{
    Data *dataHoje = criarData(18, 02, 2025);

    int anos = getAnosDiferencaData(tecnico->data, dataHoje);

    liberarData(dataHoje);

    return anos;
}

char *getCPFTecnico(Tecnico tecnico)
{
    return tecnico->cpf;
}

int getSalarioTecnico(Tecnico tecnico) {
    return (int)tecnico->salario;
}