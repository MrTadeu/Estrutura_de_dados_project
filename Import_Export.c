#include "TipoDados.h"

/* void armazenarCliente(void *Ptrcliente, char *linha){
    ClienteStruct *cliente = (ClienteStruct *) Ptrcliente;
    char buffer[500];
    sscanf(linha, "%d,%s", &cliente->id, buffer);
    strcpy(cliente->nome, buffer);
}

void armazenarFuncionario(void *PtrFuncionario, char* linha){
    FuncionarioStruct *funcionario = (FuncionarioStruct *) PtrFuncionario;
    char buffer[500];
    sscanf(linha, "%d,%s", &funcionario->id, buffer);
    strcpy(funcionario->nome, buffer);
}

void armazenarProduto(void *PtrProduto, char *linha){
    ProdutoStruct *produto = (ProdutoStruct *) PtrProduto;
    char buffer[500];
    sscanf(linha, "%d,%s,%f,%f,%f", &produto->codigo, produto->nome, &produto->preco, &produto->tempoCompra, &produto->tempoCaixa);
}*/

ClienteStruct* importarClientes(int* totalClientes, char* nomeficheiro){
    char linha[1000], *buffer;
    int i = 0;
    *totalClientes = 0;
    
    FILE* f = fopen(nomeficheiro, "r");
    if(!f){
        printf("\tError: cant open file\n");
        return NULL;
    }
    fgets(linha, sizeof(linha), f); //Para limpar lixo da primeira linha
    
    fgets(linha, sizeof(linha), f);
    sscanf(linha, "%d", totalClientes);
    ClienteStruct* dadosImportados = (ClienteStruct*) malloc(*totalClientes * sizeof(ClienteStruct));

    while(fgets(linha, sizeof(linha), f)){
        dadosImportados[i].id = atoi(strtok(linha, ","));

        buffer = strtok(NULL, "\n");
        strncpy(dadosImportados[i].nome, buffer, sizeof(dadosImportados[i].nome)-1); // A guardar o nome do cliente
        dadosImportados[i].nome[sizeof(dadosImportados[i].nome)-1] = '\0';

        i++;
    }
    return dadosImportados;
}

FuncionarioStruct* importarFuncionarios(int* totalFuncionarios, char *nomeficheiro){
    char linha[1000], *buffer;
    int i = 0;
    *totalFuncionarios = 0;
    
    FILE* f = fopen(nomeficheiro, "r");
    if(!f){
        printf("\tError: cant open file\n");
        return NULL;
    }
    fgets(linha, sizeof(linha), f); //Para limpar lixo da primeira linha
    
    fgets(linha, sizeof(linha), f);
    sscanf(linha, "%d", totalFuncionarios);
    FuncionarioStruct* dadosImportados = (FuncionarioStruct*) malloc(*totalFuncionarios * sizeof(FuncionarioStruct));

    while(fgets(linha, sizeof(linha), f)){
        dadosImportados[i].id = atoi(strtok(linha, ","));

        buffer = strtok(NULL, "\n");
        strncpy(dadosImportados[i].nome, buffer, sizeof(dadosImportados[i].nome)-1); // A guardar o nome do cliente
        dadosImportados[i].nome[sizeof(dadosImportados[i].nome)-1] = '\0';

        i++;
    }
    return dadosImportados;
}

ProdutoStruct* importarProdutos(int* totalProdutos, char *nomeficheiro){
    char linha[1000], *buffer;
    int i = 0;
    *totalProdutos = 0;
    
    FILE* f = fopen(nomeficheiro, "r");
    if(!f){
        printf("\tError: cant open file\n");
        return NULL;
    }
    fgets(linha, sizeof(linha), f); //Para limpar lixo da primeira linha
    
    fgets(linha, sizeof(linha), f);
    sscanf(linha, "%d", totalProdutos);
    ProdutoStruct* dadosImportados = (ProdutoStruct*) malloc(*totalProdutos * sizeof(ProdutoStruct));

    while(fgets(linha, sizeof(linha), f)){
        dadosImportados[i].codigo = atoi(strtok(linha, ","));

        buffer = strtok(NULL, ",");
        strncpy(dadosImportados[i].nome, buffer, sizeof(dadosImportados[i].nome)-1); // A guardar o nome do cliente
        dadosImportados[i].nome[sizeof(dadosImportados[i].nome)-1] = '\0';

        buffer = strtok(NULL, ",");
        sscanf(buffer, "%f", &dadosImportados[i].preco);

        buffer = strtok(NULL, ",");
        sscanf(buffer, "%f", &dadosImportados[i].tempoCompra);

        buffer = strtok(NULL, "\n");
        sscanf(buffer, "%f", &dadosImportados[i].tempoCaixa);

        i++;
    }
    return dadosImportados;
}