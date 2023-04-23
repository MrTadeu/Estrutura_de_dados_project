#ifndef TIPODADOS_H_INCLUDED
    #define TIPODADOS_H_INCLUDED

    #include "../includes/ListaLigada.h"
    #include <stdio.h>
    #include <stdlib.h> 
    #include <string.h>
    #include <math.h>
    #include <time.h>
    #include <locale.h>

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
        int id, experiencia, ativo;                 // A experiencia é a quantidade de vendas realizadas e influencia o salário.
        float atrasoMedio, bonus, salario;          // O atraso medio pode ser negativo ou positivo e influencia o bonus.
    }FuncionarioStruct;

    typedef struct{
        int id, tempoTotalEspera, aberta, fecharUrgencia;
        float percentagemParaAtraso;
        FuncionarioStruct *funcionario;
        Lista *listaPessoas;
    }CaixaStruct;

    typedef struct{
        int id;
        char *nome;
        float preco, tempoCompra, tempoCaixa;
    }ProdutoStruct;

    typedef struct{
        int dia, mes, ano;
    }DataStruct;

    typedef struct{
        int id, ativo;                  // guests: -1
        char *nome;                     // guests: "Desconhecido"
        DataStruct dataNascimento;      // guests: -1/-1/-1
        float saldoCartaoCliente;       // guests: -1 | clientes: angariado a cada compra e pode ser usado em qualquer uma das compras

        int tempoEstimadoCompra;        // soma do tempo de compra dos proprios produtos
        int tempoEstimadoFila;          // soma do tempo dos produtos das pessoas a sua frente no momento em que entrou na fila
        int tempoEstimadoCaixa;         // soma do tempo de caixa dos proprios produtos

        int tempoAtraso;                // soma do atraso aleatorio de cada pessoa a sua frente

        Lista *listaProdutos;           // lista dos produtos
    }ClienteStruct;
    
    typedef struct{
        Lista* Caixas;
        int n_caixasTotal, n_caixasAbertas, probabilidadeGerarPessoa;
    }GlobalStruct;

     typedef enum {
        CLIENTES,
        FUNCIONARIOS,
        PRODUTOS
    } TipoDados;

    //GLOBAL VARIABLES
    extern GlobalStruct Global;
    extern ClienteStruct *Clientes;
    extern FuncionarioStruct *Funcionarios;
    extern ProdutoStruct *Produtos;
    extern int n_clientes, n_clientesAtivos, n_funcionarios, n_funcionariosAtivos, n_produtos;

    //ImportExport.c
    void importarClientes(char **linhaString, int n_linha);
    void importarFuncionarios(char **linhaString, int n_linha);
    void importarProdutos(char **linhaString, int n_linha);
    void importarDados(void (guardarDados)(char **, int), TipoDados tipo);

    //TipoDadosFuncoes.c
    int escolherAleatorioVetor(void *vetor, int n_ativos, int tamanhoVetor, size_t tamanhoElemento, void *ptrElemento); // Funcional
    void associarProdutosCliente(ClienteStruct *cliente, Lista *produtos);
    CaixaStruct *criarCaixa(int id);
    ClienteStruct *criarGuest();
    void *escolherFuncionarios();
    void *escolherProduto();
    void *escolherCliente();
    void batenteChange(void* ptr1, void* ptr2, size_t size, int *batente, char sinal);
    void mostrarFuncionario(void *funcionarioArg, int indentLevel);
    void mostrarCaixa(void *caixaArg, int indentLevel);
    void mostrarProduto(void *produtoArg, int indentLevel);
    void mostrarCliente(void *clienteArg, int indentLevel);
    int compararProduto(void *ptrProduto1_Info, void * ptrProduto2_Info);
    int compararCliente(void *ptrCliente1_Info, void *ptrCliente2_Info);
    int pesquisarClienteVetor(ClienteStruct *pessoa);

    //Utils.c
    int Aleatorio(int min, int max);
    DataStruct gerarData(int anoMin, int anoMax);
    int DataAntesDepois(DataStruct d1, DataStruct d2);
    void dormir(int tempo);
    
    //FuncoesCaixa.c
    void *ThreadCaixa(CaixaStruct *caixa);

    //Threads.c
    void *ThreadGlobal();
    
#endif