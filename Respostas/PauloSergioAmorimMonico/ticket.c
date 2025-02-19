#include "ticket.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ticket {
  void *ticket;
  char *id;
  char *status;
  char *cpf;
  func_ptr_notifica notifica;
  func_ptr_desaloca desaloca;
};

/**
 * @brief Aloca uma estrutura Ticket na memória e inicializa os parâmetro
 * necessários
 * @param cpfSol CPF de quem está solicitando a abertura do ticket
 * @param dado   Um ticket genérico  (considerando que existe mais de um tipo de
 * ticket)
 * @param getTempo  Função de callback que retorna o tempo para aquele ticket
 * ser resolvido
 * @param getTipo   Função de callback que retorna o tipo do ticket ser
 * resolvido
 * @param notifica  Função de callback de notificação  (impressãode um ticket
 * @param desaloca  Função de callback que irá desalocar  um ticket da memória
 * @return  Uma estrutura Ticket inicializada.
 */
Ticket *criaTicket(char *cpfSol, void *dado, func_ptr_tempoEstimado getTempo,
                   func_ptr_tipo getTipo, func_ptr_notifica notifica,
                   func_ptr_desaloca desaloca) {
  Ticket *pTicket = malloc(sizeof(struct Ticket));
  assert(pTicket);

  pTicket->cpf = cpfSol;
  pTicket->ticket = dado;
  pTicket->notifica = notifica;
  pTicket->desaloca = desaloca;
}

/**
 * @brief Atribui um ID a um ticket
 * @param d Ticket inicializado
 * @param id ID a ser atribuido ao ticket
 */
void setIDTicket(Ticket *d, char *id);

/**
 * @brief Finaliza um ticket
 * @param t Ticket inicializado
 */
void finalizaTicket(Ticket *t);

/**
 * @brief Recupera o CPF de quem solicitou a abertura do ticket
 * @param t Ticket inicializado
 * @return CPF de quem solicitou a abertura do ticket
 */
char *getCPFSolicitanteTicket(Ticket *t);

/**
 * @brief Recupera o tempo estimado para resolver um ticket
 * @param t Ticket inicializado
 * @return tempo estimado para resolver um ticket
 */
int getTempoEstimadoTicket(Ticket *t);

/**
 * @brief Recupera o tipo de um ticket
 * @param t Ticket inicializado
 * @return tipo do Ticket
 */
char getTipoTicket(Ticket *t);

/**
 * @brief Recupera o status de um ticket
 * @param t Ticket inicializado
 * @return status do Ticket
 */
char getStatusTicket(Ticket *t) {
    return t->status;
}

/**
 * @brief  Desaloca um ticket da memória
 * @param doc estrutura do tipo Ticket que deve ser liberada da memória
 */
void desalocaTicket(Ticket *doc);

/**
 * @brief  Notifica (imprime) um ticket
 * @param doc Ticket a ser notificado
 */
void notificaTicket(Ticket *doc);
