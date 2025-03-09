#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

#define TAM_INICIAL 10

struct Fila
{
    Ticket **tickets;
    int size;
    int count;
};

/**
 * @brief Aloca uma estrutura Fila na memória e inicializa os parâmetro necessários
 * @return  Uma Fila inicializada.
 */
Fila *criaFila()
{
    Fila *fila = malloc(sizeof(Fila));

    fila->tickets = malloc(TAM_INICIAL * sizeof(Ticket *));
    fila->size = TAM_INICIAL;
    fila->count = 0;

    return fila;
}

/**
 * @brief  Desaloca uma fila da memória
 * @param f estrutura do tipo Fila que deve ser liberada da memória
 * @return (void)
 */
void desalocaFila(Fila *f)
{
    for (int i = 0; i < f->count; i++)
        desalocaTicket(f->tickets[i]);

    free(f->tickets);
    free(f);
    f = NULL;
}

/**
 * @brief  Insere um ticket na fila de processamento. Um ticket deve ser inserido sempre na última posição.
 * Obviamente, essa função também faz a manipulação de memória necessária para alocar um novo ticket.
 * @param f  Fila que receberá o novo ticket
 * @param cpfSol CPF de quem está solicitando a abertura do ticket
 * @param dado   Um ticket genérico  (considerando que existe mais de um tipo de ticket)
 * @param getTempo  Função de callback que retorna o tempo para aquele ticket ser resolvido (ver ticket.h)
 * @param getTipo   Função de callback que retorna o tipo do ticket ser resolvido (ver ticket.h)
 * @param notifica  Função de callback de notificação de um ticket (ver ticket.h)
 * @param desaloca  Função de callback que desaloca  um ticket da memória (ver ticket.h)
 */
void insereTicketFila(Fila *f, char *cpfSol, void *dado, func_ptr_tempoEstimado getTempo, func_ptr_tipo getTipo,
                      func_ptr_notifica notifica, func_ptr_desaloca desaloca)
{
    if (f->count == f->size)
    {
        f->size *= 2;
        f->tickets = realloc(f->tickets, f->size * sizeof(Ticket *));
    }

    Ticket *ticket = criaTicket(cpfSol, dado, getTempo, getTipo, notifica, desaloca);
    char id[20] = "";
    sprintf(id, "Tick-%d", f->count + 1);
    setIDTicket(ticket, id);
    f->tickets[f->count] = ticket;
    f->count++;
}

/**
 * @brief Recupera a quantidade de tickets  em uma fila
 * @param f  Estrutura Fila inicializada.
 * @return Quantidade de Tickets na fila
 */
int getQtdTicketsNaFila(Fila *f)
{
    return f->count;
}

/**
 * @brief Recupera a quantidade de tickets em uma fila com um determinado status
 * @param f  Estrutura Fila inicializada.
 * @param status Status do ticket
 * @return Quantidade de Tickets na fila com o status informado
 */
int getQtdTicketsPorStatusNaFila(Fila *f, char status)
{
    int count = 0;

    for (int i = 0; i < f->count; i++)
        if (getStatusTicket(f->tickets[i]) == status)
            count++;

    return count;
}

/**
 * @brief Recupera um ticket na fila de processamento. Um ticket deve ser recuperado sempre na i-ésima posição.
 * @param f  Fila que contém o ticket
 * @param i  Posição do ticket na fila
 * @return  Ticket recuperado da fila
 */
Ticket *getTicketNaFila(Fila *f, int i) {
    if (i < 0 || i >= f->count)
        return NULL;
    
    return f->tickets[i];
}

/**
 * @brief A função notificaFila imprime todos os tickets na Fila f
 * @param f  Fila inicializada contendo zero ou mais tickets.
 */
void notificaFila(Fila *f) {
    for (int i = 0; i < f->count; i++)
        notificaTicket(f->tickets[i]);
}
