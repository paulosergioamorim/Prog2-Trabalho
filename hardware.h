#pragma once

#define MAX_TAM_NOME_HARDWARE 100
#define MAX_TAM_MOTIVO_HARDWARE 500

/**
 * Estrutura de um Ticket Hardware contendo os parametros especificos de um ticket do tipo Hardware
 */
typedef struct Hardware Hardware;

/**
 * @brief Aloca uma estrutura Hardware na memória e inicializa os parâmetro necessários
 * @param nome Nome do Hardware
 * @param categoria Categoria do Hardware
 * @param impacto Impacto do chamado
 * @param motivo Motivo da abertura do ticket
 * @return  Uma estrutura Hardware inicializada.
 */
Hardware *criaHardware(char *nome, int tipoMaquina, int tipoProblema, char *motivo);

/**
 * @brief Lê da entrada padrão um  ticket do TIPO Hardware
 * @return  Um chamado do Tipo Hardware
 */
Hardware *lerHardware();

/**
 * @brief  Calcula o tempo estimado para resolver um ticket do tipo Hardware.
 * Tempo estimado depende da categoria e impacto
 * @param s  Ticket do tipo Hardware
 */
void setTempoEstimadoHardware(Hardware *s);

/**
 * @brief  Retorna o tempo estimado para resolver um ticket do tipo Hardware.
 * @param dado  Ticket do tipo Hardware
 * @return  Tempo estimado para resolver um ticket do tipo Hardware
 */
int getTempoEstimadoHardware(void *dado);

/**
 * @brief  Retorna o tipo do ticket
 * @return  'H' para Hardware
 */
char getTipoHardware();

/**
 * @brief  Desaloca um ticket do tipo Hardware da memória
 * @param s  Ticket do tipo Hardware
 */
void desalocaHardware(void *s);

/**
 * @brief  Imprime um ticket do tipo Hardware
 * @param dado  Ticket do tipo Hardware
 */
void notificaHardware(void *dado);
