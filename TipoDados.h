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
    char nome[200];
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
    int codigo;
    char nome[200];
    float preco, tempoCompra, tempoCaixa;
}ProdutoStruct;
ProdutoStruct *ptrProdutos();

typedef struct{
    int dia, mes, ano;
}DataStruct;

typedef struct{
    int id;                             // guests: -1
    char nome[200];                     // guests: "none"
    DataStruct dataNascimento;          // guests: 0/0/0
    float saldoCartaoCliente;           // guests: -1 | clientes: angariado a cada compra e pode ser usado em qualquer uma das compras

    int tempoEstimadoCaixa;        // soma do tempo de caixa dos proprios produtos
    int tempoEstimadoFila;         // soma do tempo dos produtos das pessoas a sua frente no momento em que entrou na fila
    int tempoAtraso;               // soma do atraso aleatorio de cada pessoa a sua frente
    LG *listaProdutos;             // lista dos produtos
}ClienteStruct;
ClienteStruct *ptrPessoa();


void escolherAleatorioVetor(void *vetor, int tamanhoVetor, size_t tamanhoElemento, void *ptrElemento);



CaixaStruct *criarCaixa(FuncionarioStruct funcionario);


DataStruct gerarDataValidaAleatoria(DataStruct data, int anoMin, int anoMax);
int DataAntes_Depois(DataStruct d1, DataStruct d2);


//Funções importar_exportar
ClienteStruct* importarClientes(int* totalClientes, char *nomeficheiro);
FuncionarioStruct* importarFuncionarios(int* totalClientes, char *nomeficheiro);
ProdutoStruct* importarProdutos(int* totalClientes, char *nomeficheiro);

#endif