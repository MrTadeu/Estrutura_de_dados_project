#include "../includes/TipoDados.h"

void initHistorico(){
    HistoricoDados.tamanhoVetorHash = 30;
    HistoricoDados.HistoricoTransacoes = malloc(HistoricoDados.tamanhoVetorHash * sizeof(Lista*));
    for (int i = 0; i < HistoricoDados.tamanhoVetorHash; i++)
        HistoricoDados.HistoricoTransacoes[i] = criarLista();
}

void initDadosEstatisticos(){
    HistoricoDados.dadosEstatisticos = (DadosEstatisticosStruct *)malloc(sizeof(DadosEstatisticosStruct));
    HistoricoDados.dadosEstatisticos->dadosIntantaneosdiarios = (DadosInstantaneoStruct **) malloc(sizeof(DadosInstantaneoStruct*)*24);
    
    //DADOS INSTANTANEOS
    for (int i = 0; i < 24; i++){
            HistoricoDados.dadosEstatisticos->dadosIntantaneosdiarios[i] = (DadosInstantaneoStruct*) malloc(sizeof(DadosInstantaneoStruct)*6);
        for (int j = 0; j < 6; j++){
            HistoricoDados.dadosEstatisticos->dadosIntantaneosdiarios[i][j].tempoEspera_numeroClienteFila_CadaCaixa = (int **)malloc(sizeof(int*)*Opcoes.numCaixasTotal);
            for (int l = 0; l < Opcoes.numCaixasTotal; l++){
                HistoricoDados.dadosEstatisticos->dadosIntantaneosdiarios[i][j].tempoEspera_numeroClienteFila_CadaCaixa[l] = (int*)calloc(2, sizeof(int));
                // Coluna 0: tempoEspera | Coluna 1: numeroClientesFila
            }
            HistoricoDados.dadosEstatisticos->dadosIntantaneosdiarios[i][j].numerosCaixasAbertas = 0;
            HistoricoDados.dadosEstatisticos->dadosIntantaneosdiarios[i][j].numeroClienteSupermercado = 0;
        }      
    }

    //INTS
        HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario = (int **)malloc(sizeof(int*)*n_funcionarios);
        for (int i = 0; i < n_funcionarios; i++)
            HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i] = (int *)calloc(3, sizeof(int));
        //coluna 0: ids funcionarios | coluna 1: n pessoas atendidas | coluna 2: n produtos vendidos


        HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa = (int**) malloc(sizeof(int*)*Opcoes.numCaixasTotal);
        for (int i = 0; i < Opcoes.numCaixasTotal; i++)
            HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i] = (int *)calloc(2, sizeof(int));
        //coluna 0: n pessoas atendidas por cada caixa | coluna 1: n produtos vendidos por cada caixa

        HistoricoDados.dadosEstatisticos->mediaDiaria.numeroProdutosOferecidos = 0;

    //CHARS
        HistoricoDados.dadosEstatisticos->mediaDiaria.nomeFuncionarioAtendeuMaisPessoas = (char*) malloc(sizeof(char)*11);
        strcpy(HistoricoDados.dadosEstatisticos->mediaDiaria.nomeFuncionarioAtendeuMaisPessoas, "Calculando");
        HistoricoDados.dadosEstatisticos->mediaDiaria.nomeFuncionarioAtendeuMenosPessoas = (char*) malloc(sizeof(char)*11);
        strcpy(HistoricoDados.dadosEstatisticos->mediaDiaria.nomeFuncionarioAtendeuMenosPessoas, "Calculando");
        HistoricoDados.dadosEstatisticos->mediaDiaria.nomeFuncionarioVendeuMaisProdutos = (char*) malloc(sizeof(char)*11);
        strcpy(HistoricoDados.dadosEstatisticos->mediaDiaria.nomeFuncionarioVendeuMaisProdutos, "Calculando");
        HistoricoDados.dadosEstatisticos->mediaDiaria.nomeFuncionarioVendeuMenosProdutos = (char*) malloc(sizeof(char)*11);
        strcpy(HistoricoDados.dadosEstatisticos->mediaDiaria.nomeFuncionarioVendeuMenosProdutos, "Calculando");
    


    //FLOATS    
        HistoricoDados.dadosEstatisticos->mediaDiaria.tempoMedioEspera_CadaCaixa_CadaHora = (float **)malloc(sizeof(float*)*24);
        HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioClienteFila_CadaCaixa_CadaHora = (float **)malloc(sizeof(float*)*24);
        for (int i = 0; i < 24; i++){
            HistoricoDados.dadosEstatisticos->mediaDiaria.tempoMedioEspera_CadaCaixa_CadaHora[i] = (float*)calloc(Opcoes.numCaixasTotal, sizeof(float));
            HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioClienteFila_CadaCaixa_CadaHora[i] = (float*)calloc(Opcoes.numCaixasTotal, sizeof(float));
        }
        HistoricoDados.dadosEstatisticos->mediaDiaria.tempoMedioEsperaTotal_CadaHora = (float*)calloc(24, sizeof(float));
        HistoricoDados.dadosEstatisticos->mediaDiaria.tempoMedioEspera_CadaCaixa = (float*)calloc(Opcoes.numCaixasTotal, sizeof(float));
        HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioClienteFila_CadaHora = (float*)calloc(24, sizeof(float));
        HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioClienteFila_CadaCaixa = (float*)calloc(Opcoes.numCaixasTotal, sizeof(float));
        HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioCaixasAbertas_CadaHora = (float*)calloc(24, sizeof(float));
        HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioClienteSupermercado_CadaHora = (float*)calloc(24, sizeof(float));

        HistoricoDados.dadosEstatisticos->mediaDiaria.tempoMedioEspera_Dia = 0.0;
        HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioClienteFila_Dia = 0.0;
        HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioCaixasAbertas_dia = 0.0;
        HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioClienteSupermercado_Dia = 0.0;
}


