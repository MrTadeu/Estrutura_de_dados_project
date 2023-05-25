#--------------------------------------------------------------------------------------------------
#tab é importante para o makefile
#target: dependencies
#	action
#--------------------------------------------------------------------------------------------------
CC = gcc
CFLAGS = -O3 -Wall -Wextra -std=c99 -march=native
#--------------------------------------------------------------------------------------------------
#----------------------DIRETÓRIOS------------------------------------------------------------------
#INCLUDES_DIR = includes
SRC_DIR = src
BUILD_DIR := build
BIN = Data
#--------------------------------------------------------------------------------------------------
#----------------------DIRETÓRIOS E FICHEIROS------------------------------------------------------
SRC = $(wildcard $(SRC_DIR)/*.c) # TODOS OS .c (vai fazer a lista de todos os .c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC)) # vou substituir para cada um do $(SRC_DIR)/%.c por $(BUILD_DIR)/%.o que se encontra em $(SRC) build/main.c --> build/main.o
HEADERS = $(wildcard $((INCLUDES_DIR)/*.h)) # TODOS OS .h (vai fazer a lista de todos os .h)

# TODOS OS .c VÃO SER SUBSTITUIDOS POR .o src/main.c -> build/main.o
#--------------------------------------------------------------------------------------------------
PROGRAM = simulation
#--------------------------------------------------------------------------------------------------
.DEFAULT_GOAL = build

# -e preprucessor que trata dos includes (depois vem o compiler) -s é para parar no assembly -c é para os arquivos linker
build: setup $(PROGRAM) $(BIN)
buildLinux: setupLinux $(PROGRAM)
# isto vai criar ./simulation.o
#por -g para o valgrind
$(PROGRAM): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(PROGRAM) -lm

# isto vai criar um arquivo .o para cada arquivo .c || a opção -c é para não criar um executavel e sim um arquivos  .o ou seja compilar individualmente
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $^ -o $@  -lm

# .PHONY - Não é um arquivo, é um comando usado para não dar erro de arquivo não encontrado
.PHONY: setup
setup:
	@if not exist "$(BIN)" mkdir "$(BIN)"
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
#run.o: $(SRC) $(HEADERS)
#	$(CC) $(CFLAGS) $(SRC) -o run
.PHONY: setupLinux
#@-sudo chmod -R a+rwx .
#setupLinux:
#	@-mkdir -p $(BUILD_DIR)
#	@-mkdir -p $(BIN)
setupLinux:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN)

.PHONY: clean
clean:
	@rmdir /s /q $(BUILD_DIR) || echo "" > nul
	@del $(PROGRAM).exe

.PHONY: cleanLinux
cleanLinux:
	@-rm -r $(BUILD_DIR)
	@-rm $(PROGRAM)
# wildcard - Função das Makefile em que dá uma lista de um determinado .c
# patsubst - PatSubstring é substituir uma determinada lista de .c por .o
# @ - Não mostra o comando no terminal
# $@ - é o target
# - se o comando falhar, ele é ignorado
# -p - Se o diretório não existir, ele cria
# -r - Se o diretório não existir, ele não cria
# $< - Primeira dependencia
# $^ - dependencia todas