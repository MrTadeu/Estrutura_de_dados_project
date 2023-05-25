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
#include <sys/time.h>
#include <stdarg.h>

// Criar as threads
#ifndef PTHREAD_H
#include <pthread.h>
#endif

// TIME (SLEEP)
#ifdef _WIN32
#include <windows.h>
#define SET_UTF8_CODEPAGE system("chcp 65001 > nul");
#endif
#ifdef __linux__
#include <unistd.h>
#define SET_UTF8_CODEPAGE
#endif

// Printcolor
#ifndef CJAG_COLORPRINT
#define CJAG_COLORPRINT
#define ERROR_TAG "[r][ERROR][/r] "
void printc(const char *fmt, ...);
void spinner_start(unsigned int type, const char *fmt, ...);
void spinner_update(const char *fmt, ...);
void spinner_done(const char *fmt, ...);
void progress_start(int max, char *fmt);
void progress_update();
#endif

typedef struct
{
    char *nome;
    int id, n_vendas, ativo; // A experiencia é a quantidade de vendas realizadas e influencia o salário.
    int atrasoMedio;         // O atraso medio pode ser negativo ou positivo e influencia o bonus.
} FuncionarioStruct;

typedef struct
{
    int id, aberta, fecharUrgencia, threadAberta;
    int tempoTotalEspera; // tempoEstimadoCaixa += tempoEstimadoCaixa
    FuncionarioStruct *funcionario;
    Lista *listaPessoas;
    pthread_mutex_t lock;
} CaixaStruct;

typedef struct
{
    int id, quantidadeProdutosRepetidos, oferecido, tempoCompra, tempoCaixa;
    char *nome;
    float preco;
} ProdutoStruct;

typedef struct
{
    int dia, mes, ano, hora, minuto, segundo;
} DataStruct;

typedef struct
{
    int id, ativo;             // guests: -1
    char *nome;                // guests: "Desconhecido"
    DataStruct dataNascimento; // guests: -1/-1/-1
    float saldoCartaoCliente;  // guests: -1 | clientes: angariado a cada compra e pode ser usado em qualquer uma das compras

    int tempoEstimadoCompra; // soma do tempo de compra dos proprios produtos
    int tempoEstimadoCaixa;  // soma do tempo de caixa dos proprios produtos
    int tempoEstimadoFila;   // soma do tempo dos produtos das pessoas a sua frente no momento em que entrou na fila (== ao tempoTotalEspera)
    int tempoAtraso;         // tempo de atraso da proprio pessoa (random)

    int tempoBrinde; // soma do atraso aleatorio de cada pessoa a sua frente

    Lista *listaProdutos; // lista dos produtos
    float precoTotalProdutos;
} ClienteStruct;

typedef struct
{
    int nivel, n_vendas; // NIVEL 1/2/3
    float salario;
} NivelFuncionarioStruct;

typedef struct
{
    int numCaixasTotal,          // FEITO
        numCaixasAbertas,        // NADA
        probGerarPessoa,         // FEITO
        numCaixasAbertasAranque, // dsalkjajhdsjhasdjhasdjhkasdjkasdjhkajkh
        probUsarSaldoCartao,     // POR FAZER--
        lotacaoMaxima,           // FEITO
        lojaAberta,              // NADA
        VerTransacoes,           // NADA
        threadGlobalAranque,     // FEITO
        TempoLimiteSuperior,     // POR FAZER--
        TempoLimiteInferior,     // POR FAZER--
        QuantMaxProd,            // POR FAZER--
        QuantMinProd,            // POR FAZER--
        tempoAtrasoMaximoBrinde; // POR FAZER--
    float eurosPorSegundoAdiantamentoFuncinario,
        percentagemParaAtraso,
        percentagemPrecoAngariarSaldo,
        multiplicadorTempo; // POR FAZER
    NivelFuncionarioStruct nivelFuncionario[3];
} OpcaoStruct;

