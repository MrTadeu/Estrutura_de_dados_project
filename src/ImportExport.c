#include "../includes/TipoDados.h"

void importOpcoes(){
    char *file = malloc(sizeof(char)*16);
    strcpy(file,"Data/opcoes.bin");
    pthread_t threadRelogio, threadS;
    pthread_create(&threadRelogio, NULL, threadTempo, NULL);
    pthread_create(&threadS, NULL, ThreadSchedule, NULL);
    
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

void exportarHistoricoTransacoesParaTXT(const char* diretorio){
    char nomeArquivo[100];
    sprintf(nomeArquivo, "%s/HistoricoTransacoes.txt", diretorio);
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return;
    }

    pthread_mutex_lock(&HistoricoDados.HistoricoTransacoesLock);
    for (int i = 0; i < HistoricoDados.tamanhoVetorHash; i++){
        Elemento *clientesHistorico = HistoricoDados.HistoricoTransacoes[i]->head;
        while (clientesHistorico){
            HistoricoSubStructCliente *clientesHistoricoInfo = (HistoricoSubStructCliente *)clientesHistorico->Info;
            for (int j = 0; j < numeroMaximoCaixasPossivel; j++){
                Elemento *caixasHistorico = clientesHistoricoInfo->caixas[j]->head;
                while (caixasHistorico){   
                    char horas[9];
                    HistoricoSubStructTransacao *caixasHistoricoInfo = (HistoricoSubStructTransacao *)caixasHistorico->Info;
                    formatTime(caixasHistoricoInfo->tempoEstimadoCaixa, horas);

                    fprintf(arquivo, "Nome cliente: %s\tID cliente: %d\nID caixa: %d\tNome funcionário: %s\tID funcionário: %d\nData de transação: %d/%d/%d\tHora: %d:%d:%d\nTempo de espera na fila: %s\t", clientesHistoricoInfo->nome, clientesHistoricoInfo->id, j+1, caixasHistoricoInfo->funcionario->nome, caixasHistoricoInfo->funcionario->id, caixasHistoricoInfo->dataTransacao.dia, caixasHistoricoInfo->dataTransacao.mes, caixasHistoricoInfo->dataTransacao.ano, caixasHistoricoInfo->dataTransacao.hora, caixasHistoricoInfo->dataTransacao.minuto, caixasHistoricoInfo->dataTransacao.segundo, horas);

                    fprintf(arquivo, "Tempo de atraso: ");
                    if (caixasHistoricoInfo->tempoAtraso < 0)
                        fprintf(arquivo, "Adiantou-se: %.2f segundos\n", fabs((float)caixasHistoricoInfo->tempoAtraso / 1000.0));
                    else if (caixasHistoricoInfo->tempoAtraso > 0)
                        fprintf(arquivo, "Atrasou-se: %.2f segundos\n", (float)caixasHistoricoInfo->tempoAtraso / 1000.0);

                    Elemento *produtos = caixasHistoricoInfo->listaProdutos->head;
                    while (produtos)
                    {
                        ProdutoStruct *produtoInfo = (ProdutoStruct *)produtos->Info;
                        fprintf(arquivo, "\n\t\tID produto: %d Nome produto: %s, QT: %dX, Preco: %.2f TCompra: %d TCaixa: %d\n", produtoInfo->id, produtoInfo->nome, produtoInfo->quantidadeProdutosRepetidos, produtoInfo->preco, produtoInfo->tempoCompra, produtoInfo->tempoCaixa);
                        produtos = produtos->next;
                    }

                    fprintf(arquivo,"\tPreço total: %.2f\n", caixasHistoricoInfo->precoTotal);

                    if (caixasHistoricoInfo->valorProdutoOferecido > 0)
                    {
                        fprintf(arquivo,"\tProduto oferecido! Preço: %.2f", caixasHistoricoInfo->valorProdutoOferecido);
                    }
                    fprintf(arquivo,"\tSaldo cartão cliente:\n");
                    if (caixasHistoricoInfo->movimentoCartaoCliente < 0)
                    {
                        fprintf(arquivo,"\t\tO cliente usou %.2f euros", fabs(caixasHistoricoInfo->movimentoCartaoCliente));
                    }
                    else
                        fprintf(arquivo,"\t\tO cliente angariou %.2f euros", caixasHistoricoInfo->movimentoCartaoCliente);

                    caixasHistorico = caixasHistorico->next;
                }
            }
            clientesHistorico = clientesHistorico->next;
        }
    }
    pthread_mutex_unlock(&HistoricoDados.HistoricoTransacoesLock);
    fclose(arquivo);
    printf("Dados exportados com sucesso para o arquivo %s.\n", nomeArquivo);
}

