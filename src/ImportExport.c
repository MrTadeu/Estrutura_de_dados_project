#include "../includes/TipoDados.h"

void importOpcoes(){
    char *file = malloc(sizeof(char)*16);
    strcpy(file,"Data/opcoes.bin");
    pthread_t threadRelogio, threadS;
    pthread_create(&threadRelogio, NULL, threadTempo, NULL);
    pthread_create(&threadS, NULL, threadSchedule, NULL);
    
    if(checkIFfileExists(file) == 1){
        FILE *file = fopen("Data/opcoes.bin", "rb");
        if (!file) {
            printf("\n\n\tImpossivel abrir Ficheiro [red]Data/opcoes.bin[/red]\n\n");
            exit(1);
        }
        fread(&Opcoes, sizeof(OpcaoStruct), 1, file);
        fclose(file);
    }
    else{
        Opcoes.numCaixasTotal = 10;
        Opcoes.numCaixasAbertas = 0;
        Opcoes.probGerarPessoa = 100;
        Opcoes.probUsarSaldoCartao = 30;
        Opcoes.percentagemPrecoAngariarSaldo = 10; // 0-10%
        Opcoes.percentagemParaAtraso = 20;
        Opcoes.lotacaoMaxima = 200;
        Opcoes.lojaAberta = 0;
        Opcoes.VerTransacoes = 0;
        Opcoes.threadGlobalAranque = 0;
        Opcoes.nivelFuncionario[0].n_vendas = 10000;  
        Opcoes.nivelFuncionario[1].n_vendas = 30000;  
        Opcoes.nivelFuncionario[2].n_vendas = 60000;  
        Opcoes.nivelFuncionario[0].salario = 850.0;
        Opcoes.nivelFuncionario[1].salario = 900.0;
        Opcoes.nivelFuncionario[2].salario = 950.0;
        Opcoes.eurosPorSegundoAdiantamentoFuncinario = 50;
        Opcoes.TempoLimiteInferior = 180000; // 180 * 1000
        Opcoes.TempoLimiteSuperior = 200000; // 200 * 1000
        Opcoes.QuantMinProd = 1;
        Opcoes.QuantMaxProd = 20;
        Opcoes.multiplicadorTempo = 1.0; //*Quanto menor, mais depressa o tempo decorre
        Opcoes.tempoAtrasoMaximoBrinde = 900000; // *15 minutos 900 segundos * 1000 = 900 milisegundos
    }
    Opcoes.nivelFuncionario[0].nivel = 1;
    Opcoes.nivelFuncionario[1].nivel = 2;
    Opcoes.nivelFuncionario[2].nivel = 3;
    free(file);
}

void importarClientes(char **linhaString, int n_linha, int n_colunas){
    Clientes[n_linha] = malloc(sizeof(ClienteStruct));
    Clientes[n_linha]->id = atoi(linhaString[0]);
    Clientes[n_linha]->nome = malloc((strlen(linhaString[1])+1));
    strcpy(Clientes[n_linha]->nome, linhaString[1]);
    if(n_colunas == 6){
        Clientes[n_linha]->saldoCartaoCliente = atof(linhaString[2]);
        Clientes[n_linha]->dataNascimento.dia = atoi(linhaString[3]);
        Clientes[n_linha]->dataNascimento.mes = atoi(linhaString[4]);
        Clientes[n_linha]->dataNascimento.ano = atoi(linhaString[5]);
    }
    else{
        Clientes[n_linha]->saldoCartaoCliente = 0;
        struct tm tm = getCurrentTime();
        Clientes[n_linha]->dataNascimento = gerarData(tm.tm_year + 1900 - 110, tm.tm_year + 1900 - 10);
    }
    Clientes[n_linha]->precoTotalProdutos = 0;
    Clientes[n_linha]->tempoEstimadoCompra = 0;
    Clientes[n_linha]->tempoEstimadoFila = 0;
    Clientes[n_linha]->tempoEstimadoCaixa = 0;
    Clientes[n_linha]->tempoAtraso = 0;
    Clientes[n_linha]->ativo = 0;
    Clientes[n_linha]->tempoBrinde = 0;
}

void importarFuncionarios(char **linhaString, int n_linha, int n_colunas){
    Funcionarios[n_linha] = malloc(sizeof(FuncionarioStruct));
    Funcionarios[n_linha]->id = atoi(linhaString[0]);
    Funcionarios[n_linha]->nome = malloc((strlen(linhaString[1])+1));
    strcpy(Funcionarios[n_linha]->nome, linhaString[1]);
    if(n_colunas == 6){
        Funcionarios[n_linha]->n_vendas = atoi(linhaString[3]);
        Funcionarios[n_linha]->atrasoMedio = atof(linhaString[5]);
    }
    else{
        Funcionarios[n_linha]->n_vendas = 0;
        Funcionarios[n_linha]->atrasoMedio = 0;
    }
    Funcionarios[n_linha]->ativo = 0;
}

