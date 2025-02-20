#include "tecnico.h"
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
    Tecnico *pTecnico = malloc(sizeof(struct tecnico));
    assert(pTecnico);

    strcpy(pTecnico->nome, nome);
    strcpy(pTecnico->cpf, cpf);
    pTecnico->data = data;
    strcpy(pTecnico->telefone, telefone);
    strcpy(pTecnico->genero, genero);
    strcpy(pTecnico->areaAtuacao, areaAtuacao);
    pTecnico->salario = salario;
    pTecnico->disponibilidadeTempo = disponibilidadeTempo;
    pTecnico->tempoTrabalhado = 0;

    return pTecnico;
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
