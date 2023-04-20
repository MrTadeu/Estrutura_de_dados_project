#include "../includes/TipoDados.h"

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


//GLOBAL VARIABLES
extern ClienteStruct *Clientes;
extern FuncionarioStruct *Funcionarios;
extern ProdutoStruct *Produtos;
extern int n_clientes, n_funcionarios, n_produtos;
/* void importarClientesNew(); */

/* int main(){
    printf("Hello World");
    importarClientesNew();

    return 0;
} */


void importarClientesNew(){
    FILE *file = fopen("../Data/clientes.txt","r");
    char **filedata = malloc(5*sizeof(char *)), *linhaString = malloc(250);
    Clientes = malloc(sizeof(ClienteStruct));

    if (!file) {
        printf("\n\n\tImpossivel abrir Ficheiro [red]clientes.txt[/red]\n\n");
        exit(1);
    }

    int linha = 0;
    while (!feof(file)){
        fgets(linhaString,250,file);
        char *pch = strtok (linhaString, "\t\r\n");
        
        int count = 0;

        while (pch != NULL){
            filedata[count] = malloc((strlen(pch)+1));
            strcpy(filedata[count], pch);
            pch = strtok (NULL, "\t\r\n");
            count++;
        }
        Clientes = realloc(Clientes, ((n_clientes)+1)*sizeof(ClienteStruct));

        Clientes[n_clientes].id = atoi(filedata[0]);
        Clientes[n_clientes].nome = malloc((strlen(filedata[1])+1));
        strcpy(Clientes[n_clientes].nome, filedata[1]);

        n_clientes++;
    }

    for (int i = 0; i < n_clientes; i++){
        printf("\nLinha %d: ID: %d NOME: %s", i+1,Clientes[i].id, Clientes[i].nome);
    }

    fclose(file);
}





/* 



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
} */