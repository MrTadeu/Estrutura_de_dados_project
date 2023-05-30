#include "../includes/TipoDados.h"

int encontrarIdCliente(int id){
    for (int i = 0; i < n_clientes; i++){
        if (id == Clientes[i]->id){
            return i;            
        }
    }
    return -1;
}

void verClientes(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    printc("[yellow]Listar Todos Clientes:[/yellow]\n");
    for(int i = 0; i < n_clientes; i++){
        printf("\nID: %d Nome: %s Saldo do Cartão: %.2f€ Data Nascimento: %d/%d/%d", Clientes[i]->id, Clientes[i]->nome, Clientes[i]->saldoCartaoCliente, Clientes[i]->dataNascimento.dia, Clientes[i]->dataNascimento.mes, Clientes[i]->dataNascimento.ano);
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void encontrarCaixaCliente(ClienteStruct *cliente){
    Elemento* caixaAux = Global.caixas->head;
    while (caixaAux){
        Elemento* pessoas = ((CaixaStruct *)caixaAux->Info)->listaPessoas->head;
        while (pessoas){
            if (((ClienteStruct *)pessoas->Info)->id == cliente->id){
                printc("O cliente %s com id %d está na caixa: %d", cliente->nome, cliente->id, ((CaixaStruct *)caixaAux->Info)->id);
                Elemento *Produtos = ((ClienteStruct *)pessoas->Info)->listaProdutos->head;
                while(Produtos){
                    ProdutoStruct *ProdutoInfo = ((ProdutoStruct *)Produtos->Info);
                    printc("\n\t\t[blue]%s %dx PREÇO: %.2f€[/blue] tempoCaixa:%d", ProdutoInfo->nome, ProdutoInfo->quantidadeProdutosRepetidos, ProdutoInfo->preco, ProdutoInfo->tempoCaixa);
                    Produtos = Produtos->next;
                }
                return;
            }
            pessoas = pessoas->next;
        }
        caixaAux = caixaAux->next;
    }
}

void verSeClienteEspecificoEmCaixa(){
    int id;
    scanfs("%d", &id, "\nInsira o ID do cliente que pretende pesquisar: ", "Apenas pode inserir números inteiros!");
    int pos = encontrarIdCliente(id);
    if (pos == -1) {
        printc("\n\n\t[red]Cliente id não existe![/red]");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
        return;
    } 


    if (Clientes[pos]->ativo == 1){
        encontrarCaixaCliente(Clientes[pos]);
    }
    else printc("\n\n\t[yellow]Cliente não está em nenhuma caixa![/yellow]");
    
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void verClientesEmLoja(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    if(Opcoes.lojaAberta == 0){
        printc("\n\n[yellow]A loja está fechada! Não é possível ver os clientes em caixa.[/yellow]");
    }else{
        printc("[yellow]Listar Todos Clientes na Loja:[/yellow]\n");
        for(int i = 0; i < n_clientesAtivos; i++){
            printf("\nID: %d Nome: %s Saldo do Cartão: %.2f€ Data Nascimento: %d/%d/%d Tempo Compra: %d Tempo Caixa: %d", Clientes[i]->id, Clientes[i]->nome, Clientes[i]->saldoCartaoCliente, Clientes[i]->dataNascimento.dia, Clientes[i]->dataNascimento.mes, Clientes[i]->dataNascimento.ano, Clientes[i]->tempoEstimadoCompra, Clientes[i]->tempoEstimadoCaixa);
        }
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void verClientesInativos(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    printc("[yellow]Listar Todos Clientes Inativos:[/yellow]\n");
    for(int i = n_clientesAtivos; i < n_clientes; i++){
        printf("\nID: %d Nome: %s Saldo do Cartão: %.2f€ Data Nascimento: %d/%d/%d", Clientes[i]->id, Clientes[i]->nome, Clientes[i]->saldoCartaoCliente, Clientes[i]->dataNascimento.dia, Clientes[i]->dataNascimento.mes, Clientes[i]->dataNascimento.ano);
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void verClientesCaixa(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    if(/* Opcoes.lojaAberta ==  */0){
        printc("\n\n[yellow]A loja está fechada! Não é possível ver os clientes em caixa.[/yellow]");
    }
    else{
        Elemento *Caixa = Global.caixas->head;
        while(Caixa){
            if(((CaixaStruct *)Caixa->Info)->aberta == 1 /* || ((CaixaStruct *)Caixa->Info)->listaPessoas->head != NULL */){
                char tempoTotalEspera[9];
                formatTime(((CaixaStruct *)Caixa->Info)->tempoTotalEspera, tempoTotalEspera);
                printc("[red]%d ºCaixa [green]ABERTA[/green]  Funcionario: %s Número De Vendas: %d Tempo Espera: %s [/red]\n", ((CaixaStruct *)Caixa->Info)->id, ((CaixaStruct *)Caixa->Info)->funcionario->nome, ((CaixaStruct *)Caixa->Info)->funcionario->n_vendas, tempoTotalEspera);
            }
            else{
                printc("[red]%d ºCaixa FECHADA[/red]\n", ((CaixaStruct *)Caixa->Info)->id);
            }
            Elemento *Cliente = ((CaixaStruct *)Caixa->Info)->listaPessoas->head;
            while (Cliente){
                ClienteStruct ClienteInfo = *((ClienteStruct *)Cliente->Info);
                printc("\t[green]ID: %d Nome: %s Saldo do Cartão: %.2f€ Data Nascimento: %d/%d/%d TempoAtraso: %d tempoBrinde: %d TempoEstimadoCaixa: %d tempoEstimadoCompra: %d precoTotalProdutos: %.2f [/green]", ClienteInfo.id, ClienteInfo.nome, ClienteInfo.saldoCartaoCliente, ClienteInfo.dataNascimento.dia, ClienteInfo.dataNascimento.mes, ClienteInfo.dataNascimento.ano, ClienteInfo.tempoAtraso, ClienteInfo.tempoBrinde, ClienteInfo.tempoEstimadoCaixa, ClienteInfo.tempoEstimadoCompra, ClienteInfo.precoTotalProdutos);
                Elemento *Produtos = ClienteInfo.listaProdutos->head;
                while(Produtos){
                    ProdutoStruct *ProdutoInfo = ((ProdutoStruct *)Produtos->Info);
                    printc("\n\t\t[blue]%s %dx PREÇO: %.2f€[/blue] tempoCaixa:%d", ProdutoInfo->nome, ProdutoInfo->quantidadeProdutosRepetidos, ProdutoInfo->preco, ProdutoInfo->tempoCaixa);
                    Produtos = Produtos->next;
                }
                printf("\n");
                Cliente = Cliente->next;
            }
            printf("\n\n");
            Caixa = Caixa->next; 
        }
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void pesquisarClienteID(){
    int id , flag = 0;
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    scanfs("%d", &id, "\nInsira o ID do cliente que pretende pesquisar: ", "Apenas pode inserir números inteiros!");

    for(int i = 0; i < n_clientes; i++){
        if(Clientes[i]->id == id){
            flag = 1;
            printf("\nID: %d Nome: %s Saldo do Cartão: %.2f€ Data Nascimento: %d/%d/%d", Clientes[i]->id, Clientes[i]->nome, Clientes[i]->saldoCartaoCliente, Clientes[i]->dataNascimento.dia, Clientes[i]->dataNascimento.mes, Clientes[i]->dataNascimento.ano);
        }
    }
    if(flag == 0){
        printc("\n[yellow]Não existe nenhum cliente com esse ID![/yellow]");
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void pesquisarClienteNome(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    char nome[100];
    scanfv("%[^\n]", &nome, "Insira o nome do cliente que pretende pesquisar: ", "Input invalido, tente novamente: ", validateIsAlphabetic);

    printc("\n[blue]Resultados semelhantes:[/blue] \n");
    int flag = 0;
    for (int i = 0; i < n_clientes; i++){
        if (PesquisaParecido(nome, Clientes[i]->nome) <= 4){
            printf("\nID: %d Nome: %s Saldo do Cartão: %.2f€ Data Nascimento: %d/%d/%d", Clientes[i]->id, Clientes[i]->nome, Clientes[i]->saldoCartaoCliente, Clientes[i]->dataNascimento.dia, Clientes[i]->dataNascimento.mes, Clientes[i]->dataNascimento.ano);
            flag = 1;
        }
    }
    if (flag == 0){
        printc("[red]Não foram encontrados resultados semelhantes![/red]\n");
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void adicionarCliente(){
    char nome[100];
    int invalidDate = 0;
    Clientes = (ClienteStruct **) realloc(Clientes, (n_clientes + 1) * sizeof(ClienteStruct *));
    Clientes[n_clientes] = (ClienteStruct *) malloc(sizeof(ClienteStruct));
    Clientes[n_clientes]->id = generateID(encontrarIdCliente);
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    printc("[blue]Introduza os dados do Cliente:[/blue]\n");
    printc("\n\n[yellow]ID CLIENTE: %d[/yellow]\n", Clientes[n_clientes]->id);
    
    scanfv("%[^\n]", &nome, "Nome: ", "Input invalido, tente novamente: ", validateIsAlphabetic);

    Clientes[n_clientes]->nome = (char*) malloc((strlen(nome) + 1) * sizeof(char));
    strcpy(Clientes[n_clientes]->nome, nome);

    float n;
    scanfv("%f", &n, "Saldo do cliente: ", "Saldo do cliente >= 0!\n", validateRangeFloat, 0.0, 100000000.0);
    Clientes[n_clientes]->saldoCartaoCliente = n;

    printc("\nData de nascimento:");
    struct tm tm = getCurrentTime();
    do{
        invalidDate++;
        if(invalidDate >=2){
            printc("\n[red]Data Invalida![/red]\n");
        }
        scanfs("%d", &Clientes[n_clientes]->dataNascimento.dia, "Dia: ", "Apenas pode inserir números inteiros!");
        scanfs("%d", &Clientes[n_clientes]->dataNascimento.mes, "Mês: ", "Apenas pode inserir números inteiros!");
        scanfs("%d", &Clientes[n_clientes]->dataNascimento.ano, "Ano: ", "Apenas pode inserir números inteiros!");
    } while (validarData(Clientes[n_clientes]->dataNascimento, tm.tm_year + 1900 - 110, tm.tm_year + 1900 - 10) == 0);
    
    n_clientes++;
    printc("\n[yellow]Cliente adicionado com sucesso![/yellow]");
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarCliente(){
    int id, invalidDate = 0;
    char nome[100];
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    scanfs("%d", &id, "Insira o ID do cliente que pretende editar: ", "Apenas pode inserir números inteiros!");
    
    int index = encontrarIdCliente(id);
    if(index == -1){
        printc("[red]\nCliente não encontrado![/red]\n");
    }
    else{
        printc("[yellow]Listar Dados do Cliente a editar:[/yellow]\n");
        printf("\nID: %d \nNome: %s \nSaldo do Cartão: %.2f€ \nData Nascimento: %d/%d/%d", Clientes[index]->id, Clientes[index]->nome, Clientes[index]->saldoCartaoCliente, Clientes[index]->dataNascimento.dia, Clientes[index]->dataNascimento.mes, Clientes[index]->dataNascimento.ano);
        printc("\n[blue]Introduza os novos dados do cliente a editar[/blue]\n");

        scanfv("%[^\n]", &nome, "Nome: ", "Input invalido, tente novamente: ", validateIsAlphabetic);
        free(Clientes[index]->nome);
        Clientes[index]->nome = (char*) malloc((strlen(nome) + 1) * sizeof(char));
        strcpy(Clientes[index]->nome, nome);

        float n;
        scanfv("%f", &n, "Saldo do cliente: ", "Saldo do cliente >= 0!\n", validateRangeFloat, 0.0, 100000000.0);
        Clientes[index]->saldoCartaoCliente = n;

        printc("\nData de nascimento:");
        struct tm tm = getCurrentTime();
        do{
            invalidDate++;
            if(invalidDate >=2){
                printc("\n[red]Data Invalida![/red]\n");
            }
            scanfs("%d", &Clientes[index]->dataNascimento.dia, "Dia: ", "Apenas pode inserir números inteiros!");
            scanfs("%d", &Clientes[index]->dataNascimento.mes, "Mês: ", "Apenas pode inserir números inteiros!");
            scanfs("%d", &Clientes[index]->dataNascimento.ano, "Ano: ", "Apenas pode inserir números inteiros!");
        } while (validarData(Clientes[index]->dataNascimento, tm.tm_year + 1900 - 110, tm.tm_year + 1900 - 10) == 0);

        printc("\n[yellow]Cliente editado com sucesso![/yellow]");
    }
   
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void removerCliente(){
    int id, index;
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    scanfs("%d", &id, "Insira o ID do cliente que pretende remover: ", "Apenas pode inserir números inteiros!");

    index = encontrarIdCliente(id);
    if(index == -1){
        printc("\n[yellow]Não existe nenhum cliente com esse ID1![/yellow]");
    }
    else{
        free(Clientes[index]->nome);
        free(Clientes[index]);
        Clientes[index] = Clientes[--n_clientes];
        Clientes = (ClienteStruct**) realloc(Clientes, n_clientes * sizeof(ClienteStruct*));
    }

    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void criarProdutosAddCliente(ClienteStruct *cliente){
    ProdutoStruct *produtoEscolhido;
    for(int i = 0; i < Aleatorio(Opcoes.QuantMinProd, Opcoes.QuantMaxProd); i++){
        produtoEscolhido = escolherProduto();
        if(pesquisarProdutoListaAtualizarRepetidos(cliente->listaProdutos, produtoEscolhido) == 0)
            AddElementoFim(cliente->listaProdutos, criarElemento((void *)produtoEscolhido));
    }
}

void calculos_TempoPreco_Cliente(ClienteStruct *cliente){
    if(!cliente){
        printf("[red]Error![/red] Given client is NULL");
        return;
    }
    Elemento *Aux = cliente->listaProdutos->head;
    while(Aux){
        ProdutoStruct *produto = (ProdutoStruct *) Aux->Info;
        cliente->tempoEstimadoCaixa += produto->tempoCaixa * produto->quantidadeProdutosRepetidos;
        cliente->tempoEstimadoCompra += produto->tempoCompra * produto->quantidadeProdutosRepetidos;
        cliente->precoTotalProdutos += produto->preco * produto->quantidadeProdutosRepetidos; 

        Aux = Aux->next;
    }
}

ClienteStruct *escolherCliente(){
    ClienteStruct *cliente;
    if(Aleatorio(1, 75) >= 75){ //Existe uma probabilidade de 25% de a pessoa não ser cliente
        cliente = criarGuest();
    }
    else if(n_clientesAtivos >= n_clientes){
        /* printc("\n\t[red]Erro![/red] Nao existem mais clientes disponiveis.\n"); */
        return NULL;
    }    
    else{
        pthread_mutex_lock(&ClientesLock);
        int index = Aleatorio(n_clientesAtivos, n_clientes - 1);
        cliente = Clientes[index];
        cliente->ativo = 1;
        
        Clientes[index] = Clientes[n_clientesAtivos];
        Clientes[n_clientesAtivos] = cliente;
        n_clientesAtivos++;
        pthread_mutex_unlock(&ClientesLock);
    }
    
    Global.n_pessoasEmLoja++;
    cliente->listaProdutos = criarLista();
    criarProdutosAddCliente(cliente);
    calculos_TempoPreco_Cliente(cliente);
    return cliente;
}

void DesocuparCliente(ClienteStruct *pessoa){
    pthread_mutex_lock(&ClientesLock);
    if (Opcoes.VerTransacoes){
        printc("\n\n[blue]Clientes em Loja:[/blue] %d, [blue]Clientes Total:[/blue] %d\n", n_clientesAtivos, n_clientes);
    }
    
    int index = pesquisarClienteVetorBatente(pessoa);
    if(index == -1){
        printc("[blue]\n\n\n\t\tn_clientesAtivos %d, n_clientes\n[/blue] %d", n_clientesAtivos, n_clientes);
        printc("[red]Error![/red] Given client is NULL É AQUI DESOCUPAR CLIENTE");
        pthread_mutex_unlock(&ClientesLock);
        return;
    }
    ClienteStruct *cliente = Clientes[index];
    cliente->ativo = 0;
    
    Clientes[index] = Clientes[--n_clientesAtivos];
    Clientes[n_clientesAtivos] = cliente;
    /* n_clientesAtivos--; */
    pthread_mutex_unlock(&ClientesLock);
}

int pesquisarClienteVetorBatente(ClienteStruct *pessoa){
    for (int i = 0; i < n_clientesAtivos; i++){
        /* printf("[red]\n Clientes[i]->nome %s  pessoa->nome %s[/red] id: Clientes[i]->id, %d  pessoa->id %d", Clientes[i]->nome, pessoa->nome, Clientes[i]->id, pessoa->id); */
        if(strcmp(Clientes[i]->nome, pessoa->nome) == 0 && Clientes[i]->id == pessoa->id){
            return i;
        }
    }
    return -1;
}


float atualizarSaldoCliente(ClienteStruct *pessoaEmAtendimento){
    float movimentoSaldoCartao = pessoaEmAtendimento->saldoCartaoCliente;
    if(Aleatorio(0, 100) <= Opcoes.probUsarSaldoCartao)
        pessoaEmAtendimento->saldoCartaoCliente -= Aleatorio(0, pessoaEmAtendimento->saldoCartaoCliente);
    else
        pessoaEmAtendimento->saldoCartaoCliente += (pessoaEmAtendimento->precoTotalProdutos * Opcoes.percentagemPrecoAngariarSaldo)/100;
    movimentoSaldoCartao = pessoaEmAtendimento->saldoCartaoCliente - movimentoSaldoCartao;
    //!printf("Saldo Cartao: %f\n", pessoaEmAtendimento->saldoCartaoCliente);
    return movimentoSaldoCartao;
}

ClienteStruct *criarGuest(){
    ClienteStruct *cliente = (ClienteStruct *) malloc(sizeof(ClienteStruct));
    cliente->id = -1;
    cliente->nome = (char *) malloc(sizeof(char)*13);
    strcpy(cliente->nome, "Desconhecido");
    cliente->tempoAtraso = 0;
    cliente->tempoEstimadoCaixa = 0;
    cliente->tempoEstimadoCompra = 0;
    cliente->tempoEstimadoFila = 0;
    return cliente;
}

void destruirCliente(void *Cliente){
    destruirLista(((ClienteStruct *)Cliente)->listaProdutos, destruirProduto);
    free(((ClienteStruct *)Cliente)->nome);
    free(Cliente);
}

float oferecerBrinde(ClienteStruct *cliente){
    if(cliente->tempoBrinde > Opcoes.tempoAtrasoMaximoBrinde){
        printc("\n\n[red]BRINDE[/red]");
        printc("[red]Preco antigo: %f[/red]", cliente->precoTotalProdutos);
        Elemento *aux = cliente->listaProdutos->head, *produtoOferecido = aux;
        float precoMin = ((ProdutoStruct*)aux->Info)->preco;

        while(aux){
            if(((ProdutoStruct*)aux->Info)->preco < precoMin){
                precoMin = ((ProdutoStruct*)aux->Info)->preco;
                produtoOferecido = aux;
            }  
            aux = aux->next;
        }
        cliente->precoTotalProdutos -= ((ProdutoStruct*)produtoOferecido->Info)->preco;
        printc("[red]ID Produto: %f[/red]", ((ProdutoStruct*)produtoOferecido->Info)->nome);
        printc("[red]Preco novo: %f[/red]", cliente->precoTotalProdutos);

        ((ProdutoStruct*)produtoOferecido->Info)->oferecido = 1;
        return precoMin;
    }
    else{
        return -1.0;
    }
}