void destruirRecolhasHistoricos(){
    // DADOS INSTANTANEOS
        for (int i = 0; i < 24; i++) {
            for (int j = 0; j < 6; j++) {
                for (int l = 0; l < Opcoes.numCaixasTotal; l++) {
                    free(HistoricoDados.dadosEstatisticos->dadosIntantaneosdiarios[i][j].tempoEspera_numeroClienteFila_CadaCaixa[l]);
                }
                free(HistoricoDados.dadosEstatisticos->dadosIntantaneosdiarios[i][j].tempoEspera_numeroClienteFila_CadaCaixa);
            }
            free(HistoricoDados.dadosEstatisticos->dadosIntantaneosdiarios[i]);
        }
        free(HistoricoDados.dadosEstatisticos->dadosIntantaneosdiarios);

    // INTS
        for (int i = 0; i < n_funcionarios; i++) {
            free(HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i]);
        }
        free(HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario);

        for (int i = 0; i < Opcoes.numCaixasTotal; i++) {
            free(HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i]);
        }
        free(HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa);

    // CHARS
        free(HistoricoDados.dadosEstatisticos->mediaDiaria.nomeFuncionarioAtendeuMaisPessoas);
        free(HistoricoDados.dadosEstatisticos->mediaDiaria.nomeFuncionarioAtendeuMenosPessoas);
        free(HistoricoDados.dadosEstatisticos->mediaDiaria.nomeFuncionarioVendeuMaisProdutos);
        free(HistoricoDados.dadosEstatisticos->mediaDiaria.nomeFuncionarioVendeuMenosProdutos);

    // FLOATS
        for (int i = 0; i < 24; i++) {
            free(HistoricoDados.dadosEstatisticos->mediaDiaria.tempoMedioEspera_CadaCaixa_CadaHora[i]);
            free(HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioClienteFila_CadaCaixa_CadaHora[i]);
        }
        free(HistoricoDados.dadosEstatisticos->mediaDiaria.tempoMedioEspera_CadaCaixa_CadaHora);
        free(HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioClienteFila_CadaCaixa_CadaHora);

        free(HistoricoDados.dadosEstatisticos->mediaDiaria.tempoMedioEsperaTotal_CadaHora);
        free(HistoricoDados.dadosEstatisticos->mediaDiaria.tempoMedioEspera_CadaCaixa);
        free(HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioClienteFila_CadaHora);
        free(HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioClienteFila_CadaCaixa);
        free(HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioCaixasAbertas_CadaHora);
        free(HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioClienteSupermercado_CadaHora);

    //Struct
    free(HistoricoDados.dadosEstatisticos);
}

