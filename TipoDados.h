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

typedef struct{
    int idCaixa, idFuncionario, tempoTotalEspera;

    //preencher
    LG *fila;
}CaixaStruct;

typedef struct{
    char nome[100];
    int codigo;
    float tempoCompra, tempoCaixa, preco;
}ProdutoStruct;

typedef struct{
    char nome[100];
    int id;                             // guests: -1
    float saldoCartaoCliente;           // guests: -1 | clientes: angariado a cada compra e pode ser usado em qualquer uma das compras

    int tempoAtendimento;               // soma do tempo dos proprios produtos
    int tempoEstimadoEspera;            // soma do tempo dos produtos das pessoas a sua frente no momento em que entrou na fila
    int tempoRealEspera;                // tempoEstimadoEspera + soma do atraso aleatorio de atendimento de cada pessoa a sua frente

    ProdutoStruct *cesto;
}PessoaStruct;

// falta implementer funcao de MostrarInfo e DestruirInfo para LG

#endif