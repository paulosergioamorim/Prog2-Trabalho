GABARITO_MAIN=../../Gabarito-obj/main.o
GABARITO_FILA=../../Gabarito-obj/fila.o
GABARITO_SOFTWARE=../../Gabarito-obj/software.o
GABARITO_TICKET=../../Gabarito-obj/ticket.o

gcc: *.c
	gcc -o prog *.c -g -Wall

gdb:
	gdb prog

test_ticket: ticket.c
	gcc -o prog ticket.c $(GABARITO_MAIN) $(GABARITO_FILA) $(GABARITO_SOFTWARE) -g -Wall

test_software: software.c
	gcc -o prog software.c $(GABARITO_MAIN) $(GABARITO_FILA) $(GABARITO_TICKET) -g -Wall

test_fila: fila.c
	gcc -o prog fila.c $(GABARITO_MAIN) $(GABARITO_TICKET) $(GABARITO_SOFTWARE) -g -Wall

test_main: main.c
	gcc -o prog main.c gerencia.c usuario.c tecnico.c manutencao.c outros.c data.c $(GABARITO_TICKET) $(GABARITO_FILA) $(GABARITO_SOFTWARE) -g -Wall