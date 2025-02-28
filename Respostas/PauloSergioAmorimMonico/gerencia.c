#include "gerencia.h"
#include "constantes.h"
#include "fila.h"
#include "lista_tecnicos.h"
#include "lista_usuarios.h"
#include "manutencao.h"
#include "outros.h"
#include "software.h"
#include <stdio.h>
#include <stdlib.h>

struct gerencia
{
    Fila *tickets;
    ListaTecnicos *listaTecnicos;
    ListaUsuarios *listaUsuarios;
};

void imprimirRelatorioGeral(Gerencia gerencia);

Gerencia criarGerencia()
{
    Gerencia gerencia = malloc(sizeof(struct gerencia));

    gerencia->tickets = criaFila();
    gerencia->listaTecnicos = lista_tecnicos_criar();
    gerencia->listaUsuarios = lista_usuarios_criar();

    return gerencia;
}

void realizarGerencia(Gerencia gerencia)
{
    char opcao = 0;

    while (1)
    {
        scanf("%c%*c", &opcao);

        if (opcao == 'F')
            break;

        if (opcao == 'E')
        {
            char comando[sizeof("RANKING TECNICOS")] = "";
            scanf("%[^\n]%*c", comando);

            if (strcmp(comando, "TECNICOS") == 0)
                lista_tecnicos_print(gerencia->listaTecnicos);

            if (strcmp(comando, "RANKING TECNICOS") == 0)
                lista_tecnicos_print_por_ranking(gerencia->listaTecnicos);

            else if (strcmp(comando, "USUARIOS") == 0)
                lista_usuarios_print(gerencia->listaUsuarios);

            else if (strcmp(comando, "RANKING USUARIOS") == 0)
                lista_usuarios_print_por_ranking(gerencia->listaUsuarios);

            else if (strcmp(comando, "DISTRIBUI") == 0)
            {
                int countTickets = getQtdTicketsNaFila(gerencia->tickets);
                int countTecnicos = lista_tecnicos_quantidade(gerencia->listaTecnicos);

                for (int i = 0; i < countTickets; i++)
                {
                    Ticket *ticket = getTicketNaFila(gerencia->tickets, i);

                    if (getStatusTicket(ticket) == 'F')
                        continue;

                    for (int j = 0; j < countTecnicos; j++)
                    {
                        Tecnico *tecnico = lista_tecnicos_tecnico(gerencia->listaTecnicos, j);

                        if (!tecnico_tem_disponibilidade(tecnico, ticket) ||
                            !tecnico_habil_para_ticket(tecnico, ticket))
                            continue;

                        tecnico_pegar_ticket(tecnico, ticket);
                        break;
                    }
                }
            }

            else if (strcmp(comando, "NOTIFICA") == 0)
            {
                printf("----- FILA DE TICKETS -----\n");
                notificaFila(gerencia->tickets);
                printf("---------------------------\n\n");
            }

            else if (strcmp(comando, "RELATORIO") == 0)
                imprimirRelatorioGeral(gerencia);
        }

        else if (opcao == 'T')
        {
            Tecnico *tecnico = tecnico_ler();
            lista_tecnicos_adicionar(gerencia->listaTecnicos, tecnico);
        }

        else if (opcao == 'U')
        {
            Usuario *usuario = usuario_ler();
            lista_usuarios_adicionar(gerencia->listaUsuarios, usuario);
        }

        else if (opcao == 'A')
        {
            char cpfSol[TAM_CPF] = "";
            char tipoTicket[MAX_LENGTH_TIPO_TICKET] = "";
            scanf("%[^\n]%*c", cpfSol);
            scanf("%[^\n]%*c", tipoTicket);

            Usuario *solicitante = lista_usuarios_procura_por_cpf(gerencia->listaUsuarios, cpfSol);

            if (strcmp(tipoTicket, "MANUTENCAO") == 0)
            {
                Manutencao *manutecao = lerManutencao();
                setTempoEstimadoManutencao(manutecao);

                if (!solicitante)
                {
                    desalocaManutencao(manutecao);
                    continue;
                }

                setSetor(manutecao, usuario_recupera_setor(solicitante));

                insereTicketFila(gerencia->tickets, cpfSol, manutecao, getTempoEstimadoManutencao, getTipoManutencao,
                                 notificaManutencao, desalocaManutencao);
            }

            else if (strcmp(tipoTicket, "SOFTWARE") == 0)
            {
                Software *software = lerSoftware();
                setTempoEstimadoSoftware(software);

                if (!solicitante)
                {
                    desalocaSoftware(software);
                    continue;
                }

                insereTicketFila(gerencia->tickets, cpfSol, software, getTempoEstimadoSoftware, getTipoSoftware,
                                 notificaSoftware, desalocaSoftware);
            }

            else if (strcmp(tipoTicket, "OUTROS") == 0)
            {
                Outros *outros = lerOutros();

                if (!solicitante)
                {
                    desalocaOutros(outros);
                    continue;
                }

                insereTicketFila(gerencia->tickets, cpfSol, outros, getTempoEstimadoOutros, getTipoOutros,
                                 notificaOutros, desalocaOutros);
            }

            usuario_incrementa_solicitacoes(solicitante);
        }
    }
}

void liberarGerencia(Gerencia gerencia)
{
    desalocaFila(gerencia->tickets);
    lista_tecnicos_free(gerencia->listaTecnicos);
    lista_usuarios_free(gerencia->listaUsuarios);
    free(gerencia);
    gerencia = NULL;
}

void imprimirRelatorioGeral(Gerencia gerencia)
{
    printf("----- RELATORIO GERAL -----\n");
    printf("- Qtd tickets: %d\n", getQtdTicketsNaFila(gerencia->tickets));
    printf("- Qtd tickets (A): %d\n", getQtdTicketsPorStatusNaFila(gerencia->tickets, 'A'));
    printf("- Qtd tickets (F): %d\n", getQtdTicketsPorStatusNaFila(gerencia->tickets, 'F'));
    printf("- Qtd usuarios: %d\n", lista_usuarios_quantidade(gerencia->listaUsuarios));
    printf("- Md idade usuarios: %d\n", lista_usuarios_media_idade(gerencia->listaUsuarios));
    printf("- Qtd tecnicos: %d\n", lista_tecnicos_quantidade(gerencia->listaTecnicos));
    printf("- Md idade tecnicos: %d\n", lista_tecnicos_media_idade(gerencia->listaTecnicos));
    printf("- Md trabalho tecnicos: %d\n", lista_tecnicos_media_trabalho(gerencia->listaTecnicos));
    printf("---------------------------\n\n");
}