typedef enum
{
    CLIENTES,
    FUNCIONARIOS,
    PRODUTOS
} TipoDados;

typedef struct
{
    Lista *caixas, *PessoasAcabaramTempoDeCompra;
} GlobalStruct;

typedef struct
{
    FuncionarioStruct *funcionario;
    Lista *listaProdutos;
    int tempoEstimadoCaixa, tempoAtraso;
    float movimentoCartaoCliente, precoTotal, valorProdutoOferecido;
    DataStruct dataTransacao;
    // Falta struct hora
} HistoricoSubStructCaixa;

typedef struct
{
    char *nome;
    int id;
    Lista **caixas; // vetor de listas de tipo HistoricoSubStructCaixa
} HistoricoSubStructCliente;

typedef struct
{
    int *tempoEsperaCadaCaixa, *numeroClienteFilaCadaCaixa, numerosCaixasAbertas, numeroClienteSupermercado;
    // Ser criativo para adicionar mais
} DadosInstantaneoStruct;

typedef struct
{
    float *tempoMedioEsperaCadaCaixa,
        tempoMedioEsperaTodasCaixas,
        *numeroMedioClienteFilaCadaCaixa,
        numeroMedioClienteFilaTodasCaixas,
        numeroMedioCaixasAbertas,
        numeroMedioClienteSupermercado;
    // Ser criativo para adicionar mais
} DadosEstatisticosInfo;

typedef struct
{
    DadosEstatisticosInfo globais, mediaDiaria;
    DadosInstantaneoStruct dadosIntantaneosdiarios[24][6];
} DadosEstatisticosStruct; // Vai ser guardado nos ficheios txt

typedef struct
{
    int tamanhoVetorHash;
    Lista **HistoricoTransacoes; // vetor de listas com tamanho igual à variavel acima
    pthread_mutex_t HistoricoTransacoesLock;
    DadosEstatisticosStruct *dadosEstatisticos;
} HistoricoStruct;

// GLOBAL VARIABLES
extern OpcaoStruct Opcoes;
extern GlobalStruct Global;
extern HistoricoStruct HistoricoDados;
extern pthread_mutex_t ClientesLock, FuncionariosLock, PessoasAcabaramTempoDeCompraLock;
extern ClienteStruct **Clientes;
extern FuncionarioStruct **Funcionarios;
extern ProdutoStruct *Produtos;
extern int n_clientes, n_clientesAtivos, n_funcionarios, n_funcionariosAtivos, n_produtos;

int CriarGrafico();
// menu.c
void menu();
void menuClientes();
void menuFuncionarios();
void menuProdutos();
void menuConfig();
void menuPesquisarClientes();
void menuPesquisarFuncionarios();
void menuPesquisarProduto();
int menuvalidarCaixaFuncionarios();
int menuResolverCaixaFuncionario();

// opcoes.c
void editarNumCaixas();
void editarProbGerarPessoa();
void editarLotacaoMax();
void editarLojaAbertaAranque();
void Init();
void closeAll();
void editarVerTransacoes();
void editarProbUsarSaldoCartao();
void editarTempoLimiteSuperior();
void editarTempoLimiteInferior();
void editarTempoAtrasoMaximoBrinde();
void editarQuantMinProd();
void editarQuantMaxProd();
void editarMultiplicadorTempo();

// clientes.c
void verClientes();
void verClientesCaixa();
void verClientesInativos();
void verClientesEmLoja();
int encontrarIdCliente(int id);
void pesquisarClienteID();
void pesquisarClienteNome();
void adicionarCliente();
void editarCliente();
void removerCliente();
void criarProdutosAddCliente(ClienteStruct *cliente);
void calculos_TempoPreco_Cliente(ClienteStruct *cliente);
ClienteStruct *escolherCliente();
void DesocuparCliente(ClienteStruct *pessoa);
float atualizarSaldoCliente(ClienteStruct *cliente);
ClienteStruct *criarGuest();
int pesquisarClienteVetorBatente(ClienteStruct *pessoa);
void destruirCliente(void *Cliente);
float oferecerBrinde(ClienteStruct *cliente);
void encontrarCaixaCliente(ClienteStruct *cliente);
void verSeClienteEspecificoEmCaixa();

