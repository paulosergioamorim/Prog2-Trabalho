#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hardware.h"

struct Hardware {
    char nome[MAX_TAM_NOME_HARDWARE];
    int tipoMaquina;
    int tipoProblema;
    char motivo[MAX_TAM_MOTIVO_HARDWARE];
    int tempoEstimado;
};

/**
 * @brief Aloca uma estrutura Hardware na memória e inicializa os parâmetro necessários
 * @param nome Nome do Hardware
 * @param categoria Categoria do Hardware
 * @param impacto Impacto do chamado
 * @param motivo Motivo da abertura do ticket
 * @return  Uma estrutura Hardware inicializada.
 */
Hardware *criaHardware(char *nome, int tipoMaquina, int tipoProblema, char *motivo) {
    Hardware *hardware = malloc(sizeof(Hardware));

    memset(hardware->nome, 0, MAX_TAM_NOME_HARDWARE);
    memset(hardware->motivo, 0, MAX_TAM_MOTIVO_HARDWARE);
    strcpy(hardware->nome, nome);
    strcpy(hardware->motivo, motivo);
    hardware->tipoMaquina = tipoMaquina;
    hardware->tipoProblema = tipoProblema;
    hardware->tempoEstimado = 0;

    return hardware;
}

/**
 * @brief Lê da entrada padrão um  ticket do TIPO Hardware
 * @return  Um chamado do Tipo Hardware
 */
Hardware *lerHardware() {
    char nome[MAX_TAM_NOME_HARDWARE] = "";
    int tipoMaquina = 0;
    int tipoProblema = 0;
    char motivo[MAX_TAM_MOTIVO_HARDWARE] = "";

    scanf("%[^\n]\n", nome);
    scanf("%d\n", &tipoMaquina);
    scanf("%d\n", &tipoProblema);
    scanf("%[^\n]\n", motivo);

    return criaHardware(nome, tipoMaquina, tipoProblema, motivo);
}

/**
 * @brief  Calcula o tempo estimado para resolver um ticket do tipo Hardware.
 * Tempo estimado depende da categoria e impacto
 * @param s  Ticket do tipo Hardware
 */
void setTempoEstimadoHardware(Hardware *s) {
    s->tempoEstimado = s->tipoMaquina + s->tipoProblema;
}

/**
 * @brief  Retorna o tempo estimado para resolver um ticket do tipo Hardware.
 * @param dado  Ticket do tipo Hardware
 * @return  Tempo estimado para resolver um ticket do tipo Hardware
 */
int getTempoEstimadoHardware(void *dado) {
    Hardware *hardware = (Hardware *)dado;

    return hardware->tempoEstimado;
}

/**
 * @brief  Retorna o tipo do ticket
 * @return  'H' para Hardware
 */
char getTipoHardware() {
    return 'H';
}

/**
 * @brief  Desaloca um ticket do tipo Hardware da memória
 * @param s  Ticket do tipo Hardware
 */
void desalocaHardware(void *s) {
    free(s);
}

/**
 * @brief  Imprime um ticket do tipo Hardware
 * @param dado  Ticket do tipo Hardware
 */
void notificaHardware(void *dado) {
    Hardware *hardware = (Hardware *)dado;

    /*
- ID: Tick-1
- Usuario solicitante: 913.802.467-80
- Tipo: Hardware
- Nome do hardware: ZTX-3852
- Tipo da maquina: 2
- Tipo do problema: 2
- Motivo: A MAQUINA APRESENTA UM BARULHO ESTRANHO
- Tempo estimado: 4h
- Status: Aberto
    */
    
    printf("- Tipo: Hardware\n");
    printf("- Nome do hardware: %s\n", hardware->nome);
    printf("- Tipo da maquina: %d\n", hardware->tipoMaquina);
    printf("- Tipo do problema: %d\n", hardware->tipoProblema);
    printf("- Motivo: %s\n", hardware->motivo);
    printf("- Tempo estimado: %dh\n", hardware->tempoEstimado);
}