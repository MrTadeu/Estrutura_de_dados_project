#--------------------------------------------------------------------------------------------------
CC=gcc
CFLAGS=-O3 -Wall -Wextra
#--------------------------------------------------------------------------------------------------
INCLUDES_DIR = includes
SRC_DIR = src
SRC= $(wildcard $(SRC_DIR)/*.c) 
HEADERS=TipoDados.h Utils.h ListaLigada.h

all: run.exe

run.exe: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) -o run.exe

clean:
	del run.exe
