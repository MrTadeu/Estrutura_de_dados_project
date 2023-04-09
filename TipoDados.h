#ifndef TIPODADOS_H_INCLUDED
#define TIPODADOS_H_INCLUDED

#include "ListaLigada.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>
#include <time.h>     // Para contar o tempo
#include <conio.h>   // 

typedef struct{
    char nome[100];
    int id, experiencia;                // A experiencia é a quantidade de vendas realizadas e influencia o salário.
    float atrasoMedio, bonus, salario;  // O atraso medio pode ser negativo ou positivo e influencia o bonus.
}FuncionarioStruct;
FuncionarioStruct *ptrFuncionario();

typedef struct{
    int idCaixa, tempoTotalEspera;
    FuncionarioStruct funcionario;
    LG *fila;
}CaixaStruct;

typedef struct{
    char nome[100];
    int codigo;
    float tempoCompra, tempoCaixa, preco;
}ProdutoStruct;
ProdutoStruct *ptrProdutos();

typedef struct{
    int dia, mes, ano;
}DataStruct;

typedef struct{
    char nome[100];
    DataStruct dataNascimento;
    int id;                             // guests: -1
    float saldoCartaoCliente;           // guests: -1 | clientes: angariado a cada compra e pode ser usado em qualquer uma das compras

    int tempoEstimadoCaixa;         // soma do tempo de caixa dos proprios produtos
    int tempoEstimadoFila;          // soma do tempo dos produtos das pessoas a sua frente no momento em que entrou na fila
    int tempoAtraso;                // soma do atraso aleatorio de cada pessoa a sua frente

    LG *listaProdutos;
}PessoaStruct;
PessoaStruct *ptrPessoa();


void *escolherAleatorioVetor(void *vetor, int tamanhoVetor, size_t tamanhoElemento, void *(*criarPtrStruct)());



CaixaStruct *criarCaixa(FuncionarioStruct funcionario);


DataStruct gerarDataValidaAleatoria(DataStruct data, int anoMin, int anoMax);
int DataAntes_Depois(DataStruct d1, DataStruct d2);


//Funções importar_exportar
PessoaStruct* importarClientes(int* numclientes, char *nomeficheiro);
FuncionarioStruct* importarFuncionarios(int* numfuncionarios, char* nomeficheiro);
ProdutoStruct* importarProdutos(int* numProdutos, char* nomeficheiro);


#endif