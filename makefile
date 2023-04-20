CC=gcc
CFLAGS=-O3 -Wall
SRC=main.c TipoDadosFuncoes.c ListaLigadaFuncoes.c Import_Export.c Utils.c
HEADERS=TipoDados.h Utils.h ListaLigada.h

all: run.exe

run.exe: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) -o run.exe

clean:
	del run.exe
