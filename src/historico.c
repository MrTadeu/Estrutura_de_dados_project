#include "../includes/TipoDados.h"

void initHistorico(){
    HistoricoDados.tamanhoVetorHash = 30;
    for (int i = 0; i < HistoricoDados.tamanhoVetorHash; i++)
        HistoricoDados.HistoricoTransacoes[i] = criarLista();
}

void initDadosEstatisticos(){
    dadosEstatisticos = (DadosEstatisticosStruct*) malloc(sizeof(DadosEstatisticosStruct));

    for (int i = 0; i < 24; i++){
        for (int j = 0; j < 6; j++){
            dadosEstatisticos->dadosIntantaneosdiarios[i][j].numeroClienteFilaCadaCaixa = (int*) calloc(Opcoes.numCaixasTotal, sizeof(int));
            dadosEstatisticos->dadosIntantaneosdiarios[i][j].tempoEsperaCadaCaixa = (int*) calloc(Opcoes.numCaixasTotal, sizeof(int));
            dadosEstatisticos->dadosIntantaneosdiarios[i][j].numeroClienteSupermercado = 0;
            dadosEstatisticos->dadosIntantaneosdiarios[i][j].numerosCaixasAbertas = 0;

            dadosEstatisticos->mediaDiaria.numeroMedioClienteFilaCadaCaixa = (float*) calloc(Opcoes.numCaixasTotal, sizeof(float));
            dadosEstatisticos->mediaDiaria.tempoMedioEsperaCadaCaixa = (float*) calloc(Opcoes.numCaixasTotal, sizeof(float));
            dadosEstatisticos->mediaDiaria.tempoMedioEsperaTodasCaixas = 0;
            dadosEstatisticos->mediaDiaria.numeroMedioClienteFilaTodasCaixas = 0;
            dadosEstatisticos->mediaDiaria.numeroMedioCaixasAbertas = 0;
            dadosEstatisticos->mediaDiaria.numeroMedioClienteSupermercado = 0;
        }
    }
}

int hashFunction(char *nome){
    if(!nome){
        printf("\n\t[red]Error![/red] Given name is NULL\n");
        return -1;
    }
    int sum = 0;
    int p = 31;  // Um número primo para gerar o hash

    for (int i = 0; nome[i] != '\0'; i++) {
        sum = (sum * p) + nome[i];
    }

    // Ajusta o tamanho do hash para o tamanho do vetor
    sum = (sum % HistoricoDados.tamanhoVetorHash + HistoricoDados.tamanhoVetorHash) % HistoricoDados.tamanhoVetorHash;

    return sum;
}

void *criarSubStructClienteHistorico(ClienteStruct *cliente){
    HistoricoSubStructCliente *elementoCliente = (HistoricoSubStructCliente *) malloc(sizeof(HistoricoSubStructCliente));
    elementoCliente->nome = (char*) malloc(strlen(cliente->nome)+1);
    strcpy(elementoCliente->nome, cliente->nome);
    elementoCliente->id = cliente->id;
    elementoCliente->caixas = (Lista**) malloc(sizeof(Lista*)*Opcoes.numCaixasTotal);
    for (int i = 0; i < Opcoes.numCaixasTotal; i++)
        elementoCliente->caixas[i] = criarLista();
    return elementoCliente;
}

void *criarInfoHistorico(CaixaStruct *caixa, float movimentoSaldoCartao, float valorProdutoOferecido){
    ClienteStruct *pessoa = (ClienteStruct*) caixa->listaPessoas->head->Info;
    HistoricoSubStructInfo *infoHistorico = (HistoricoSubStructInfo*) malloc(sizeof(HistoricoSubStructInfo));
    infoHistorico->funcionario = caixa->funcionario;
    infoHistorico->listaProdutos = pessoa->listaProdutos;
    infoHistorico->tempoEstimadoCaixa = pessoa->tempoEstimadoCaixa;
    infoHistorico->tempoAtraso = pessoa->tempoAtraso;
    infoHistorico->movimentoCartaoCliente = movimentoSaldoCartao;
    infoHistorico->precoTotal = pessoa->precoTotalProdutos;
    infoHistorico->valorProdutoOferecido = valorProdutoOferecido;
    infoHistorico->dataTransacao = formatTimeStruct(getDataMilliseconds()); 
    // infoHistorico.hora
    return infoHistorico;
}



