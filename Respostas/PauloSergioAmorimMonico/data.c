#include "data.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct data
{
    int dia;
    int mes;
    int ano;
};

Data *data_criar(int dia, int mes, int ano)
{
    Data *pData = malloc(sizeof(struct data));
    assert(pData);

    pData->dia = dia;
    pData->mes = mes;
    pData->ano = ano;

    return pData;
}

Data *data_ler()
{
    int dia = 0;
    int mes = 0;
    int ano = 0;

    scanf("%d/%d/%d%*c", &dia, &mes, &ano);

    return data_criar(dia, mes, ano);
}

void data_print(Data *data)
{
    printf("%d/%d/%d\n", data->dia, data->mes, data->ano);
}

int data_e_valida(Data *data)
{
    if (data->dia < 1 || 31 < data->dia)
        return 0;

    if (data->mes < 1 || 12 < data->mes)
        return 0;

    if (data->ano < 0)
        return 0;

    switch (data->mes)
    {
    case 2:
        if (data_e_ano_bissexto(data))
        {
            if (data->dia > 29)
                return 0;
        }
        else if (data->dia > 28)
            return 0;
        break;
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if (data->dia > 31)
            return 0;
        break;
    default:
        if (data->dia > 30)
            return 0;
        break;
    }

    return 1;
}

int data_e_ano_bissexto(Data *data)
{
    return data->ano % 4 == 0 || (data->ano % 100 == 0 && data->ano % 400 == 0);
}

int data_anos_diferenca(Data *dataInicio, Data *dataFim)
{
    int years = dataFim->ano - dataInicio->ano;

    if (dataFim->mes > dataInicio->mes)
        years--;

    if (dataFim->mes == dataInicio->mes && dataFim->mes > dataInicio->mes)
        years--;

    return years;
}

int data_comparar(void *pData1, void *pData2)
{
    Data *date1 = *(Data **)pData1;
    Data *date2 = *(Data **)pData2;

    if (date2->ano > date1->ano)
        return 1;

    if (date2->ano < date1->ano)
        return -1;

    if (date2->mes > date1->mes)
        return 1;

    if (date2->mes < date1->mes)
        return -1;

    if (date2->dia > date1->dia)
        return 1;

    if (date2->dia < date1->dia)
        return -1;

    return 0;
}

void data_free(Data *date)
{
    assert(date);
    free(date);
}
