#--------------------------------------------------------------------------------------------------
CC = gcc
CFLAGS = -O3 -Wall -Wextra
#--------------------------------------------------------------------------------------------------
INCLUDES_DIR = includes
SRC_DIR = src
BUILD_DIR = build
#--------------------------------------------------------------------------------------------------
SRC = $(wildcard $(SRC_DIR)/*.c) # TODOS OS .c (vai fazer a lista de todos os .c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC)) # TODOS OS .c VÃO SER SUBSTITUIDOS POR .o
HEADERS = $(wildcard $((INCLUDES_DIR)/*.h)) # TODOS OS .h (vai fazer a lista de todos os .h)
# TODOS OS .c VÃO SER SUBSTITUIDOS POR .o src/main.c -> build/main.o
#--------------------------------------------------------------------------------------------------
PROGRAM = simulation
#--------------------------------------------------------------------------------------------------
.DEFAULT_GOAL = build

build: setup $(PROGRAM)

# isto vai criar ./simulation.o
$(PROGRAM): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(PROGRAM)

# isto vai criar um arquivo .o para cada arquivo .c
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) -c $(CFLAGS) $(INCLUDES_DIR) -o $@ $^
# .PHONY - Não é um arquivo, é um comando usado para não dar erro de arquivo não encontrado
.PHONY: setup
setup:
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
#run.o: $(SRC) $(HEADERS)
#	$(CC) $(CFLAGS) $(SRC) -o run

.PHONY: clean
clean:
	del $(BUILD_DIR)
	del $(PROGRAM).o

.PHONY: cleanLinux
cleanLinux:
	@-rm -r $(BUILD_DIR)
	@-rm $(PROGRAM) 


# wildcard - Função das Makefile em que dá uma lista de um determinado .c
# patsubst - PatSubstring é substituir uma determinada lista de .c por .o
# @ - Não mostra o comando no terminal
# $@ - Nome do arquivo (variavel)
# - se o comando falhar, ele é ignorado
# -p - Se o diretório não existir, ele cria
# -r - Se o diretório não existir, ele não cria
# $< - Primeiro arquivo
# $^ - Todos os arquivos