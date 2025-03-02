#include "gerencia.h"
#include "constantes.h"
#include "fila.h"
#include "list.h"
#include "manutencao.h"
#include "outros.h"
#include "software.h"
#include "tecnico.h"
#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>

list(Usuario);
list(Tecnico);

struct gerencia
{
    Fila *tickets;
    Tecnicos tecnicos;
    Usuarios usuarios;
};

void imprimirRelatorioGeral(Gerencia gerencia);

Gerencia criarGerencia()
{
    Gerencia gerencia = malloc(sizeof(struct gerencia));

    gerencia->tickets = criaFila();
    gerencia->tecnicos = Tecnicos_create(tecnico_print, tecnico_free);
    gerencia->usuarios = Usuarios_create(usuario_print, usuario_free);

    return gerencia;
}

void handleOption(Gerencia gerencia, const char option)
{
    if (option == 'F')
        return;

    if (option == 'E')
    {
        char comando[sizeof("RANKING TECNICOS")] = "";
        scanf("%[^\n]%*c", comando);

        if (strcmp(comando, "TECNICOS") == 0)
            Tecnicos_print(gerencia->tecnicos, "----- BANCO DE TECNICOS -----\n", "----------------------------\n\n");

        if (strcmp(comando, "RANKING TECNICOS") == 0)
        {
            Tecnicos sortedList = Tecnicos_to_sorted(gerencia->tecnicos, qsort_compara_tecnicos);
            Tecnicos_print(sortedList, "----- RANKING DE TECNICOS -----\n", "----------------------------\n\n");
            Tecnicos_free_only_buffer(sortedList);
        }

        if (strcmp(comando, "USUARIOS") == 0)
            Usuarios_print(gerencia->usuarios, "----- BANCO DE USUARIOS -----\n", "----------------------------\n\n");

        if (strcmp(comando, "RANKING USUARIOS") == 0)
        {
            Usuarios sortedList = Usuarios_to_sorted(gerencia->usuarios, qsort_compara_usuarios);
            Usuarios_print(sortedList, "----- RANKING DE USUARIOS -----\n", "----------------------------\n\n");
            Usuarios_free_only_buffer(sortedList);
        }

        else if (strcmp(comando, "DISTRIBUI") == 0)
        {
            int countTickets = getQtdTicketsNaFila(gerencia->tickets);
            int countTecnicos = Tecnicos_get_count(gerencia->tecnicos);

            for (int i = 0; i < countTickets; i++)
            {
                Ticket *ticket = getTicketNaFila(gerencia->tickets, i);

                if (getStatusTicket(ticket) == 'F')
                    continue;

                for (int j = 0; j < countTecnicos; j++)
                {
                    Tecnico tecnico = Tecnicos_get(gerencia->tecnicos, j);

                    if (!tecnico_tem_disponibilidade(tecnico, ticket) || !tecnico_habil_para_ticket(tecnico, ticket))
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

    else if (option == 'T')
    {
        Tecnico tecnico = tecnico_ler();
        Tecnicos_push(gerencia->tecnicos, tecnico);
    }

    else if (option == 'U')
    {
        Usuario usuario = usuario_ler();
        Usuarios_push(gerencia->usuarios, usuario);
    }

    else if (option == 'A')
    {
        char cpfSol[TAM_CPF] = "";
        char tipoTicket[MAX_LENGTH_TIPO_TICKET] = "";
        scanf("%[^\n]%*c", cpfSol);
        scanf("%[^\n]%*c", tipoTicket);

        Usuario solicitante = Usuarios_get_by_char_property(gerencia->usuarios, cpfSol, usuario_recupera_cpf);

        if (strcmp(tipoTicket, "MANUTENCAO") == 0)
        {
            Manutencao *manutecao = lerManutencao();
            setTempoEstimadoManutencao(manutecao);

            if (!solicitante)
            {
                desalocaManutencao(manutecao);
                return;
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
                return;
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
                return;
            }

            insereTicketFila(gerencia->tickets, cpfSol, outros, getTempoEstimadoOutros, getTipoOutros, notificaOutros,
                             desalocaOutros);
        }

        usuario_incrementa_solicitacoes(solicitante);
    }
}

void liberarGerencia(Gerencia gerencia)
{
    desalocaFila(gerencia->tickets);
    Tecnicos_free(gerencia->tecnicos);
    Usuarios_free(gerencia->usuarios);
    free(gerencia);
    gerencia = NULL;
}

void imprimirRelatorioGeral(Gerencia gerencia)
{
    printf("----- RELATORIO GERAL -----\n");
    printf("- Qtd tickets: %d\n", getQtdTicketsNaFila(gerencia->tickets));
    printf("- Qtd tickets (A): %d\n", getQtdTicketsPorStatusNaFila(gerencia->tickets, 'A'));
    printf("- Qtd tickets (F): %d\n", getQtdTicketsPorStatusNaFila(gerencia->tickets, 'F'));
    printf("- Qtd usuarios: %d\n", Usuarios_get_count(gerencia->usuarios));
    printf("- Md idade usuarios: %d\n", Usuarios_average(gerencia->usuarios, usuario_recupera_idade));
    printf("- Qtd tecnicos: %d\n", Tecnicos_get_count(gerencia->tecnicos));
    printf("- Md idade tecnicos: %d\n", Tecnicos_average(gerencia->tecnicos, tecnico_recupera_idade));
    printf("- Md trabalho tecnicos: %d\n", Tecnicos_average(gerencia->tecnicos, tecnico_recupera_tempo_trabalhado));
    printf("---------------------------\n\n");
}
