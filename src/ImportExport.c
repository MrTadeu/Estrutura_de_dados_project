#include "../includes/TipoDados.h"

void importGlobal(){
    char *file = malloc(sizeof(char)*16);
    strcpy(file,"Data/global.bin");
    if(checkIFfileExists(file) == 1){
        FILE *file = fopen("Data/global.bin", "rb");
        if (!file) {
            printf("\n\n\tImpossivel abrir Ficheiro [red]Data/global.bin[/red]\n\n");
            exit(1);
        }
        fread(&Global, sizeof(GlobalStruct), 1, file);
        fclose(file);
    }
    else{
        Global.numCaixasTotal = 10;
        Global.numCaixasAbertas = 0;
        Global.probGerarPessoa = 50;
        Global.lotacaoMaxima = 200;
        Global.lojaAberta = 0;
    }
    free(file);
}

void importarClientes(char **linhaString, int n_linha, int n_colunas){
    Clientes[n_linha].id = atoi(linhaString[0]);
    Clientes[n_linha].nome = malloc((strlen(linhaString[1])+1));
    strcpy(Clientes[n_linha].nome, linhaString[1]);
    if(n_colunas == 6){
        Clientes[n_linha].saldoCartaoCliente = atof(linhaString[2]);
        Clientes[n_linha].dataNascimento.dia = atoi(linhaString[3]);
        Clientes[n_linha].dataNascimento.mes = atoi(linhaString[4]);
        Clientes[n_linha].dataNascimento.ano = atoi(linhaString[5]);
    }
    else{
        Clientes[n_linha].saldoCartaoCliente = 0;
        struct tm tm = getCurrentTime();
        Clientes[n_linha].dataNascimento = gerarData(tm.tm_year + 1900 - 110, tm.tm_year + 1900 - 10);
    }
    
    Clientes[n_linha].tempoEstimadoCompra = 0;
    Clientes[n_linha].tempoEstimadoFila = 0;
    Clientes[n_linha].tempoEstimadoCaixa = 0;
    Clientes[n_linha].tempoAtraso = 0;
    Clientes[n_linha].ativo = 0;
}

void importarFuncionarios(char **linhaString, int n_linha, int n_colunas){
    Funcionarios[n_linha].id = atoi(linhaString[0]);
    Funcionarios[n_linha].nome = malloc((strlen(linhaString[1])+1));
    strcpy(Funcionarios[n_linha].nome, linhaString[1]);
    if(n_colunas == 6){
        Funcionarios[n_linha].bonus = atof(linhaString[2]);
        Funcionarios[n_linha].salario = atof(linhaString[3]);
        Funcionarios[n_linha].experiencia = atoi(linhaString[4]);
        Funcionarios[n_linha].atrasoMedio = atof(linhaString[5]);
    }
    else{
        Funcionarios[n_linha].bonus = 0;
        Funcionarios[n_linha].salario = 0;
        Funcionarios[n_linha].experiencia = 0;
        Funcionarios[n_linha].atrasoMedio = 0;
    }
    Funcionarios[n_linha].ativo = 0;
}

void importarProdutos(char **linhaString, int n_linha, int n_colunas){
    if(n_colunas == 5){
        Produtos[n_linha].id = atoi(linhaString[0]);
        Produtos[n_linha].nome = malloc((strlen(linhaString[1])+1));
        strcpy(Produtos[n_linha].nome, linhaString[1]);
        Produtos[n_linha].preco = atof(linhaString[2]);
        Produtos[n_linha].tempoCompra = atof(linhaString[3]);
        Produtos[n_linha].tempoCaixa = atof(linhaString[4]);
    }
}

void importarDados(void (guardarDados)(char **, int, int), TipoDados tipo){
    int n_linha = 0, countFile, colunas = 0;
    char *linhaString = malloc(250), *filename = malloc(40);

    if(tipo == CLIENTES){
        free(Clientes);
        strcpy(filename, "Data/clientes.txt");
        colunas = 6;
        countFile = importarCount(filename);
        n_clientes = countFile;
        Clientes = malloc(sizeof(ClienteStruct)*countFile);
    }
    if(tipo == FUNCIONARIOS){
        free(Funcionarios);
        strcpy(filename, "Data/funcionarios.txt");
        colunas = 6;
        countFile = importarCount(filename);
        n_funcionarios = countFile;
        Funcionarios = malloc(sizeof(FuncionarioStruct)*countFile);
    }
    if(tipo == PRODUTOS){
        free(Produtos);
        strcpy(filename, "Data/produtos.txt");
        colunas = 5;
        countFile = importarCount(filename);
        n_produtos = countFile;
        Produtos = malloc(sizeof(ProdutoStruct)*countFile);
    }
    char **filedata = malloc(colunas*sizeof(char *));
    
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
        guardarDados(filedata, n_linha, count);
        n_linha++;
    }

    free(linhaString);
    free(filename);
    fclose(file);
}

int importarCount(char *filename){
    FILE *file = fopen(filename,"r");
    char linhaString[250], *filedata;
    int n_linhas = 0;
    int n_total_linhas = 0;


    if (!file) {
        printc("\n\n\tImpossivel abrir Ficheiro [red]%s[/red]\n\n", filename);
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
    free(filedata);
    fclose(file);
    return n_linhas;
}

void exportarDados(void (guardarDadosTxt)(FILE *, int), TipoDados tipo){
    char *filename = malloc(40);
    int n_elementos = 0;
   
    if(tipo == CLIENTES){
        strcpy(filename, "Data/clientes.txt");
        n_elementos = n_clientes;
    }
    if(tipo == FUNCIONARIOS){
        strcpy(filename, "Data/funcionarios.txt");
        n_elementos = n_funcionarios;
    }
    if(tipo == PRODUTOS){
        strcpy(filename, "Data/produtos.txt");
        n_elementos = n_produtos;
    }

    FILE *file = fopen(filename, "w");
    if (!file) {
        printc("\n\n\tImpossivel abrir Ficheiro [red]%s[/red]\n\n", filename);
        exit(1);
    }
    fprintf(file, "%d\n", n_elementos);
    for (int i = 0; i < n_elementos; i++){
        guardarDadosTxt(file, i);
    }

    free(filename);
    fclose(file);
}

void guardarClienteTxt(FILE *file, int i){
    fprintf(file, "%d\t%s\t%f\t%d\t%d\t%d\n", Clientes[i].id, Clientes[i].nome, Clientes[i].saldoCartaoCliente, Clientes[i].dataNascimento.dia, Clientes[i].dataNascimento.mes, Clientes[i].dataNascimento.ano);
}

void guardarFuncionarioTxt(FILE *file, int i){
    fprintf(file, "%d\t%s\t%f\t%f\t%d\t%f\n", Funcionarios[i].id, Funcionarios[i].nome, Funcionarios[i].bonus, Funcionarios[i].salario, Funcionarios[i].experiencia, Funcionarios[i].atrasoMedio);
}

void guardarProdutoTxt(FILE *file, int i){
    fprintf(file, "%d\t%s\t%f\t%f\t%f\n", Produtos[i].id, Produtos[i].nome, Produtos[i].preco, Produtos[i].tempoCompra, Produtos[i].tempoCaixa);
}

void exportarGlobal(){
    FILE *file = fopen("Data/global.bin", "wb");
    if (!file) {
        printc("\n\n\tImpossivel abrir Ficheiro [red]global.bin[/red]\n\n");
        exit(1);
    }
    fwrite(&Global, sizeof(GlobalStruct), 1, file);

    fclose(file);
}