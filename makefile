MAINFILE :=	main
HIPER:=	hipergrafoTAD
HEURISTICA:=	heuristica
MAINGRAFO:=	grafo
COMPFLAGS := 	-Wall -O9 -c
LINKFLAGS := 	-o

geral:
	gcc	$(COMPFLAGS) 	*.c
hiper:	geral
	gcc	$(LINKFLAGS)	$(MAINFILE)	$(MAINFILE).o 	$(HIPER).o 	-g
heuristica:	geral
	gcc	$(LINKFLAGS)	$(MAINFILE)	$(MAINFILE).o	$(HEURISTICA).o 	-g
grafo:	geral
	gc	$(LINKFLAGS)	$(MAINGRAFO)	$(GRAFOMAIN).c	-g
clear:
	rm -f	*.o	$(MAINFILE)	$(MAINGRAFO)
run:
	./$(MAINGRAFO)
