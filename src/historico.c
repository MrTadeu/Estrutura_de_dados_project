#include "../includes/TipoDados.h"

void initHistorico(){
    HistoricoDados.tamanhoVetorHash = 30;
    HistoricoDados.HistoricoTransacoes = malloc(HistoricoDados.tamanhoVetorHash * sizeof(Lista*));
    for (int i = 0; i < HistoricoDados.tamanhoVetorHash; i++)
        HistoricoDados.HistoricoTransacoes[i] = criarLista();
}

void initDadosEstatisticos()
{
    HistoricoDados.dadosEstatisticos = (DadosEstatisticosStruct *)malloc(sizeof(DadosEstatisticosStruct));

    for (int i = 0; i < 24; i++){
        for (int j = 0; j < 6; j++){
            HistoricoDados.dadosEstatisticos->dadosIntantaneosdiarios[i][j].numeroClienteFilaCadaCaixa = (int *)calloc(Opcoes.numCaixasTotal, sizeof(int));
            HistoricoDados.dadosEstatisticos->dadosIntantaneosdiarios[i][j].tempoEsperaCadaCaixa = (int *)calloc(Opcoes.numCaixasTotal, sizeof(int));
            HistoricoDados.dadosEstatisticos->dadosIntantaneosdiarios[i][j].numeroClienteSupermercado = 0;
            HistoricoDados.dadosEstatisticos->dadosIntantaneosdiarios[i][j].numerosCaixasAbertas = 0;

            HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioClienteFilaCadaCaixa = (float *)calloc(Opcoes.numCaixasTotal, sizeof(float));
            HistoricoDados.dadosEstatisticos->mediaDiaria.tempoMedioEsperaCadaCaixa = (float *)calloc(Opcoes.numCaixasTotal, sizeof(float));
            HistoricoDados.dadosEstatisticos->mediaDiaria.tempoMedioEsperaTodasCaixas = 0;
            HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioClienteFilaTodasCaixas = 0;
            HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioCaixasAbertas = 0;
            HistoricoDados.dadosEstatisticos->mediaDiaria.numeroMedioClienteSupermercado = 0;
        }
    }
}

int hashFunction(char *nome){
    if (!nome)
    {
        printf("\n\t[red]Error![/red] Given name is NULL\n");
        return -1;
    }
    int sum = 0;
    int p = 31; // Um número primo para gerar o hash

    for (int i = 0; nome[i] != '\0'; i++)
    {
        sum = (sum * p) + nome[i];
    }

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
    // infoHistorico.hora
    return infoHistorico;
}

void AddHistorico_Hash(CaixaStruct *caixa, float movimentoSaldoCartao, float valorProdutoOferecido)
{
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

                    printc("\n[blue]Nome cliente:[/blue] %s\t[blue]ID cliente:[/blue] %d\n[blue]ID caixa:[/blue] %d\t[blue]Nome funcionário:[/blue] %d\t[blue]ID funcionário:[/blue] %d\n[blue]Data de transação:[/blue] %d/%d/%d\t[blue]Hora: %d:%d:%d[/blue]\n[blue]Tempo de espera na fila:[/blue] %s\t", clientesHistoricoInfo->nome, clientesHistoricoInfo->id, j, caixasHistoricoInfo->funcionario->nome, caixasHistoricoInfo->funcionario->id, caixasHistoricoInfo->dataTransacao.dia, caixasHistoricoInfo->dataTransacao.mes, caixasHistoricoInfo->dataTransacao.ano, caixasHistoricoInfo->dataTransacao.hora, caixasHistoricoInfo->dataTransacao.minuto, caixasHistoricoInfo->dataTransacao.segundo, horas);

                    printc("[blue]Tempo de atraso:[/blue] ");
                    if (caixasHistoricoInfo->tempoAtraso < 0)
                        printc("[green]Adiantou-se:[/green] %.2f segundos\n", (float)caixasHistoricoInfo->tempoAtraso / 1000.0);
                    else if (caixasHistoricoInfo->tempoAtraso > 0)
                        printc("[red]Atrasou-se:[/red] %.2f segundos\n", (float)caixasHistoricoInfo->tempoAtraso / 1000.0);

                    Elemento *produtos = caixasHistoricoInfo->listaProdutos->head;
                    while (produtos)
                    {
                        ProdutoStruct *produtoInfo = (ProdutoStruct *)produtos->Info;
                        printc("\n\t[blue]ID produto:[/blue] %d [blue]Nome produto:[/blue] %s, [blue]QT:[/blue] %dX, [blue]Preco:[/blue] %.2f [blue]TCompra:[/blue] %d [blue]TCaixa:[/blue] %d\n", produtoInfo->id, produtoInfo->nome, produtoInfo->quantidadeProdutosRepetidos, produtoInfo->preco, produtoInfo->tempoCompra, produtoInfo->tempoCaixa);
                        produtos = produtos->next;
                    }

                    printc("[blue]Preço total:[/blue] %.2f\n", caixasHistoricoInfo->precoTotal);

                    if (caixasHistoricoInfo->valorProdutoOferecido > 0)
                    {
                        printc("[yellow]Produto oferecido![/yellow] [blue]Preço:[/blue] %.2f", caixasHistoricoInfo->valorProdutoOferecido);
                    }
                    printc("[blue]Saldo cartão cliente[/blue] ");
                    if (caixasHistoricoInfo->movimentoCartaoCliente < 0)
                    {
                        printc("[blue]O cliente usou[/blue] %.2f euros", fabs(caixasHistoricoInfo->movimentoCartaoCliente));
                    }
                    else
                        printc("[blue]O cliente angariou[/blue] %.2f euros", caixasHistoricoInfo->movimentoCartaoCliente);

                    caixasHistorico = caixasHistorico->next;
                }
            }

            clientesHistorico = clientesHistorico->next;
        }
    }

    pthread_mutex_unlock(&HistoricoDados.HistoricoTransacoesLock);
}