void calculosRecolhas(){
    int idFunc_maisAtendimentos = HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[0][1],
    idFunc_menosAtendimentos = HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[0][1],
    idFunc_maisProdutos = HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[0][2],
    idFunc_menosProdutos = HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[0][2];
    for (int i = 0; i < n_funcionarios; i++){
        if(idFunc_maisAtendimentos < HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][1])
            idFunc_maisAtendimentos = HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][1];
        if(idFunc_menosAtendimentos > HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][1])
            idFunc_menosAtendimentos = HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][1];
        if(idFunc_maisProdutos < HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][2])
            idFunc_maisProdutos = HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][2];
        if(idFunc_menosProdutos > HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][2])
            idFunc_menosProdutos = HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[i][2];
    }

    int idCaixa_maisAtendimentos = HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[0][0], 
    idCaixa_menosAtendimentos = HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[0][0], 
    idCaixa_maisProdutos = HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[0][1],
    idCaixa_menosProdutos = HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[0][1];

    for (int i = 0; i < Opcoes.numCaixasTotal; i++){
        if(idCaixa_maisAtendimentos < HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i][1])
            idCaixa_maisAtendimentos = HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i][1];
        if(idCaixa_menosAtendimentos > HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i][1])
            idCaixa_menosAtendimentos = HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i][1];
        if(idCaixa_maisProdutos < HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i][2])
            idCaixa_maisProdutos = HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i][2];
        if(idCaixa_menosProdutos > HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i][2])
            idCaixa_menosProdutos = HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[i][2];
    }
    
    
    
}


int hashFunction(char *nome){
    if (!nome){
        printf("\n\t[red]Error![/red] Given name is NULL\n");
        return -1;
    }
    int sum = 0, p = 31;// Um número primo para gerar o hash

    for (int i = 0; nome[i] != '\0'; i++)
        sum = (sum * p) + nome[i];

    // Ajusta o tamanho do hash para o tamanho do vetor
    sum = (sum % HistoricoDados.tamanhoVetorHash + HistoricoDados.tamanhoVetorHash) % HistoricoDados.tamanhoVetorHash;
    return sum;
}

void *criarSubStructClienteHistorico(ClienteStruct *cliente)
{
    HistoricoSubStructCliente *elementoCliente = (HistoricoSubStructCliente *)malloc(sizeof(HistoricoSubStructCliente));
    elementoCliente->nome = (char *)malloc(strlen(cliente->nome) + 1);
    strcpy(elementoCliente->nome, cliente->nome);
    elementoCliente->id = cliente->id;
    elementoCliente->caixas = (Lista **)malloc(sizeof(Lista *) * Opcoes.numCaixasTotal);
    for (int i = 0; i < Opcoes.numCaixasTotal; i++)
        elementoCliente->caixas[i] = criarLista();
    return elementoCliente;
}

void *criarInfoHistorico(CaixaStruct *caixa, float movimentoSaldoCartao, float valorProdutoOferecido)
{
    ClienteStruct *pessoa = (ClienteStruct *)caixa->listaPessoas->head->Info;
    HistoricoSubStructCaixa *infoHistorico = (HistoricoSubStructCaixa *)malloc(sizeof(HistoricoSubStructCaixa));
    infoHistorico->funcionario = caixa->funcionario;
    infoHistorico->listaProdutos = pessoa->listaProdutos;
    infoHistorico->tempoEstimadoCaixa = pessoa->tempoEstimadoCaixa;
    infoHistorico->tempoAtraso = pessoa->tempoAtraso;
    infoHistorico->movimentoCartaoCliente = movimentoSaldoCartao;
    infoHistorico->precoTotal = pessoa->precoTotalProdutos;
    infoHistorico->valorProdutoOferecido = valorProdutoOferecido;
    infoHistorico->dataTransacao = formatTimeStruct(getCurrentTimeMillisecounds());
    return infoHistorico;
}