void importarProdutos(char **linhaString, int n_linha, int n_colunas){
    if(n_colunas == 5){
        Produtos[n_linha].id = atoi(linhaString[0]);
        Produtos[n_linha].quantidadeProdutosRepetidos = 1;
        Produtos[n_linha].oferecido = 0;
        Produtos[n_linha].nome = malloc((strlen(linhaString[1])+1));
        strcpy(Produtos[n_linha].nome, linhaString[1]);
        Produtos[n_linha].preco = atof(linhaString[2]);
        Produtos[n_linha].tempoCompra = (int) (atof(linhaString[3])*1000);
        Produtos[n_linha].tempoCaixa = (int) (atof(linhaString[4])*1000);
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
    char linhaString[250], *filedata = NULL;
    int n_linhas = 0;

    if (!file) {
        printc("\n\n\tImpossivel abrir Ficheiro [red]%s[/red]\n\n", filename);
        exit(1);
    }

    while (!feof(file)){
        fgets(linhaString,250,file);
        char *pch = strtok (linhaString, "\t\r\n");
        int count = 0;

        while (pch != NULL){
            filedata = (char *) malloc(sizeof(char)*(strlen(pch)+1));
            strcpy(filedata, pch);
            pch = strtok (NULL, "\t\r\n");
            count++;
        }
        
        if(count == 1 &&  n_linhas == 0){
            n_linhas = atoi(filedata);
            free(filedata);
            fclose(file);
            return n_linhas;
        }

        if(count == 0 &&  n_linhas == 0){
            free(filedata);
            fclose(file);
            return 0;
        }

        n_linhas++;
        if (filedata != NULL) {
            free(filedata);
        }
    }
    fclose(file);
    return n_linhas;
}

void exportarDados(void (guardarDadosTxt)(FILE *, int), TipoDados tipo){
    char *filename = (char *) malloc(sizeof(char)*40);
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
    fprintf(file, "%d", n_elementos);
    for (int i = 0; i < n_elementos; i++){
        guardarDadosTxt(file, i);
    }

    free(filename);
    fclose(file);
}

void guardarClienteTxt(FILE *file, int i){
    fprintf(file, "\n%d\t%s\t%f\t%d\t%d\t%d", Clientes[i]->id, Clientes[i]->nome, Clientes[i]->saldoCartaoCliente, Clientes[i]->dataNascimento.dia, Clientes[i]->dataNascimento.mes, Clientes[i]->dataNascimento.ano);
}

void guardarFuncionarioTxt(FILE *file, int i){
    fprintf(file, "\n%d\t%s\t%d\t%d", Funcionarios[i]->id, Funcionarios[i]->nome, Funcionarios[i]->n_vendas, Funcionarios[i]->atrasoMedio);
}

void guardarProdutoTxt(FILE *file, int i){
    float tempoCompra = Produtos[i].tempoCompra/1000, tempoCaixa = Produtos[i].tempoCaixa/1000;
    fprintf(file, "\n%d\t%s\t%f\t%f\t%f", Produtos[i].id, Produtos[i].nome, Produtos[i].preco, tempoCompra, tempoCaixa);
}

void exportarOpcoes(){
    Opcoes.lojaAberta = 0;
    Opcoes.VerTransacoes = 0;
    Opcoes.multiplicadorTempo = 1.0;
    Opcoes.numCaixasAbertas = 0;
    FILE *file = fopen("Data/opcoes.bin", "wb");
    if (!file) {
        printc("\n\n\tImpossivel abrir Ficheiro [red]opcoes.bin[/red]\n\n");
        exit(1);
    }
    fwrite(&Opcoes, sizeof(OpcaoStruct), 1, file);

    fclose(file);
}

void exportarOpcoesInsta(){
    FILE *file = fopen("Data/opcoes.bin", "wb");
    if (!file) {
        printc("\n\n\tImpossivel abrir Ficheiro [red]opcoes.bin[/red]\n\n");
        exit(1);
    }
    fwrite(&Opcoes, sizeof(OpcaoStruct), 1, file);
    fclose(file);
}

void exportHistoricoTransacoes(){
    
}

void exportHistoricoDadosEstatisticos(){

}