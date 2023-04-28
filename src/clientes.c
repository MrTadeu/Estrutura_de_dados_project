#include "../includes/TipoDados.h"

int checkIfUserExists(int id){
    for (int i = 0; i < n_clientes; i++){
        if (id == Clientes[i].id){
            return 1;            
        }
    }
    return 0;
}

int generateUserID(){
    int id = 0;
    srand(time(NULL));
    do{
        id = rand() % 1000000;
    }while(checkIfUserExists(id) == 1);
    return id;
}

void verClientes(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    for(int i = 0; i < n_clientes; i++){
        printf("\nID: %d Nome: %s Saldo do Cartão: %.2f€ Data Nascimento: %d/%d/%d", Clientes[i].id, Clientes[i].nome, Clientes[i].saldoCartaoCliente, Clientes[i].dataNascimento.dia, Clientes[i].dataNascimento.mes, Clientes[i].dataNascimento.ano);
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    getchar();
    getchar();
}

void verClientesCaixa(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    if(Opcoes.lojaAberta == 0){
        printc("\n\n[yellow]A loja está fechada! Não é possível ver os clientes em caixa.[/yellow]");
    }
    else{
        Elemento *Caixa = Global.caixas->head;
        while(Caixa){
            if(((CaixaStruct *)Caixa->Info)->aberta == 1){
                printc("[red]%d ºCaixa [green]ABERTA[/green] Tempo Espera: %ds [/red]\n", ((CaixaStruct *)Caixa->Info)->id, ((CaixaStruct *)Caixa->Info)->tempoTotalEspera);
            }
            else{
                printc("[red]%d ºCaixa FECHADA[/red]\n", ((CaixaStruct *)Caixa->Info)->id);
            }
            Elemento *Cliente = ((CaixaStruct *)Caixa->Info)->listaPessoas->head;
            while (Cliente){
                ClienteStruct ClienteInfo = *((ClienteStruct *)Cliente->Info);
                printc("\t[green]ID: %d Nome: %s Saldo do Cartão: %.2f€ Data Nascimento: %d/%d/%d[/green]", ClienteInfo.id, ClienteInfo.nome, ClienteInfo.saldoCartaoCliente, ClienteInfo.dataNascimento.dia, ClienteInfo.dataNascimento.mes, ClienteInfo.dataNascimento.ano);
                Elemento *Produtos = ClienteInfo.listaProdutos->head;
                while(Produtos){
                    ProdutoStruct *ProdutoInfo = ((ProdutoStruct *)Produtos->Info);
                    printc("\n\t\t[blue]%s X%d PREÇO: %.2f€[/blue]", ProdutoInfo->nome, ProdutoInfo->quantidadeProdutosRepetidos, ProdutoInfo->preco);
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
    getchar();
    getchar();
}

/* void verClientes(){ // VER CLIENTES INATIVOS / LOJA
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    for(int i = 0; i < n_clientes; i++){
        printf("\nID: %d Nome: %s Saldo do Cartão: %.2f€ Data Nascimento: %d/%d/%d", Clientes[i].id, Clientes[i].nome, Clientes[i].saldoCartaoCliente, Clientes[i].dataNascimento.dia, Clientes[i].dataNascimento.mes, Clientes[i].dataNascimento.ano);
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    getchar();
    getchar();
} */

void pesquisarClientes(){
    int id , flag = 0;
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    printc("Qual o ID do cliente que pretende pesquisar? ");
    scanf("%d", &id);
    for(int i = 0; i < n_clientes; i++){
        if(Clientes[i].id == id){
            flag = 1;
            printf("\nID: %d Nome: %s Saldo do Cartão: %.2f€ Data Nascimento: %d/%d/%d", Clientes[i].id, Clientes[i].nome, Clientes[i].saldoCartaoCliente, Clientes[i].dataNascimento.dia, Clientes[i].dataNascimento.mes, Clientes[i].dataNascimento.ano);
        }
    }
    if(flag == 0){
        printc("\n[yellow]Não existe nenhum cliente com esse ID![/yellow]");
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    getchar();
    getchar();
}

void adicionarCliente(){
    char *nome = (char*) malloc(100 * sizeof(char));
    Clientes = (ClienteStruct*) realloc(Clientes, (n_clientes + 1) * sizeof(ClienteStruct));
    Clientes[n_clientes].id = generateUserID();
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    printc("Qual o nome do cliente que pretende adicionar? ");
    scanf("%s", nome);
    Clientes[n_clientes].nome = (char*) malloc((strlen(nome) + 1) * sizeof(char));
    strcpy(Clientes[n_clientes].nome, nome);
    Clientes[n_clientes].saldoCartaoCliente = 0;
    printc("\n\nQual a data de nascimento do cliente? "); //falta validar data //falta validar data //falta validar data //falta validar data //falta validar data
    printc("\nDia: ");
    scanf("%d", &Clientes[n_clientes].dataNascimento.dia);
    printc("\nMês: ");
    scanf("%d", &Clientes[n_clientes].dataNascimento.mes);
    printc("\nAno: ");
    scanf("%d", &Clientes[n_clientes].dataNascimento.ano);
    Clientes[n_clientes].id = n_clientes;
    n_clientes++;
    printc("\n[yellow]Cliente adicionado com sucesso![/yellow]");
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    getchar();
    getchar();
    free(nome);
}

void editarCliente(){
    int id, flag = 0;
    char *nome = (char*) malloc(100 * sizeof(char));
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    printc("Qual o ID do cliente que pretende editar? ");
    scanf("%d", &id);
    for(int i = 0; i < n_clientes; i++){
        if(Clientes[i].id == id){
            flag = 1;
            printc("\nQual o novo nome do cliente? ");
            scanf("%s", nome);
            Clientes[i].nome = (char*) malloc((strlen(nome) + 1) * sizeof(char));
            strcpy(Clientes[i].nome, nome);
            printc("\n\nQual o novo saldo do cartão do cliente? ");
            scanf("%f", &Clientes[i].saldoCartaoCliente);
            printc("\n\nQual a nova data de nascimento do cliente? "); //falta validar data //falta validar data //falta validar data //falta validar data
            printc("\nDia: ");
            scanf("%d", &Clientes[i].dataNascimento.dia);
            printc("\nMês: ");
            scanf("%d", &Clientes[i].dataNascimento.mes);
            printc("\nAno: ");
            scanf("%d", &Clientes[i].dataNascimento.ano);
            printc("\n[yellow]Cliente editado com sucesso![/yellow]");
        }
    }
    if(flag == 0){
        printc("\n[yellow]Não existe nenhum cliente com esse ID![/yellow]");
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    getchar();
    getchar();
    free(nome);
}

void removerCliente(){
    int id, flag = 0;
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    printc("Qual o ID do cliente que pretende remover? ");
    scanf("%d", &id);
    for(int i = 0; i < n_clientes; i++){
        if(Clientes[i].id == id){
            flag = 1;
            for(int j = i; j < n_clientes; j++){
                Clientes[j] = Clientes[j + 1];
            }
            n_clientes--;
            printc("\n[yellow]Cliente removido com sucesso![/yellow]");
            continue;
        }
    }
    Clientes = (ClienteStruct*) realloc(Clientes, n_clientes * sizeof(ClienteStruct));
    if(flag == 0){
        printc("\n[yellow]Não existe nenhum cliente com esse ID![/yellow]");
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    getchar();
    getchar();
}

void criarProdutosAddCliente(ClienteStruct *cliente){
    ProdutoStruct *produtoEscolhido;
    for(int i = 0; i < Aleatorio(Opcoes.QuantMinProd, Opcoes.QuantMaxProd); i++){
        produtoEscolhido = escolherProduto();
        if(pesquisarProdutoListaRealizarAcao(cliente->listaProdutos, produtoEscolhido, aumentarNumProdutosrepetidos) == 0)
            AddElementoFim(cliente->listaProdutos, criarElemento((void *)produtoEscolhido));
    }
}

void calculoTemposCliente(ClienteStruct *cliente){
    if(!cliente){
        printf("[red]Error![/red] Given client is NULL");
        return;
    }

    Elemento *Aux = cliente->listaProdutos->head;
    while(Aux){
        ProdutoStruct *produto = (ProdutoStruct *) Aux->Info;
        cliente->tempoEstimadoCaixa += produto->tempoCaixa;
        cliente->tempoEstimadoCompra += produto->tempoCompra;
        Aux = Aux->next;
    }
}

ClienteStruct *escolherCliente(){
    ClienteStruct *cliente;
    if(Aleatorio(1, 75) > 75){ //Existe uma probabilidade de 25% de a pessoa não ser cliente
        cliente = criarGuest();
        cliente->listaProdutos = criarLista();
    }
    else if(n_clientesAtivos >= n_clientes){
        /* printc("\n\t[red]Erro![/red] Nao existem mais clientes disponiveis.\n"); */
        return NULL;
    }    
    else{
        cliente = (ClienteStruct *) malloc(sizeof(ClienteStruct)); 
        int indice = escolherAleatorioVetor(Clientes, n_clientesAtivos, n_clientes, sizeof(ClienteStruct), cliente); // Aleatoriamente escolhe um dos clientes do ficheiro txt e armazena os dados na varivel cliente criada acima
        Clientes[indice].ativo = 1;         

        pthread_mutex_lock(&vetorLock);
        batenteChange(&Clientes[n_clientesAtivos], &Clientes[indice], sizeof(ClienteStruct), &n_clientesAtivos, '+');   
        pthread_mutex_unlock(&vetorLock);
    }
    cliente->listaProdutos = criarLista();
    criarProdutosAddCliente(cliente);
    calculoTemposCliente(cliente);
    return cliente;
}

void DesocuparCliente(ClienteStruct *pessoa){
    int index = pesquisarClienteVetorBatente(pessoa);
    batenteChange(&Clientes[index], &Clientes[n_clientesAtivos-1], sizeof(ClienteStruct), &n_clientesAtivos, '-');
    pessoa->ativo = 0;
}