void AddHistorico_Hash(CaixaStruct *caixa, float movimentoSaldoCartao, float valorProdutoOferecido){
    if (!caixa)
    {
        printf("\n\t[red]Error![/red] Given caixa is NULL\n");
        return;
    }
    if (!caixa->listaPessoas->head->Info)
    {
        printf("\n\t[red]Error![/red] Given cliente is NULL\n");
        return;
    }
    printf("\n\n\n\t\t\t\tola1\n\n\n\n\n\n");

    ClienteStruct *pessoaAtendida = (ClienteStruct *)malloc(sizeof(ClienteStruct));
    memcpy(pessoaAtendida, caixa->listaPessoas->head->Info, sizeof(ClienteStruct));
    int hashIndex = hashFunction(pessoaAtendida->nome);

    FuncionarioStruct *funcionario = (FuncionarioStruct *)malloc(sizeof(FuncionarioStruct));
    memcpy(funcionario, caixa->funcionario, sizeof(FuncionarioStruct));

    pthread_mutex_lock(&HistoricoDados.HistoricoTransacoesLock);
    Elemento *Aux = HistoricoDados.HistoricoTransacoes[hashIndex]->head;
    while (Aux){
        HistoricoSubStructCliente *guardado = (HistoricoSubStructCliente *)Aux->Info;
        if (pessoaAtendida->id == guardado->id)
        {   printc("\n\n\n\t\t\t\t[green]ola5 ADD INFO HISTORICO[/green]\n\n\n\n\n\n");
            AddElementoInicio(guardado->caixas[caixa->id - 1], criarElemento(criarInfoHistorico(caixa, movimentoSaldoCartao, valorProdutoOferecido)));
            pthread_mutex_unlock(&HistoricoDados.HistoricoTransacoesLock);
            return;
        }
        Aux = Aux->next;
    }
    AddElementoInicio(HistoricoDados.HistoricoTransacoes[hashIndex], criarElemento(criarSubStructClienteHistorico(pessoaAtendida)));
    pthread_mutex_unlock(&HistoricoDados.HistoricoTransacoesLock);
    printc("\n\n\n\t\t\t\t[green]RECURSIVEEEEEEEEEEEEE[/green]\n\n\n\n\n\n");
    AddHistorico_Hash(caixa, movimentoSaldoCartao, valorProdutoOferecido);
}

//* index Hash->|0|1|2|3|...          __HistoricoSubStructCliente
//*              |        ___________/      /
//*              V       V                 /
//*           |Nome, Id|  --> |1|2|3|4|5|... <--id caixas
//*                             |
//*                          |Info|  <--- HistoricoSubStructCaixa

