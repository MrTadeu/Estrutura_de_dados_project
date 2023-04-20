#ifndef TIPODADOS_H_INCLUDED
#define TIPODADOS_H_INCLUDED

#include "../includes/ListaLigada.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>
#include <time.h>     // Para contar o tempo
#ifndef PTHREAD_H
#include <pthread.h> 
#endif // Para criar as threads
#include <conio.h>   


typedef struct{
    char *nome;
    int id, experiencia;                // A experiencia é a quantidade de vendas realizadas e influencia o salário.
    float atrasoMedio, bonus, salario;  // O atraso medio pode ser negativo ou positivo e influencia o bonus.
}FuncionarioStruct;

typedef struct{
    int id, tempoTotalEspera;
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
    int id;                             // guests: -1
    char *nome;                         // guests: "none"
    DataStruct dataNascimento;          // guests: 0/0/0
    float saldoCartaoCliente;           // guests: -1 | clientes: angariado a cada compra e pode ser usado em qualquer uma das compras

    int tempoEstimadoCompra;        // soma do tempo de compra dos proprios produtos
    int tempoEstimadoFila;          // soma do tempo dos produtos das pessoas a sua frente no momento em que entrou na fila
    int tempoEstimadoCaixa;         // soma do tempo de caixa dos proprios produtos

    int tempoAtraso;                // soma do atraso aleatorio de cada pessoa a sua frente

    Lista *listaProdutos;           // lista dos produtos
}ClienteStruct;


//GLOBAL VARIABLES
extern ClienteStruct *Clientes;
extern FuncionarioStruct *Funcionarios;
extern ProdutoStruct *Produtos;
extern int n_clientes, n_funcionarios, n_produtos;

FuncionarioStruct *criarFuncionario();
CaixaStruct *criarCaixa();
ProdutoStruct *criarProduto();
ClienteStruct *criarCliente();

void escolherAleatorioVetor(void *vetor, int tamanhoVetor, size_t tamanhoElemento, void *ptrElemento); // Funcional

void mostrarFuncionario(void *funcionarioArg, int indentLevel);
void mostrarCaixa(void *caixaArg, int indentLevel);
void mostrarProduto(void *produtoArg, int indentLevel);
void mostrarCliente(void *clienteArg, int indentLevel);

DataStruct gerarDataValidaAleatoria(DataStruct data, int anoMin, int anoMax); // Funcional
int DataAntes_Depois(DataStruct d1, DataStruct d2); // Funcional


//Funções importar_exportar
ClienteStruct* importarClientes(int* totalClientes, char *nomeficheiro); // Funcional
FuncionarioStruct* importarFuncionarios(int* totalClientes, char *nomeficheiro); // Funcional
ProdutoStruct* importarProdutos(int* totalClientes, char *nomeficheiro); // Funcional

#endif