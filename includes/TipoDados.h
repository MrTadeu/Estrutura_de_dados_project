#ifndef TIPODADOS_H_INCLUDED
    #define TIPODADOS_H_INCLUDED

    #include "../includes/ListaLigada.h"
    #include <stdio.h>
    #include <stdlib.h> 
    #include <string.h>
    #include <math.h>
    #include <time.h>
    #include <locale.h>
    #include <unistd.h>

    //Criar as threads
    #ifndef PTHREAD_H
        #include <pthread.h> 
    #endif 
    
    //TIME (SLEEP)
    #ifdef _WIN32
        #include <windows.h>
        #define SET_UTF8_CODEPAGE system("chcp 65001 > nul");
    #endif
    #ifdef __linux__
        #include <linux.h>
        #define SET_UTF8_CODEPAGE
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
        int id, n_vendas, ativo;                    // A experiencia é a quantidade de vendas realizadas e influencia o salário.
        float atrasoMedio, bonus;                   // O atraso medio pode ser negativo ou positivo e influencia o bonus.
    }FuncionarioStruct;

    typedef struct{
        int id, tempoTotalEspera, aberta, fecharUrgencia;
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
        int tempoEstimadoCaixa;         // soma do tempo de caixa dos proprios produtoOpcaoStructs

        int tempoAtraso;                // soma do atraso aleatorio de cada pessoa a sua frente

        Lista *listaProdutos;           // lista dos produtos
    }ClienteStruct;

    typedef struct{
        int nivel;
        float salario;
    }NivelFuncionarioStruct;

    typedef struct{
        int numCaixasTotal, numCaixasAbertas, probGerarPessoa, percentagemParaAtraso, lotacaoMaxima, lojaAberta, VerTransacoes, threadGlobalAranque;
        float /* **nivelFuncionario,  */eurosPorSegundoAdiantamentoFuncinario;
        NivelFuncionarioStruct nivelFuncionario[3];
    }OpcaoStruct;


    typedef struct{
        Lista* caixas;
    }GlobalStruct;

     typedef enum {
        CLIENTES,
        FUNCIONARIOS,
        PRODUTOS
    } TipoDados;

    typedef struct{
        CaixaStruct *caixa;
        ClienteStruct *pessoa;
    }HistoricoStruct;

    //GLOBAL VARIABLES
    extern OpcaoStruct Opcoes;
    extern ClienteStruct *Clientes;
    extern FuncionarioStruct *Funcionarios;
    extern ProdutoStruct *Produtos;
    extern int n_clientes, n_clientesAtivos, n_funcionarios, n_funcionariosAtivos, n_produtos;

    //menu.c
    void menu();
    void menuClientes();
    void menuFuncionarios();
    void menuConfig();

    //opcoes.c
    void editarNumCaixas();
    void editarProbGerarPessoa();
    void editarLotacaoMax();
    void editarLojaAbertaAranque();
    void Init();
    void closeAll();
    void editarVerTransacoes();

    //clientes.c
    void verClientes();
    int checkIfUserExists(int id);
    int generateUserID();
    void pesquisarClientes();
    void adicionarCliente();
    void editarCliente();
    void removerCliente();

    //caixas.c
    int CaixaIndex(Lista *caixa);
    void SelecionarCaixa(Lista *caixas, Elemento *cliente);

    //funcionarios.c
    int encontrarIdFuncionario(int id);
    float convertNumeroDeVendasSalario_vetor(int pos);
    float convertVendasToSalario_lista(FuncionarioStruct *funcionario);
    void verFuncionariosCaixa();
    void verFuncionariosInativos();
    void pesquisarFuncionarios();
    void editarFuncionarios();
    void adicionarFuncionario();
    void removerFuncionario();

    //ImportExport.c
    int importarCount(char *filename);
    void importarClientes(char **linhaString, int n_linha, int n_colunas);
    void importarFuncionarios(char **linhaString, int n_linha, int n_colunas);
    void importarProdutos(char **linhaString, int n_linha, int n_colunas);
    void importarDados(void (guardarDados)(char **, int, int), TipoDados tipo);
    void exportarDados(void (guardarDadosTxt)(FILE *, int), TipoDados tipo);
    void guardarClienteTxt(FILE *file, int i);
    void guardarFuncionarioTxt(FILE *file, int i);
    void guardarProdutoTxt(FILE *file, int i);
    void importOpcoes();
    void exportarOpcoes();


    //TipoDadosFuncoes.c
    int escolherAleatorioVetor(void *vetor, int n_ativos, int tamanhoVetor, size_t tamanhoElemento, void *ptrElemento); // Funcional
    ClienteStruct *criarGuest();
    FuncionarioStruct *escolherFuncionarios();
    ProdutoStruct *escolherProduto();
    ClienteStruct *escolherCliente();//alterado para retornar um ponteiro para o cliente escolhido
    void batenteChange(void* ptr1, void* ptr2, size_t size, int *batente, char sinal);
    void mostrarFuncionario(void *funcionarioArg, int indentLevel);
    void mostrarCaixa(void *caixaArg, int indentLevel);
    void mostrarProduto(void *produtoArg, int indentLevel);
    void mostrarCliente(void *clienteArg, int indentLevel);
    int compararProduto(void *ptrProduto1_Info, void * ptrProduto2_Info);
    int compararCliente(void *ptrCliente1_Info, void *ptrCliente2_Info);
    int pesquisarClienteVetorBatente(ClienteStruct *pessoa);

    //Utils.c
    void setPortugues();
    int Aleatorio(int min, int max);
    DataStruct gerarData(int anoMin, int anoMax);
    int DataAntesDepois(DataStruct d1, DataStruct d2);
    void dormir(int tempo);
    struct tm getCurrentTime();
    int checkIFfileExists(char *filepath);
    int generateID(int (*checkIfExists)(int), int x);
    
    //FuncoesCaixa.c
    void *ThreadCaixa(CaixaStruct *caixa);

    //ThreadGlobal.c
    typedef struct{
        Lista *ListaClientesNaFila;
        ClienteStruct *cliente;
    }Argumentos;
    void changeStateThreadGlobal();
    void *ThreadGlobal();
    void ThreadTempoDeCompra(Lista *ListaClientesNaFila, ClienteStruct *pessoa);
    void *ThreadEsperaTempoCompra(void *args);

    
#endif