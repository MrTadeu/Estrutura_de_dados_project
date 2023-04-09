#include "TipoDados.h"

/* void armazenarCliente(void *Ptrcliente, char *linha){
    ClienteStruct *cliente = (ClienteStruct *) Ptrcliente;
    char buffer[500];
    sscanf(linha, "%d,%s", &(*cliente).id, buffer);
    strcpy(cliente->nome, buffer);
}

void armazenarFuncionario(void *PtrFuncionario, char* linha){
    FuncionarioStruct *funcionario = (FuncionarioStruct *) PtrFuncionario;
    char buffer[500];
    sscanf(linha, "%d,%s", &(*funcionario).id, buffer);
    strcpy(funcionario->nome, buffer);
}

void armazenarProduto(void *PtrProduto, char *linha){
    ProdutoStruct *produto = (ProdutoStruct *) PtrProduto;
    char buffer[1000];
    sscanf(linha, "%d,%s,%f,%f,%f", &(*produto).codigo, produto->nome, &produto->preco, &produto->tempoCompra, &produto->tempoCaixa);
}*/

ClienteStruct* importarClientes(int* totalClientes, char *nomeficheiro){
    char linha[1000], buffer[1000];
    int QtPalavras;
    *totalClientes = 0;

    FILE *f = fopen(nomeficheiro, "r");
    if(!f){
        printf("\tError: cant open file\n");
        return NULL;
    }

    ClienteStruct* dadosImportados = (ClienteStruct *) malloc(sizeof(ClienteStruct));
    printf("teste\n");

    while(fgets(linha, sizeof(linha), f)){
        printf("teste\n");
        sscanf(linha, "%d,%s", &dadosImportados[*totalClientes].id, buffer);
        strcpy(dadosImportados[*totalClientes].nome, buffer);
        printf("ID: %d, Nome: %s\n", dadosImportados[*totalClientes].id, dadosImportados[*totalClientes].nome);
        *totalClientes = *totalClientes + 1;
    }
    printf("testesaaaaaaaaaaaaaaaaaaaaaaaaa\n");
    return dadosImportados;
} 

FuncionarioStruct* importarFuncionarios(int* totalFuncionarios, char *nomeficheiro){
    char linha[1000];
    int QtPalavras;
    *totalFuncionarios = 0;

    FILE *f = fopen(nomeficheiro, "r");
    if(!f){
        printf("\tError: cant open file\n");
        return NULL;
    }

    FuncionarioStruct* dadosImportados = (FuncionarioStruct *) malloc(sizeof(FuncionarioStruct));

    while(fgets(linha, sizeof(linha), f)){
        sscanf(linha, "%d,%s", &dadosImportados[*totalFuncionarios].id, dadosImportados[*totalFuncionarios].nome);
        *totalFuncionarios = *totalFuncionarios + 1;
    }
    return dadosImportados;
}

ProdutoStruct* importarProdutos(int* totalProdutos, char *nomeficheiro){
    char linha[1000];
    int QtPalavras;
    *totalProdutos = 0;

    FILE *f = fopen(nomeficheiro, "r");
    if(!f){
        printf("\tError: cant open file\n");
        return NULL;
    }

    ProdutoStruct* dadosImportados = (ProdutoStruct *) malloc(sizeof(ProdutoStruct));

    while(fgets(linha, sizeof(linha), f)){
        sscanf(linha, "%d,%s,%f,%f,%f", &dadosImportados[*totalProdutos].codigo, dadosImportados[*totalProdutos].nome, &dadosImportados[*totalProdutos].preco, &dadosImportados[*totalProdutos].tempoCompra, &dadosImportados[*totalProdutos].tempoCaixa);
        *totalProdutos = *totalProdutos + 1;
    }

    return dadosImportados;
}