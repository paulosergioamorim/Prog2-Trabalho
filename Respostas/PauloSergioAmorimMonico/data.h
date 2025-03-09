#pragma once

typedef struct data Data;

Data *criarData(int dia, int mes, int ano);

Data *lerData();

void imprimirData(Data *data);

int eDataValida(Data *data);

int eAnoBissextoData(Data *data);

int getAnosDiferencaData(Data *data1, Data *data2);

int compararDatas(void *pData1, void *pData2);

void liberarData(Data *data);
