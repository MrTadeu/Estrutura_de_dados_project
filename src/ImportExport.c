#include "../includes/TipoDados.h"

/* 
int main(){
    importarDados("../Data/clientes.txt", 5, importarClientes, CLIENTES);
    importarDados("../Data/funcionarios.txt", 5, importarFuncionarios, FUNCIONARIOS);
    
    printf("\nClientes");
    for (int i = 0; i < n_clientes; i++){
        printf("\nLinha %d: ID: %d NOME: %s DATANASC: %d/%d/%d", i+1,Clientes[i].id, Clientes[i].nome, Clientes[i].dataNascimento.dia, Clientes[i].dataNascimento.mes, Clientes[i].dataNascimento.ano);
    }
    printf("\n\nFuncionarios");
    for (int i = 0; i < n_funcionarios; i++){
        printf("\nLinha %d: ID: %d NOME: %s", i+1,Funcionarios[i].id, Funcionarios[i].nome);
    }
} */


int importarCount(char *filename){
    FILE *file = fopen(filename,"r");
    char linhaString[250], *filedata;
    int n_linhas = 0;
    int n_total_linhas = 0;


    if (!file) {
        printf("\n\n\tImpossivel abrir Ficheiro [red]%s[/red]\n\n", filename);
        exit(1);
    }

    while (!feof(file)){
        fgets(linhaString,250,file);
        char *pch = strtok (linhaString, "\t\r\n");
        int count = 0;

        while (pch != NULL){
            filedata = malloc((strlen(pch)+1));
            strcpy(filedata, pch);
            pch = strtok (NULL, "\t\r\n");
            count++;
        }
        
        if(count == 1 &&  n_linhas == 0){
            n_total_linhas = atoi(filedata);
            fclose(file);
            return n_total_linhas;
        }

        n_linhas++;
    }
    fclose(file);
    return n_linhas;
}

void importarClientes(char **linhaString, int n_linha){
    Clientes[n_linha].id = atoi(linhaString[0]);
    Clientes[n_linha].nome = malloc((strlen(linhaString[1])+1));
    strcpy(Clientes[n_linha].nome, linhaString[1]);
}

void importarFuncionarios(char **linhaString, int n_linha){
    Funcionarios[n_linha].id = atoi(linhaString[0]);
    Funcionarios[n_linha].nome = malloc((strlen(linhaString[1])+1));
    strcpy(Funcionarios[n_linha].nome, linhaString[1]);
}

void importarProdutos(char **linhaString, int n_linha){
    Produtos[n_linha].id = atoi(linhaString[0]);
    Produtos[n_linha].nome = malloc((strlen(linhaString[1])+1));
    strcpy(Produtos[n_linha].nome, linhaString[1]);
    Produtos[n_linha].preco = atof(linhaString[2]);
    Produtos[n_linha].tempoCompra = atof(linhaString[3]);
    Produtos[n_linha].tempoCaixa = atof(linhaString[4]);
}

void importarDados(void (guardarDados)(char **, int), TipoDados tipo){
    int n_linha = 0, countFile, colunas = 0;
    char **filedata = malloc(colunas*sizeof(char *)), *linhaString = malloc(250), *filename = malloc(40);

    if(tipo == CLIENTES){
        strcpy(filename, "Data/clientes.txt");
        colunas = 2;
        countFile = importarCount(filename);
        n_clientes = countFile;
        Clientes = malloc(sizeof(ClienteStruct)*countFile);
    }
    if(tipo == FUNCIONARIOS){
        strcpy(filename, "Data/funcionarios.txt");
        colunas = 2;
        countFile = importarCount(filename);
        n_funcionarios = countFile;
        Funcionarios = malloc(sizeof(FuncionarioStruct)*countFile);
    }
    if(tipo == PRODUTOS){
        strcpy(filename, "Data/produtos.txt");
        colunas = 5;
        countFile = importarCount(filename);
        n_produtos = countFile;
        Produtos = malloc(sizeof(ProdutoStruct)*countFile);
    }

    
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("\n\n\tImpossivel abrir Ficheiro [red]%s[/red]\n\n", filename);
        exit(1);
    }

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
        
        if(count == 1 &&  n_linha == 0){
            continue;
        }

        guardarDados(filedata, n_linha);
        n_linha++;
    }

    free(filedata);
    free(linhaString);
    free(filename);
    fclose(file);
}