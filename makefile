MAINFILE :=	hipergrafoTAD
MAINGRAFO:=	grafo
COMPFLAGS := 	-Wall -O9 -c
LINKFLAGS := 	-o

geral:
	gcc	$(COMPFLAGS) 	*.c
hiper:	geral
	gcc	$(LINKFLAGS)	$(MAINFILE)	$(MAINFILE).c 	-g
grafo:	geral
	gc	$(LINKFLAGS)	$(MAINGRAFO)	$(GRAFOMAIN).c	-g
clear:
	rm -f	*.o	$(MAINFILE)	$(MAINGRAFO)	
run:
	./$(MAINGRAFO)
