#pragma once

#define MAX_TAM_NOME_MANUTENCAO 100
#define MAX_TAM_ESTADO_MANUTENCAO sizeof("REGULAR")
#define MAX_TAM_LOCAL_MANUTENCAO 100

/**
 * Estrutura de um Ticket Manutencao contendo os parametros especificos de um ticket do tipo Manutencao
 */
typedef struct Manutencao Manutencao;

Manutencao *criaManutencao(char *nome, char *estado, char *local);

/**
 * @brief Lê da entrada padrão um  ticket do TIPO Manutencao
 * @return  Um chamado do Tipo Manutencao
 */
Manutencao *lerManutencao();

/**
 * @brief  Calcula o tempo estimado para resolver um ticket do tipo Manutencao.
 * Tempo estimado depende da categoria e impacto
 * @param s  Ticket do tipo Manutencao
 */
void setTempoEstimadoManutencao(Manutencao *s);

/**
 * @brief  Retorna o tempo estimado para resolver um ticket do tipo Manutencao.
 * @param dado  Ticket do tipo Manutencao
 * @return  Tempo estimado para resolver um ticket do tipo Manutencao
 */
int getTempoEstimadoManutencao(void *dado);

/**
 * @brief  Retorna o tipo do ticket
 * @return  'S' para Manutencao
 */
char getTipoManutencao();

/**
 * @brief  Desaloca um ticket do tipo Manutencao da memória
 * @param s  Ticket do tipo Manutencao
 */
void desalocaManutencao(void *s);

/**
 * @brief  Imprime um ticket do tipo Manutencao
 * @param dado  Ticket do tipo Manutencao
 */
void notificaManutencao(void *dado);

void setSetor(Manutencao *manutencao, char *setor);
