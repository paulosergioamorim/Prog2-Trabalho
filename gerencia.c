#include "gerencia.h"
#include "constantes.h"
#include "fila.h"
#include "list.h"
#include "manutencao.h"
#include "outros.h"
#include "software.h"
#include "tecnico.h"
#include "usuario.h"
#include "hardware.h"
#include "empresa.h"
#include <stdio.h>
#include <stdlib.h>

list(Usuario);
list(Tecnico);
list(Empresa);

struct gerencia
{
    Fila *tickets;
    Tecnicos tecnicos;
    Usuarios usuarios;
    Empresas empresas;
};

void imprimirRelatorioGeral(Gerencia gerencia);
void imprimirRelatorioTecnicos(Gerencia gerencia);

Gerencia criarGerencia()
{
    Gerencia gerencia = malloc(sizeof(struct gerencia));

    gerencia->tickets = criaFila();
    gerencia->tecnicos = Tecnicos_create(imprimirTecnico, liberarTecnico);
    gerencia->usuarios = Usuarios_create(imprimirUsuario, liberarUsuario);
    gerencia->empresas = Empresas_create(imprimirEmpresa, liberarEmpresa);

    return gerencia;
}

void realizarGerencia(Gerencia gerencia, const char opcao)
{
    if (opcao == 'F')
        return;

    if (opcao == 'E')
    {
        char comando[50] = "";
        scanf("%[^\n]%*c", comando);

        if (strcmp(comando, "EMPRESAS FORNECEDORAS") == 0) {
            printf("----- EMPRESAS FORNECEDORAS -----\n");
            Empresas_print(gerencia->empresas);
            printf("----------------------------\n\n");
        }

        else if (strcmp(comando, "TECNICOS") == 0)
        {
            printf("----- BANCO DE TECNICOS -----\n");
            Tecnicos_print(gerencia->tecnicos);
            printf("----------------------------\n\n");
        }

        else if (strcmp(comando, "RANKING TECNICOS") == 0)
        {
            Tecnicos sortedList = Tecnicos_to_sorted(gerencia->tecnicos, compararTecnicos);
            printf("----- RANKING DE TECNICOS -----\n");
            Tecnicos_print(sortedList);
            printf("-------------------------------\n\n");
            Tecnicos_free_only_buffer(sortedList);
        }

        else if (strcmp(comando, "USUARIOS") == 0)
        {
            printf("----- BANCO DE USUARIOS -----\n");
            Usuarios_print(gerencia->usuarios);
            printf("----------------------------\n\n");
        }

        else if (strcmp(comando, "RANKING USUARIOS") == 0)
        {
            Usuarios sortedList = Usuarios_to_sorted(gerencia->usuarios, compararUsuarios);
            printf("----- RANKING DE USUARIOS -----\n");
            Usuarios_print(sortedList);
            printf("-------------------------------\n\n");
            Usuarios_free_only_buffer(sortedList);
        }

        else if (strcmp(comando, "BUSCAR TICKETS") == 0) {
            char cpfSol[TAM_CPF] = "";
            scanf("%[^\n]\n", cpfSol);

            printf("----- BUSCAR TICKETS -----\n");
            notificaFilaPorCPF(gerencia->tickets, cpfSol);
            printf("-------------------------------\n\n");
        }

        else if (strcmp(comando, "DISTRIBUI") == 0)
        {
            int countTickets = getQtdTicketsNaFila(gerencia->tickets);
            int countTecnicos = Tecnicos_get_count(gerencia->tecnicos);
            int start = 0; // Índice inicial para o Round Robin

            for (int i = 0; i < countTickets; i++)
            {
                Ticket *ticket = getTicketNaFila(gerencia->tickets, i);

                if (getStatusTicket(ticket) == 'F')
                    continue;

                int quantidadeTecnicosOferecidos = 0;
                int j = start;
                int algumTecnicoPegouTicket = 0;

                // Tenta técnicos em ordem circular
                while (quantidadeTecnicosOferecidos < countTecnicos)
                {
                    Tecnico tecnico = Tecnicos_get(gerencia->tecnicos, j);

                    if (podePegarTicketTecnico(tecnico, ticket))
                    {
                        pegarTicketTecnico(tecnico, ticket);
                        algumTecnicoPegouTicket = 1;
                        break;
                    }

                    j = (j + 1) % countTecnicos;
                    quantidadeTecnicosOferecidos++;
                }

                // Atualiza o ponto inicial para o próximo ticket
                if (algumTecnicoPegouTicket)
                    start = (j + 1) % countTecnicos;
                else
                    start = (start + 1) % countTecnicos;
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

        else if (strcmp(comando, "RELATORIO TECNICOS") == 0) {
            imprimirRelatorioTecnicos(gerencia);
        }
    }

    else if (opcao == 'T')
    {
        Tecnico tecnico = lerTecnico();

        if (Tecnicos_get_by_char_property(gerencia->tecnicos, getCPFTecnico(tecnico), getCPFTecnico))
        {
            liberarTecnico(tecnico);
            return;
        }

        Tecnicos_push(gerencia->tecnicos, tecnico);
    }

    else if (opcao == 'U')
    {
        Usuario usuario = lerUsuario();

        if (Usuarios_get_by_char_property(gerencia->usuarios, getCPFUsuario(usuario), getCPFUsuario))
        {
            liberarUsuario(usuario);
            return;
        }

        Usuarios_push(gerencia->usuarios, usuario);
    }

    else if (opcao == 'P') {
        Empresa empresa = lerEmpresa();

        if (Empresas_get_by_char_property(gerencia->empresas, getCNPJEmpresa(empresa), getCNPJEmpresa)) {
            liberarEmpresa(empresa);
            return;
        }

        Empresas_push(gerencia->empresas, empresa);
    }

    else if (opcao == 'A')
    {
        char cpfSol[TAM_CPF] = "";
        char tipoTicket[MAX_LENGTH_TIPO_TICKET] = "";
        scanf("%[^\n]%*c", cpfSol);
        scanf("%[^\n]%*c", tipoTicket);

        Usuario solicitante = Usuarios_get_by_char_property(gerencia->usuarios, cpfSol, getCPFUsuario);

        if (strcmp(tipoTicket, "MANUTENCAO") == 0)
        {
            Manutencao *manutecao = lerManutencao();

            if (!solicitante)
            {
                desalocaManutencao(manutecao);
                return;
            }

            setSetor(manutecao, getSetorUsuario(solicitante));

            insereTicketFila(gerencia->tickets, cpfSol, manutecao, getTempoEstimadoManutencao, getTipoManutencao,
                             notificaManutencao, desalocaManutencao);
            setTempoEstimadoManutencao(manutecao);
        }

        else if (strcmp(tipoTicket, "HARDWARE") == 0) {
            Hardware *hardware = lerHardware();

            if (!solicitante) {
                desalocaHardware(hardware);
                return;
            }

            insereTicketFila(gerencia->tickets, cpfSol, hardware, getTempoEstimadoHardware, getTipoHardware, notificaHardware, desalocaHardware);
            setTempoEstimadoHardware(hardware);
        }

        else if (strcmp(tipoTicket, "SOFTWARE") == 0)
        {
            Software *software = lerSoftware();

            if (!solicitante)
            {
                desalocaSoftware(software);
                return;
            }

            insereTicketFila(gerencia->tickets, cpfSol, software, getTempoEstimadoSoftware, getTipoSoftware,
                             notificaSoftware, desalocaSoftware);
            setTempoEstimadoSoftware(software);
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
            setTempoEstimadoOutros(outros);
        }

        addSolicitacaoUsuario(solicitante);
    }
}

void liberarGerencia(Gerencia gerencia)
{
    desalocaFila(gerencia->tickets);
    Tecnicos_free(gerencia->tecnicos);
    Usuarios_free(gerencia->usuarios);
    Empresas_free(gerencia->empresas);
    free(gerencia);
}

void imprimirRelatorioGeral(Gerencia gerencia)
{
    printf("----- RELATORIO GERAL -----\n");
    printf("- Qtd tickets: %d\n", getQtdTicketsNaFila(gerencia->tickets));
    printf("- Qtd tickets (A): %d\n", getQtdTicketsPorStatusNaFila(gerencia->tickets, 'A'));
    printf("- Qtd tickets (F): %d\n", getQtdTicketsPorStatusNaFila(gerencia->tickets, 'F'));
    printf("- Qtd usuarios: %d\n", Usuarios_get_count(gerencia->usuarios));
    printf("- Md idade usuarios: %d\n", Usuarios_average(gerencia->usuarios, getIdadeUsuario));
    printf("- Qtd tecnicos: %d\n", Tecnicos_get_count(gerencia->tecnicos));
    printf("- Md idade tecnicos: %d\n", Tecnicos_average(gerencia->tecnicos, getIdadeTecnico));
    printf("- Md trabalho tecnicos: %d\n", Tecnicos_average(gerencia->tecnicos, getTempoTrabalhadoTecnico));
    printf("---------------------------\n\n");
}

/*
----- RELATORIO TECNICOS -----
- Qtd tecnicos: 4
- Md idade tecnicos: 39
- Md trabalho tecnicos: 5
- Md disponibilidade tecnicos: 24
- Md salario tecnicos: 4575
-------------------------------
*/
void imprimirRelatorioTecnicos(Gerencia gerencia) {
    printf("----- RELATORIO TECNICOS -----\n");
    printf("- Qtd tecnicos: %d\n", Tecnicos_get_count(gerencia->tecnicos));
    printf("- Md idade tecnicos: %d\n", Tecnicos_average(gerencia->tecnicos, getIdadeTecnico));
    printf("- Md trabalho tecnicos: %d\n",Tecnicos_average(gerencia->tecnicos, getTempoTrabalhadoTecnico));
    printf("- Md disponibilidade tecnicos: %d\n", Tecnicos_average(gerencia->tecnicos, getDisponibilidadeTecnico));
    printf("- Md salario tecnicos: %d\n", Tecnicos_average(gerencia->tecnicos, getSalarioTecnico));
    printf("-------------------------------\n\n");
}