void mostrarHistorico(){
    pthread_mutex_lock(&HistoricoDados.HistoricoTransacoesLock);
    for (int i = 0; i < HistoricoDados.tamanhoVetorHash; i++){
        Elemento *clientesHistorico = HistoricoDados.HistoricoTransacoes[i]->head;
        while (clientesHistorico){
            HistoricoSubStructCliente *clientesHistoricoInfo = (HistoricoSubStructCliente *)clientesHistorico->Info;
            for (int j = 0; j < Opcoes.numCaixasTotal; j++){
                Elemento *caixasHistorico = clientesHistoricoInfo->caixas[j]->head;
                while (caixasHistorico){   
                    char horas[9];
                    HistoricoSubStructCaixa *caixasHistoricoInfo = (HistoricoSubStructCaixa *)caixasHistorico->Info;
                    formatTime(caixasHistoricoInfo->tempoEstimadoCaixa, horas);

                    printc("\n[blue]Nome cliente:[/blue] %s\t[blue]ID cliente:[/blue] %d\n[blue]ID caixa:[/blue] %d\t[blue]Nome funcionário:[/blue] %s\t[blue]ID funcionário:[/blue] %d\n[blue]Data de transação:[/blue] %d/%d/%d\t[blue]Hora:[/blue] %d:%d:%d\n[blue]Tempo de espera na fila:[/blue] %s\t", clientesHistoricoInfo->nome, clientesHistoricoInfo->id, j+1, caixasHistoricoInfo->funcionario->nome, caixasHistoricoInfo->funcionario->id, caixasHistoricoInfo->dataTransacao.dia, caixasHistoricoInfo->dataTransacao.mes, caixasHistoricoInfo->dataTransacao.ano, caixasHistoricoInfo->dataTransacao.hora, caixasHistoricoInfo->dataTransacao.minuto, caixasHistoricoInfo->dataTransacao.segundo, horas);

                    printc("[blue]Tempo de atraso:[/blue] ");
                    if (caixasHistoricoInfo->tempoAtraso < 0)
                        printc("[green]Adiantou-se:[/green] %.2f segundos\n", fabs((float)caixasHistoricoInfo->tempoAtraso / 1000.0));
                    else if (caixasHistoricoInfo->tempoAtraso > 0)
                        printc("[red]Atrasou-se:[/red] %.2f segundos\n", (float)caixasHistoricoInfo->tempoAtraso / 1000.0);

                    Elemento *produtos = caixasHistoricoInfo->listaProdutos->head;
                    while (produtos)
                    {
                        ProdutoStruct *produtoInfo = (ProdutoStruct *)produtos->Info;
                        printc("\n\t\t[blue]ID produto:[/blue] %d [blue]Nome produto:[/blue] %s, [blue]QT:[/blue] %dX, [blue]Preco:[/blue] %.2f [blue]TCompra:[/blue] %d [blue]TCaixa:[/blue] %d\n", produtoInfo->id, produtoInfo->nome, produtoInfo->quantidadeProdutosRepetidos, produtoInfo->preco, produtoInfo->tempoCompra, produtoInfo->tempoCaixa);
                        produtos = produtos->next;
                    }

                    printc("\t[blue]Preço total:[/blue] %.2f\n", caixasHistoricoInfo->precoTotal);

                    if (caixasHistoricoInfo->valorProdutoOferecido > 0)
                    {
                        printc("\t[yellow]Produto oferecido![/yellow] [blue]Preço:[/blue] %.2f", caixasHistoricoInfo->valorProdutoOferecido);
                    }
                    printc("\t[blue]Saldo cartão cliente:[/blue]\n");
                    if (caixasHistoricoInfo->movimentoCartaoCliente < 0)
                    {
                        printc("\t\t[blue]O cliente usou[/blue] %.2f euros", fabs(caixasHistoricoInfo->movimentoCartaoCliente));
                    }
                    else
                        printc("\t\t[blue]O cliente angariou[/blue] %.2f euros", caixasHistoricoInfo->movimentoCartaoCliente);

                    caixasHistorico = caixasHistorico->next;
                }
            }

            clientesHistorico = clientesHistorico->next;
        }
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    pthread_mutex_unlock(&HistoricoDados.HistoricoTransacoesLock);
}

void pesquisarClienteNoHistorico(){
    /* for (int i = 0; i < HistoricoDados.tamanhoVetorHash; i++){ */
    int id, pos = -1, flag = 0;
    scanfs("%d", &id, "Qual o id de Cliente que pretende pesquisar? ", "Tem de inserir um numero inteiro!");
    pos =  encontrarIdCliente(id);
    if (pos == -1) return;
    char *nome = malloc(sizeof(char) * strlen(Clientes[pos]->nome));
    strcpy(nome, Clientes[pos]->nome);
    printf("Nome: %s\n", nome);
    Elemento* pessoasHistorico = HistoricoDados.HistoricoTransacoes[hashFunction(nome)]->head;
    while (pessoasHistorico != NULL){
        HistoricoSubStructCliente *ClienteInfo = (HistoricoSubStructCliente *) pessoasHistorico->Info;
        if ((id == ClienteInfo->id) /* && strcasecmp(nome, ClienteInfo->nome) */){
            flag = 1;
            printc("[blue]Cliente:[/blue] %s [blue]id:[/blue] %d \n", ClienteInfo->nome, ClienteInfo->id);
            for (int j = 0; j < Opcoes.numCaixasTotal; j++){
                Elemento *caixasHistorico = ClienteInfo->caixas[j]->head;
                while (caixasHistorico){
                    HistoricoSubStructCaixa *caixaInfo = ((HistoricoSubStructCaixa *)((HistoricoSubStructCliente *) pessoasHistorico->Info)->caixas[j]->head->Info);

                    printc("\t[blue]Caixa:[/blue] %d [blue]Funcionario:[/blue] %s [blue]id:[/blue] %d\n", j+1, caixaInfo->funcionario->nome, caixaInfo->funcionario->id);
                    printc("\t[blue]Data:[/blue] %d/%d/%d [blue]Hora:[/blue] %d:%d:%d\n", caixaInfo->dataTransacao.dia, caixaInfo->dataTransacao.mes, caixaInfo->dataTransacao.ano, caixaInfo->dataTransacao.hora, caixaInfo->dataTransacao.minuto, caixaInfo->dataTransacao.segundo);
                    
                    printc("\t[blue]Tempo de espera na fila:[/blue] %d\n", caixaInfo->tempoEstimadoCaixa);

                    printc("\t[blue]Tempo de atraso:[/blue] ");
                    if (caixaInfo->tempoAtraso < 0)
                        printc("\t[green]Adiantou-se:[/green] %.2f segundos\n", fabs((float)caixaInfo->tempoAtraso / 1000.0));
                    else if (caixaInfo->tempoAtraso > 0)
                        printc("\t[red]Atrasou-se:[/red] %.2f segundos\n", (float)caixaInfo->tempoAtraso / 1000.0);

                    printc("\t[blue]Preço total:[/blue] %.2f\n", caixaInfo->precoTotal);

                    printc("\t[blue]Saldo cartão cliente:[/blue] %.2f\n", caixaInfo->movimentoCartaoCliente);
                    
                    printc("\t[blue]Produtos:[/blue]\n");
                    Elemento *produtos = caixaInfo->listaProdutos->head;
                    while (produtos){
                        ProdutoStruct *produtoInfo = (ProdutoStruct *)produtos->Info;
                        printc("\n\t\t[blue]ID produto:[/blue] %d [blue]Nome produto:[/blue] %s, [blue]QT:[/blue] %dX, [blue]Preco:[/blue] %.2f [blue]TCompra:[/blue] %d [blue]TCaixa:[/blue] %d\n", produtoInfo->id, produtoInfo->nome, produtoInfo->quantidadeProdutosRepetidos, produtoInfo->preco, produtoInfo->tempoCompra, produtoInfo->tempoCaixa);
                        produtos = produtos->next;
                    }
                    caixasHistorico = caixasHistorico->next;
                }
            }
        }
        pessoasHistorico = pessoasHistorico->next;
    } 
    /* } */
    flag == 0 ? printc("[red]Cliente não encontrado![/red]\n") : (void)NULL;
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void pesquisarCaixaNoHistorico(){
    int id;
    scanfv("%d", &id, "Qual o id de caixa que pretende pesquisar? ", "Tem de inserir um numero inteiro!", validateRange, 1, Opcoes.numCaixasTotal);
    printc("[yellow]Caixa:[/yellow] %d\n\n", id);
    for (int i = 0; i < HistoricoDados.tamanhoVetorHash; i++){
        Elemento* pessoasHistorico = HistoricoDados.HistoricoTransacoes[i]->head;
        while (pessoasHistorico){
            HistoricoSubStructCliente *ClienteInfo = (HistoricoSubStructCliente *) pessoasHistorico->Info;
            if (ClienteInfo->caixas[id - 1]->head){
                HistoricoSubStructCaixa *caixaInfo = ((HistoricoSubStructCaixa *)((HistoricoSubStructCliente *) pessoasHistorico->Info)->caixas[id - 1]->head->Info);
                Elemento *caixasHistorico = ClienteInfo->caixas[id - 1]->head;
                while (caixasHistorico){
                    printc("\t[blue]Funcionario:[/blue] %s [blue]id:[/blue] %d\n", caixaInfo->funcionario->nome, caixaInfo->funcionario->id);
                    printc("\t[blue]Cliente:[/blue] %s [blue]id:[/blue] %d \n", ClienteInfo->nome, ((HistoricoSubStructCliente *)pessoasHistorico->Info)->id);
                    printc("\t\t[blue]Data:[/blue] %d/%d/%d [blue]Hora:[/blue] %d:%d:%d\n", caixaInfo->dataTransacao.dia, caixaInfo->dataTransacao.mes, caixaInfo->dataTransacao.ano, caixaInfo->dataTransacao.hora,    caixaInfo->dataTransacao.minuto, caixaInfo->dataTransacao.segundo);

                    printc("\t\t[blue]Tempo de espera na fila:[/blue] %d\n", caixaInfo->tempoEstimadoCaixa);
                    printc("\t[blue]Tempo de atraso:[/blue] ");
                    if (caixaInfo->tempoAtraso < 0)
                        printc("\t[green]Adiantou-se:[/green] %.2f segundos\n", fabs((float)caixaInfo->tempoAtraso / 1000.0));
                    else if (caixaInfo->tempoAtraso > 0)
                        printc("\t[red]Atrasou-se:[/red] %.2f segundos\n", (float)caixaInfo->tempoAtraso / 1000.0);

                    printc("\t[blue]Preço total:[/blue] %.2f\n", caixaInfo->precoTotal);

                printf("\t[blue]Saldo cartão cliente:[/blue] %.2f\n", caixaInfo->movimentoCartaoCliente);
                
                printf("\t[blue]Produtos:[/blue]\n");
                Elemento *produtos = caixaInfo->listaProdutos->head;
                while (produtos){
                    ProdutoStruct *produtoInfo = (ProdutoStruct *)produtos->Info;
                    printc("\n\t\t[blue]ID produto:[/blue] %d [blue]Nome produto:[/blue] %s, [blue]QT:[/blue] %dX, [blue]Preco:[/blue] %.2f [blue]TCompra:[/blue] %d [blue]TCaixa:[/blue] %d\n", produtoInfo->id, produtoInfo->nome, produtoInfo->quantidadeProdutosRepetidos, produtoInfo->preco, produtoInfo->tempoCompra, produtoInfo->tempoCaixa);
                    produtos = produtos->next;
                }
                caixasHistorico = caixasHistorico->next;
            }
            
            pessoasHistorico = pessoasHistorico->next;
        }
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}
}

void recolhaDadosEstatisticosHistoricoTransacoes(){
    pthread_mutex_lock(&HistoricoDados.HistoricoTransacoesLock);
    
    for (int i = 0; i < HistoricoDados.tamanhoVetorHash; i++){
        Elemento *clientesHistorico = HistoricoDados.HistoricoTransacoes[i]->head;
        while (clientesHistorico){
            
            HistoricoSubStructCliente *clientesHistoricoInfo = (HistoricoSubStructCliente *)clientesHistorico->Info;
            for (int j = 0; j < Opcoes.numCaixasTotal; j++){
                Elemento *caixasHistorico = clientesHistoricoInfo->caixas[j]->head;
                if(caixasHistorico)
                    HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[j][0]++; //!numAtendimentos recolhido
                while (caixasHistorico){
                    int flag = 1;
                    HistoricoSubStructCaixa *caixasHistoricoInfo = (HistoricoSubStructCaixa *)caixasHistorico->Info;
                    HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaCaixa[j][1] += caixasHistoricoInfo->listaProdutos->quantidadeElementos; //!numProdutos recolhido
                    if (caixasHistoricoInfo->valorProdutoOferecido > 0){
                        HistoricoDados.dadosEstatisticos->mediaDiaria.numeroProdutosOferecidos++; //!numeroProdutosOferecidos recolhido
                        HistoricoDados.dadosEstatisticos->mediaDiaria.valorTotalProdutosOferecidos += caixasHistoricoInfo->valorProdutoOferecido; //!valorProdutosOferecidos recolhido
                    }

                    for (int l = 0; l < n_funcionarios; l++){
                        if(HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[l][0] == 0)
                            HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[l][0] = caixasHistoricoInfo->funcionario->id;
                        if(HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[l][0] == caixasHistoricoInfo->funcionario->id){
                            HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[l][1] += flag; //!numAtendimentos recolhido
                            flag = 0;
                            HistoricoDados.dadosEstatisticos->mediaDiaria.numeroAtendimentos_numeroProdutos_CadaFuncionario[l][2] += caixasHistoricoInfo->listaProdutos->quantidadeElementos; //!numProdutos recolhido
                            break;
                        }
                    }
                    caixasHistorico = caixasHistorico->next;
                }
            clientesHistorico = clientesHistorico->next;
            }
        }
    }
    pthread_mutex_unlock(&HistoricoDados.HistoricoTransacoesLock);
}

/* void recolhaDadosEstatisticosHistoricoPeriodica(){
    // depois
} */