// caixas.c
CaixaStruct *MelhorCaixa();
void SelecionarCaixa();
void atenderPessoa(CaixaStruct *caixa);
void criarCaixaInit();
void *ThreadCaixa(void *arg);
void removerCaixa();

// funcionarios.c
int encontrarIdFuncionario(int id);
// float convertNumeroDeVendasSalario_vetor(int pos);  //Nao esta a ser usada
// NivelFuncionarioStruct getNivelFuncionario(FuncionarioStruct *funcionario); //Nao esta a ser usada
void verFuncionariosCaixa();
void verFuncionariosInativos();
void editarFuncionarios();
void adicionarFuncionario();
void removerFuncionario();
void pesquisarFuncionariosNome();
void pesquisarFuncionariosID();
void atualizarDadosFuncionario(FuncionarioStruct *funcionario, float atrasoMedio);
void verFuncionarios();
FuncionarioStruct *escolherFuncionarios();

// produtos.c
int pesquisarProdutoListaRealizarAcao(Lista *lista, ProdutoStruct *produto);
void verProdutos();
void adicionarProduto();
void editarProduto();
void removerProduto();
void pesquisarProdutoID();
void pesquisarProdutoNome();
int compareProduto(void *p1, void *p2);
ProdutoStruct *escolherProduto();
void destruirProduto(void *Produto);

// ImportExport.c
int importarCount(char *filename);
void importarClientes(char **linhaString, int n_linha, int n_colunas);
void importarFuncionarios(char **linhaString, int n_linha, int n_colunas);
void importarProdutos(char **linhaString, int n_linha, int n_colunas);
void importarDados(void(guardarDados)(char **, int, int), TipoDados tipo);
void exportarDados(void(guardarDadosTxt)(FILE *, int), TipoDados tipo);
void guardarClienteTxt(FILE *file, int i);
void guardarFuncionarioTxt(FILE *file, int i);
void guardarProdutoTxt(FILE *file, int i);
void importOpcoes();
void exportarOpcoes();

// Utils.c
void setPortugues();
int Aleatorio(int min, int max);
DataStruct gerarData(int anoMin, int anoMax);
int DataAntesDepois(DataStruct d1, DataStruct d2);
void dormir(int tempo);
struct tm getCurrentTime();
int checkIFfileExists(char *filepath);
int generateID(int (*checkIfExists)(int));
int minimo(int a, int b, int c);
int PesquisaParecido(char *str1, char *str2);
void bufferclear();
int validarData(DataStruct date, int minAno, int maxAno);
void scanfs(const char *formato, void *DataScanf, char *MensagemRepitida, char *AvisoError);
void formatTime(long long milliseconds, char *string);
DataStruct formatTimeStruct(long long milliseconds);
long long getCurrentTimeMillisecounds();
void scanfv(const char *formato, void *DataScanf, char *MensagemRepitida, char *AvisoError, int (*validator)(void *, void *), ...);
int validateRange(void *DataScanf, void *args);
int validateRangeFloat(void *DataScanf, void *args);
int validateIsAlphabetic(void *DataScanf, void *args);

// ThreadGlobal.c
void changeStateThreadGlobal();
void *ThreadGlobal();
void *ThreadEsperaTempoCompra(void *args);

// historico.c
void initHistorico();
void initDadosEstatisticos();
int hashFunction(char *nome);
void *criarElementoClienteHistorico(ClienteStruct *cliente);
void *criarInfoHistorico(CaixaStruct *caixa, float movimentoSaldoCartao, float valorProdutoOferecido);
void AddHistorico_Hash(CaixaStruct *caixa, float movimentoSaldoCartao, float valorProdutoOferecido);
void pesquisarClienteNoHistorico(ClienteStruct *cliente);

#endif