#pragma once

typedef struct data Data;

Data *data_criar(int dia, int mes, int ano);

void data_print(Data *data);

int data_e_valida(Data *data);

int data_e_ano_bissexto(Data *data);

int data_anos_diferenca(Data *data1, Data *data2);

int data_comparar(void *pData1, void *pData2);

void data_free(Data *data);
