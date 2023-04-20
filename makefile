#--------------------------------------------------------------------------------------------------
CC = gcc
CFLAGS = -O3 -Wall -Wextra
#--------------------------------------------------------------------------------------------------
#----------------------DIRETÓRIOS------------------------------------------------------------------
INCLUDES_DIR = includes
SRC_DIR = src
BUILD_DIR = build
#--------------------------------------------------------------------------------------------------
#----------------------DIRETÓRIOS E FICHEIROS------------------------------------------------------
SRC = $(wildcard $(SRC_DIR)/*.c) # TODOS OS .c (vai fazer a lista de todos os .c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC)) # TODOS OS .c VÃO SER SUBSTITUIDOS POR .o
HEADERS = $(wildcard $((INCLUDES_DIR)/*.h)) # TODOS OS .h (vai fazer a lista de todos os .h)

# TODOS OS .c VÃO SER SUBSTITUIDOS POR .o src/main.c -> build/main.o
#Os arquivos de objeto permitem uma compilação mais rápida, pois só precisam ser recompilados quando o arquivo de origem a partir do qual foram gerados é alterado. Isso acelera o processo de construção, especialmente para grandes projetos. Ele também permite compilações incrementais, o que significa que apenas os arquivos de objeto que foram alterados precisam ser recompilados, em vez de todo o programa.
#E se quisermos usar uma biblioteca no futuro que tem certas dependências, o arquivo de objeto nos ajudará a gerenciar essas dependências. Se tiver uma diferença em um cabeçalho o arquivo tem de ser recompilado, assim somente certos aquivos serão recompilados.
#É de notar que eu não fiz um comando de compilação especifica para cada um, uma vez que para esse projeto que constantemente é modificado (dava muito trabalho estar a fazer isso :) , imagina ter que ficar a ouvir reclamaçoes para atualizar este ficheiro :'(    ).
#--------------------------------------------------------------------------------------------------
PROGRAM = simulation
#--------------------------------------------------------------------------------------------------
.DEFAULT_GOAL = build

build: setup $(PROGRAM)

# isto vai criar ./simulation.o
$(PROGRAM): $(OBJ)
	$(CC) -I $(INCLUDES_DIR) $(CFLAGS) $(OBJ) -o $(PROGRAM)

# isto vai criar um arquivo .o para cada arquivo .c || a opção -c é para não criar um executavel e sim um arquivos  .o ou seja compilar individualmente
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) -c -I $(INCLUDES_DIR) $(CFLAGS) -o $@ $^

# .PHONY - Não é um arquivo, é um comando usado para não dar erro de arquivo não encontrado
.PHONY: setup
setup:
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
#run.o: $(SRC) $(HEADERS)
#	$(CC) $(CFLAGS) $(SRC) -o run

.PHONY: clean
clean:
	@del $(BUILD_DIR)
	@rmdir $(BUILD_DIR)
	@del $(PROGRAM).exe
.PHONY: cleanLinux
cleanLinux:
	@-rm -r $(BUILD_DIR)
	@-rm $(PROGRAM).o
# wildcard - Função das Makefile em que dá uma lista de um determinado .c
# patsubst - PatSubstring é substituir uma determinada lista de .c por .o
# @ - Não mostra o comando no terminal
# $@ - Nome do arquivo (variavel)
# - se o comando falhar, ele é ignorado
# -p - Se o diretório não existir, ele cria
# -r - Se o diretório não existir, ele não cria
# $< - Primeiro arquivo
# $^ - Todos os arquivos