void pesquisarClienteNoHistorico(ClienteStruct *cliente){
    /* for (int i = 0; i < HistoricoDados.tamanhoVetorHash; i++){ */
        Elemento* pessoasHistorico = HistoricoDados.HistoricoTransacoes[hashFunction(cliente->nome)]->head;
        while (pessoasHistorico != NULL){
            HistoricoSubStructCliente *ClienteInfo = (HistoricoSubStructCliente *) pessoasHistorico->Info;
            if ((cliente->id == ClienteInfo->id) && strcasecmp(cliente->nome, ClienteInfo->nome)){
                printf("[blue]Cliente:[/blue] %s [blue]id:[/blue] %d \n", ClienteInfo->nome, ((HistoricoSubStructCliente *)pessoasHistorico)->id);
                for (int j = 0; j < Opcoes.numCaixasTotal; j++){
                    HistoricoSubStructCaixa *caixaInfo = ((HistoricoSubStructCaixa *)((HistoricoSubStructCliente *) pessoasHistorico->Info)->caixas[j]->head->Info);

                    printf("\t[blue]Caixa:[/blue] %d [blue]Funcionario:[/blue] %s [blue]id:[/blue] %d\n", j+1, caixaInfo->funcionario->nome, caixaInfo->funcionario->id);
                    printf("\t[blue]Data:[/blue] %d/%d/%d [blue]Hora:[/blue] %d:%d:%d\n", caixaInfo->dataTransacao.dia, caixaInfo->dataTransacao.mes, caixaInfo->dataTransacao.ano, caixaInfo->dataTransacao.hora, caixaInfo->dataTransacao.minuto, caixaInfo->dataTransacao.segundo);
                    
                    printf("\t[blue]Tempo de espera na fila:[/blue] %d\n", caixaInfo->tempoEstimadoCaixa);

                    printc("\t[blue]Tempo de atraso:[/blue] ");
                    if (caixaInfo->tempoAtraso < 0)
                        printc("\t[green]Adiantou-se:[/green] %.2f segundos\n", (float)caixaInfo->tempoAtraso / 1000.0);
                    else if (caixaInfo->tempoAtraso > 0)
                        printc("\t[red]Atrasou-se:[/red] %.2f segundos\n", (float)caixaInfo->tempoAtraso / 1000.0);

                    printf("\t[blue]Preço total:[/blue] %.2f\n", caixaInfo->precoTotal);

                    printf("\t[blue]Saldo cartão cliente:[/blue] %.2f\n", caixaInfo->movimentoCartaoCliente);
                    
                    printf("\t[blue]Produtos:[/blue]\n");
                    Elemento *produtos = caixaInfo->listaProdutos->head;
                    while (produtos){
                        ProdutoStruct *produtoInfo = (ProdutoStruct *)produtos->Info;
                        printc("\n\t\t[blue]ID produto:[/blue] %d [blue]Nome produto:[/blue] %s, [blue]QT:[/blue] %dX, [blue]Preco:[/blue] %.2f [blue]TCompra:[/blue] %d [blue]TCaixa:[/blue] %d\n", produtoInfo->id, produtoInfo->nome, produtoInfo->quantidadeProdutosRepetidos, produtoInfo->preco, produtoInfo->tempoCompra, produtoInfo->tempoCaixa);
                        produtos = produtos->next;
                    }
                }
                return;
            }
            pessoasHistorico = pessoasHistorico->next;
        } 
    /* } */
    printc("[red]Cliente não encontrado![/red]\n");
}

void pesquisarCaixaNoHistorico(CaixaStruct *caixa){
    printc("[yellow]Caixa:[/yellow] %d\n\n", caixa->id);
    for (int i = 0; i < HistoricoDados.tamanhoVetorHash; i++){
        Elemento* pessoasHistorico = HistoricoDados.HistoricoTransacoes[i]->head;

        while (pessoasHistorico){
            HistoricoSubStructCliente *ClienteInfo = (HistoricoSubStructCliente *) pessoasHistorico->Info;
            HistoricoSubStructCaixa *caixaInfo = ((HistoricoSubStructCaixa *)((HistoricoSubStructCliente *) pessoasHistorico->Info)->caixas[caixa->id - 1]->head->Info);

            printf("\t[blue]Funcionario:[/blue] %s [blue]id:[/blue] %d\n", caixaInfo->funcionario->nome, caixaInfo->funcionario->id);
            printf("\t[blue]Cliente:[/blue] %s [blue]id:[/blue] %d \n", ClienteInfo->nome, ((HistoricoSubStructCliente *)pessoasHistorico->Info)->id);
            printf("\t\t[blue]Data:[/blue] %d/%d/%d [blue]Hora:[/blue] %d:%d:%d\n", caixaInfo->dataTransacao.dia, caixaInfo->dataTransacao.mes, caixaInfo->dataTransacao.ano, caixaInfo->dataTransacao.hora, caixaInfo->dataTransacao.minuto, caixaInfo->dataTransacao.segundo);
            

            pessoasHistorico = pessoasHistorico->next;
        }
    }
}

