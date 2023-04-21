#ifndef TIPODADOS_H_INCLUDED
    #define TIPODADOS_H_INCLUDED

    #include "../includes/ListaLigada.h"
    #include <stdio.h>
    #include <stdlib.h> 
    #include <string.h>
    #include <math.h>
    #include <time.h>

    //Criar as threads
    #ifndef PTHREAD_H
        #include <pthread.h> 
    #endif 
    
    //TIME (SLEEP)
    #ifdef _WIN32
        #include <windows.h>
    #endif
    #ifdef __linux__
        #include <linux.h>
    #endif
    
    //Printcolor
    #ifndef CJAG_COLORPRINT
        #define CJAG_COLORPRINT
        #define ERROR_TAG "[r][ERROR][/r] "
        void printc(const char *fmt, ...);
        void spinner_start(unsigned int type, const char* fmt, ...);
        void spinner_update(const char* fmt, ...);
        void spinner_done(const char* fmt, ...);
        void progress_start(int max, char* fmt);
        void progress_update();
    #endif


    typedef struct{
        char *nome;
        int id, experiencia, ativo;                // A experiencia é a quantidade de vendas realizadas e influencia o salário.
        float atrasoMedio, bonus, salario;  // O atraso medio pode ser negativo ou positivo e influencia o bonus.
    }FuncionarioStruct;

    typedef struct{
        int id, tempoTotalEspera, aberta;
        FuncionarioStruct *funcionario;
        Lista *listaPessoas;
    }CaixaStruct;

    typedef struct{
        int codigo;
        char *nome;
        float preco, tempoCompra, tempoCaixa;
    }ProdutoStruct;

    typedef struct{
        int dia, mes, ano;
    }DataStruct;

    typedef struct{
        int id, ativo;                      // guests: -1
        char *nome;                         // guests: "none"
        DataStruct dataNascimento;          // guests: -1/-1/-1
        float saldoCartaoCliente;           // guests: -1 | clientes: angariado a cada compra e pode ser usado em qualquer uma das compras

        int tempoEstimadoCompra;        // soma do tempo de compra dos proprios produtos
        int tempoEstimadoFila;          // soma do tempo dos produtos das pessoas a sua frente no momento em que entrou na fila
        int tempoEstimadoCaixa;         // soma do tempo de caixa dos proprios produtos

        int tempoAtraso;                // soma do atraso aleatorio de cada pessoa a sua frente

        Lista *listaProdutos;           // lista dos produtos
    }ClienteStruct;

     typedef enum {
        CLIENTES,
        FUNCIONARIOS
    } TipoDados;

    //GLOBAL VARIABLES
    extern ClienteStruct *Clientes;
    extern FuncionarioStruct *Funcionarios;
    extern ProdutoStruct *Produtos;
    extern int n_clientes, n_clientesAtivos, n_funcionarios, n_funcionariosAtivos, n_produtos;

    //ImportExport.c
    void importarClientesx(char **linhaString, int n_linha);
    void importarFuncionariosx(char **linhaString, int n_linha);
    void importarDados(char *filename, int colunas, void (guardarDados)(char **, int), TipoDados tipo);

    //TipoDadosFuncoes.c
    int escolherAleatorioVetor(void *vetor, int batente, int tamanhoVetor, size_t tamanhoElemento, void *ptrElemento); // Funcional
    void associarProdutosCliente(ClienteStruct *cliente, Lista *produtos);
    ClienteStruct *criarGuest();
    void *escolherFuncionarios();
    void *escolherProduto();
    void *escolherCliente();
    void batenteChange(void* ptr1, void* ptr2, size_t size, int *batente, char sinal);
    void mostrarFuncionario(void *funcionarioArg, int indentLevel);
    void mostrarCaixa(void *caixaArg, int indentLevel);
    void mostrarProduto(void *produtoArg, int indentLevel);
    void mostrarCliente(void *clienteArg, int indentLevel);

    //Utils.c
    int Aleatorio(int min, int max);
    DataStruct gerarData(int anoMin, int anoMax);
    int DataAntesDepois(DataStruct d1, DataStruct d2);
    
    //JOAOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO????????????????
    //void criarAddLista(Lista *lista, int Qt, void*(*escolherElemento)());

    //Threads.c
    void *ThreadGlobal();
    
#endif