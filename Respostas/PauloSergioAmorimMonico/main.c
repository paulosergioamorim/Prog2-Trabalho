#include "constantes.h"
#include "fila.h"
#include "lista_tecnicos.h"
#include "lista_usuarios.h"
#include "manutencao.h"
#include "outros.h"
#include "software.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprimirRelatorioGeral(Fila *tickets, ListaTecnicos *listaTecnicos, ListaUsuarios *listaUsuarios);

int main(int argc, char const *argv[])
{
    Fila *tickets = criaFila();
    ListaTecnicos *listaTecnicos = lista_tecnicos_criar();
    ListaUsuarios *listaUsuarios = lista_usuarios_criar();

    char op = 0;

    while (1)
    {
        scanf("%c%*c", &op);

        if (op == 'F')
            break;

        if (op == 'E')
        {
            char comando[50] = "";
            scanf("%[^\n]%*c", comando);

            if (strcmp(comando, "TECNICOS") == 0)
                lista_tecnicos_print(listaTecnicos);

            if (strcmp(comando, "RANKING TECNICOS") == 0)
                lista_tecnicos_print_por_ranking(listaTecnicos);

            else if (strcmp(comando, "USUARIOS") == 0)
                lista_usuarios_print(listaUsuarios);

            else if (strcmp(comando, "RANKING USUARIOS") == 0)
                lista_usuarios_print_por_ranking(listaUsuarios);

            else if (strcmp(comando, "DISTRIBUI") == 0)
            {
                int countTickets = getQtdTicketsNaFila(tickets);
                int countTecnicos = lista_tecnicos_quantidade(listaTecnicos);

                for (int i = 0; i < countTickets; i++)
                {
                    Ticket *ticket = getTicketNaFila(tickets, i);

                    if (getStatusTicket(ticket) == 'F')
                        continue;

                    for (int j = 0; j < countTecnicos; j++)
                    {
                        Tecnico *tecnico = lista_tecnicos_tecnico(listaTecnicos, j);

                        if (!tecnico_tem_disponibilidade(tecnico, ticket) || tecnico_habil_para_ticket(tecnico, ticket))
                            continue;

                        tecnico_pegar_ticket(tecnico, ticket);
                        break;
                    }
                }
            }

            else if (strcmp(comando, "NOTIFICA") == 0)
            {
                printf("----- FILA DE TICKETS -----\n");
                notificaFila(tickets);
                printf("---------------------------\n\n");
            }

            else if (strcmp(comando, "RELATORIO") == 0)
                imprimirRelatorioGeral(tickets, listaTecnicos, listaUsuarios);
        }

        else if (op == 'T')
        {
            Tecnico *tecnico = tecnico_ler();
            lista_tecnicos_adicionar(listaTecnicos, tecnico);
        }

        else if (op == 'U')
        {
            Usuario *usuario = usuario_ler();
            lista_usuarios_adicionar(listaUsuarios, usuario);
        }

        else if (op == 'A')
        {
            char cpfSol[TAM_CPF] = "";
            char tipoTicket[MAX_LENGTH_TIPO_TICKET] = "";
            scanf("%[^\n]%*c", cpfSol);
            scanf("%[^\n]%*c", tipoTicket);

            Usuario *solicitante = lista_usuarios_procura_por_cpf(listaUsuarios, cpfSol);

            if (strcmp(tipoTicket, "MANUTENCAO") == 0)
            {
                Manutencao *manutecao = lerManutencao();

                if (!solicitante)
                {
                    desalocaManutencao(manutecao);
                    continue;
                }

                setSetor(manutecao, usuario_recupera_setor(solicitante));

                insereTicketFila(tickets, cpfSol, manutecao, getTempoEstimadoManutencao, getTipoManutencao,
                                 notificaManutencao, desalocaManutencao);
            }

            else if (strcmp(tipoTicket, "SOFTWARE") == 0)
            {
                Software *software = lerSoftware();

                if (!solicitante)
                {
                    desalocaSoftware(software);
                    continue;
                }

                insereTicketFila(tickets, cpfSol, software, getTempoEstimadoSoftware, getTipoSoftware, notificaSoftware,
                                 desalocaSoftware);
            }

            else if (strcmp(tipoTicket, "OUTROS") == 0)
            {
                Outros *outros = lerOutros();

                if (!solicitante)
                {
                    desalocaOutros(outros);
                    continue;
                }

                insereTicketFila(tickets, cpfSol, outros, getTempoEstimadoOutros, getTipoOutros, notificaOutros,
                                 desalocaOutros);
            }

            usuario_incrementa_solicitacoes(solicitante);
        }
    }

    desalocaFila(tickets);
    lista_tecnicos_free(listaTecnicos);
    lista_usuarios_free(listaUsuarios);

    return 0;
}

void imprimirRelatorioGeral(Fila *tickets, ListaTecnicos *listaTecnicos, ListaUsuarios *listaUsuarios)
{
    printf("----- RELATORIO GERAL -----\n");
    printf("- Qtd tickets: %d\n", getQtdTicketsNaFila(tickets));
    printf("- Qtd tickets (A): %d\n", getQtdTicketsPorStatusNaFila(tickets, 'A'));
    printf("- Qtd tickets (F): %d\n", getQtdTicketsPorStatusNaFila(tickets, 'F'));
    printf("- Qtd usuarios: %d\n", lista_usuarios_quantidade(listaUsuarios));
    printf("- Md idade usuarios: %d\n", lista_usuarios_media_idade(listaUsuarios));
    printf("- Qtd tecnicos: %d\n", lista_tecnicos_quantidade(listaTecnicos));
    printf("- Md idade tecnicos: %d\n", lista_tecnicos_media_idade(listaTecnicos));
    printf("- Md trabalho tecnicos: %d\n", lista_tecnicos_media_trabalho(listaTecnicos));
    printf("---------------------------\n\n");
}
