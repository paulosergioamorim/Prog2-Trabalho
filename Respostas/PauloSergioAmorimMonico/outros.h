
#pragma once

#define OUTROS_DESCRICAO 500
#define OUTROS_LOCAL 100

/**
 * Estrutura de um Ticket Outros contendo os parametros especificos de um ticket do tipo Outros
 */
typedef struct Outros Outros;

Outros *criaOutros(char *descricao, char *local, int nivelDificuldade);

/**
 * @brief Lê da entrada padrão um  ticket do TIPO Outros
 * @return  Um chamado do Tipo Outros
 */
Outros *lerOutros();

/**
 * @brief  Calcula o tempo estimado para resolver um ticket do tipo Outros.
 * Tempo estimado depende da categoria e impacto
 * @param s  Ticket do tipo Outros
 */
void setTempoEstimadoOutros(Outros *s);

/**
 * @brief  Retorna o tempo estimado para resolver um ticket do tipo Outros.
 * @param dado  Ticket do tipo Outros
 * @return  Tempo estimado para resolver um ticket do tipo Outros
 */
int getTempoEstimadoOutros(void *dado);

/**
 * @brief  Retorna o tipo do ticket
 * @return  'S' para Outros
 */
char getTipoOutros();

/**
 * @brief  Desaloca um ticket do tipo Outros da memória
 * @param s  Ticket do tipo Outros
 */
void desalocaOutros(void *s);

/**
 * @brief  Imprime um ticket do tipo Outros
 * @param dado  Ticket do tipo Outros
 */
void notificaOutros(void *dado);