void AddHistorico_Hash(CaixaStruct *caixa, float movimentoSaldoCartao, float valorProdutoOferecido){
    if(!caixa){
        printf("\n\t[red]Error![/red] Given caixa is NULL\n");         
        return;                                                       
    } 
    if(!caixa->listaPessoas->head->Info){                                                
        printf("\n\t[red]Error![/red] Given cliente is NULL\n");        
        return;                                                         
    }

    ClienteStruct* pessoaAtendida = (ClienteStruct*) malloc(sizeof(ClienteStruct));
    pthread_mutex_lock(&ClientesLock);
        memcpy(pessoaAtendida, caixa->listaPessoas->head->Info, sizeof(ClienteStruct));
        int hashIndex = alfabetoIndex(pessoaAtendida->nome);      
    pthread_mutex_unlock(&ClientesLock);

    FuncionarioStruct* funcionario = (FuncionarioStruct*) malloc(sizeof(FuncionarioStruct));
    pthread_mutex_lock(&FuncionariosLock);
        memcpy(funcionario, caixa->funcionario, sizeof(FuncionarioStruct));
    pthread_mutex_unlock(&FuncionariosLock);


    pthread_mutex_lock(&HistoricoDados.HistoricoTransacoesLock);
    int flag = 0;
    Elemento *Aux = HistoricoDados.HistoricoTransacoes[hashIndex]->head;
    while(Aux){
        HistoricoSubStructCliente *guardado = (HistoricoSubStructCliente*) Aux->Info;
        if(pessoaAtendida->id == guardado->id){
            AddElementoInicio(guardado->caixas[caixa->id-1], criarElemento(criarInfoHistorico(caixa, movimentoSaldoCartao, valorProdutoOferecido)));
            flag = 1;
            pthread_mutex_unlock(&HistoricoDados.HistoricoTransacoesLock);
            return;
        }
        Aux = Aux->next;
    }
    AddElementoInicio(HistoricoDados.HistoricoTransacoes[hashIndex], criarElemento(criarSubStructClienteHistorico(pessoaAtendida)));
    pthread_mutex_unlock(&HistoricoDados.HistoricoTransacoesLock);
    guardarHistorico(caixa, movimentoSaldoCartao, valorProdutoOferecido);  
}

//* index Hash->|0|1|2|3|...          __HistoricoSubStructCliente
//*              |        ___________/      /
//*              V       V                 /
//*            |Nome, Id|  --> |1|2|3|4|5|... <--id caixas
//*                             | 
//*                          |Info|  <--- HistoricoSubStructInfo

void mostrarHistorico(){
    pthread_mutex_lock(&HistoricoDados.HistoricoTransacoesLock);
    for (int i = 0; i < HistoricoDados.tamanhoVetorHash; i++){
        Elemento* clientesHistorico = HistoricoDados.HistoricoTransacoes[i]->head;
        while(clientesHistorico){
            HistoricoSubStructCliente* clientesHistoricoInfo = (HistoricoSubStructCliente*) clientesHistorico->Info;
            for (int j = 0; j < Opcoes.numCaixasTotal; j++){
                Elemento* caixasHistorico = clientesHistoricoInfo->caixas[j]->head;
                while(caixasHistorico){
                    HistoricoSubStructInfo* caixasHistoricoInfo = (HistoricoSubStructInfo*) caixasHistorico->Info;
                    printc("\n[blue]Nome cliente:[/blue] %s\t[blue]ID cliente:[/blue] %d\n[blue]ID caixa:[/blue] %d\t[blue]Nome funcionário:[/blue] %d\t[blue]ID funcionário:[/blue] %d\n[blue]Data de transação:[/blue] %d/%d/%d\t[blue]Hora: %d:%d:%d[/blue]\n[blue]Tempo de espera na fila:[/blue] %s\t", clientesHistoricoInfo->nome, clientesHistoricoInfo->id, j, caixasHistoricoInfo->funcionario->nome, caixasHistoricoInfo->funcionario->id, caixasHistoricoInfo->dataTransacao.dia, caixasHistoricoInfo->dataTransacao.mes, caixasHistoricoInfo->dataTransacao.ano, caixasHistoricoInfo->dataTransacao.hora, caixasHistoricoInfo->dataTransacao.minuto, caixasHistoricoInfo->dataTransacao.segundo, formatTime(caixasHistoricoInfo->tempoEstimadoCaixa));

                    printc("[blue]Tempo de atraso:[/blue] ");
                    if(caixasHistoricoInfo->tempoAtraso < 0)
                        printc("[green]Adiantou-se:[/green] %.2f segundos\n", (float)caixasHistoricoInfo->tempoAtraso/1000.0);
                    else if(caixasHistoricoInfo->tempoAtraso > 0)
                        printc("[red]Atrasou-se:[/red] %.2f segundos\n", (float)caixasHistoricoInfo->tempoAtraso/1000.0);

                    Elemento* produtos = caixasHistoricoInfo->listaProdutos->head;
                    while(produtos){
                        ProdutoStruct* produtoInfo = (ProdutoStruct*) produtos->Info;
                        printc("\n\t[blue]ID produto:[/blue] %d [blue]Nome produto:[/blue] %s, [blue]QT:[/blue] %dX, [blue]Preco:[/blue] %.2f [blue]TCompra:[/blue] %d [blue]TCaixa:[/blue] %d",produtoInfo->id, produtoInfo->nome, produtoInfo->quantidadeProdutosRepetidos, produtoInfo->preco, produtoInfo->tempoCompra, produtoInfo->tempoCaixa );
                        produtos = produtos->next;
                    }

                    

                    caixasHistorico = caixasHistorico->next;
                }
            }
            
            clientesHistorico = clientesHistorico->next;
        }
    }
    
    pthread_mutex_unlock(&HistoricoDados.HistoricoTransacoesLock);
}