void exportarHistoricoTransacoesParaCSV(const char* diretorio){
    char nomeArquivo[100];
    sprintf(nomeArquivo, "%s/HistoricoTransacoes.csv", diretorio);
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return;
    }

    pthread_mutex_lock(&HistoricoDados.HistoricoTransacoesLock);
    for (int i = 0; i < HistoricoDados.tamanhoVetorHash; i++){
        Elemento *clientesHistorico = HistoricoDados.HistoricoTransacoes[i]->head;
        while (clientesHistorico){
            HistoricoSubStructCliente *clientesHistoricoInfo = (HistoricoSubStructCliente *)clientesHistorico->Info;
            for (int j = 0; j < numeroMaximoCaixasPossivel; j++){
                Elemento *caixasHistorico = clientesHistoricoInfo->caixas[j]->head;
                while (caixasHistorico){   
                    HistoricoSubStructTransacao *caixasHistoricoInfo = (HistoricoSubStructTransacao *)caixasHistorico->Info;
                    char tempoCaixa[9], tempoAtraso[9], tempoCaixaProduto[9], tempoCompraProduto[9];
                    formatTime(caixasHistoricoInfo->tempoEstimadoCaixa, tempoCaixa);
                    formatTime(caixasHistoricoInfo->tempoAtraso, tempoAtraso);

                    fprintf(arquivo, "Nome cliente;ID cliente;ID caixa;Nome funcionario;ID funcionario;Dia de transacao;Mes de transacao;Ano de transacao;Tempo de espera na fila;Tempo de atraso;Produto ID;Produto Nome;Produto Quantidade;Produto Preco;Produto tempo compra;Produto tempo caixa;Preco total;Valor produto Oferecido;Saldo cartao cliente;\n");

                    fprintf(arquivo, "%s;%d;%d;%s;%d;%d;%d;%d;%s;%s\"", clientesHistoricoInfo->nome, clientesHistoricoInfo->id, j+1, caixasHistoricoInfo->funcionario->nome, caixasHistoricoInfo->funcionario->id, caixasHistoricoInfo->dataTransacao.dia, caixasHistoricoInfo->dataTransacao.mes, caixasHistoricoInfo->dataTransacao.ano, tempoCaixa, tempoAtraso);

                    Elemento *produtos = caixasHistoricoInfo->listaProdutos->head;
                    while (produtos){
                        ProdutoStruct *produtoInfo = (ProdutoStruct *)produtos->Info;
                        formatTime(produtoInfo->tempoCaixa, tempoCaixaProduto);
                        formatTime(produtoInfo->tempoCompra, tempoCompraProduto);
                        fprintf(arquivo, "%d %s %dX %.2f€ %s %s,", produtoInfo->id, produtoInfo->nome, produtoInfo->quantidadeProdutosRepetidos, produtoInfo->preco, tempoCompraProduto, tempoCaixaProduto);
                        produtos = produtos->next;
                    }

                    fprintf(arquivo,"\";%.2f€;%.2f€;%.2f€\n", caixasHistoricoInfo->precoTotal, caixasHistoricoInfo->valorProdutoOferecido, caixasHistoricoInfo->movimentoCartaoCliente);
                    caixasHistorico = caixasHistorico->next;
                }  
            }
        clientesHistorico = clientesHistorico->next;
        }
    }
    pthread_mutex_unlock(&HistoricoDados.HistoricoTransacoesLock);
    fclose(arquivo);
    printf("Dados exportados com sucesso para o arquivo %s.\n", nomeArquivo);
}

void exportHistoricoDadosEstatisticosParaTXT(const char* diretorio){
    char nomeArquivo[100];
    sprintf(nomeArquivo, "%s/HistoricoDadosEstatisticos.txt", diretorio);
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return;
    }
    for (int i = 0; i < 24; i++){
        for (int j = 0; j < 6; j++){
            for(int l = 0; l < numeroMaximoCaixasPossivel; l++){
                char hora[6], tempoEspera[9];
                sprintf(hora, "%d:%d", i+1, j+1);
                formatTime(HistoricoDados.dadosIntantaneosdiarios[i][j].tempoEspera_numeroClienteFila_CadaCaixa[l][0], tempoEspera);
                fprintf(arquivo, "Hora: %s ID Caixa: %d Tempo de espera: %s Número de clientes na fila: %d Número de caixas abertas: %d Número de clientes no supermercado: %d\n", hora, l+1, tempoEspera, HistoricoDados.dadosIntantaneosdiarios[i][j].tempoEspera_numeroClienteFila_CadaCaixa[l][1], HistoricoDados.dadosIntantaneosdiarios[i][j].numerosCaixasAbertas, HistoricoDados.dadosIntantaneosdiarios[i][j].numerosCaixasAbertas);
            }
        }
    }
    fclose(arquivo);
    printf("Dados exportados com sucesso para o arquivo %s.\n", nomeArquivo);
}

void exportHistoricoDadosEstatisticosParaCSV(const char* diretorio){
    char nomeArquivo[100];
    sprintf(nomeArquivo, "%s/HistoricoDadosEstatisticos.csv", diretorio);
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return;
    }
    fprintf(arquivo, "Horas;Minutos;ID Caixa;Tempo Espera;Numero de clientes na fila;Numero de caixas abertas;Numero de clientes no supermercado\n");
    for (int i = 0; i < 24; i++){
        for (int j = 0; j < 6; j++){
            for(int l = 0; l < numeroMaximoCaixasPossivel; l++){
                fprintf(arquivo, "%d;%d;%d;%d;%d;%d;%d\n", i+1, j+1, l+1, HistoricoDados.dadosIntantaneosdiarios[i][j].tempoEspera_numeroClienteFila_CadaCaixa[l][0], HistoricoDados.dadosIntantaneosdiarios[i][j].tempoEspera_numeroClienteFila_CadaCaixa[l][1], HistoricoDados.dadosIntantaneosdiarios[i][j].numerosCaixasAbertas, HistoricoDados.dadosIntantaneosdiarios[i][j].numeroClienteSupermercado);
            }
        }
    }
    fclose(arquivo);
    printf("Dados exportados com sucesso para o arquivo %s.\n", nomeArquivo);
}
