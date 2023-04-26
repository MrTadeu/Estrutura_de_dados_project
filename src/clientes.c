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

ClienteStruct *escolherCliente(){
    if(n_clientesAtivos >= n_clientes){
        printc("\n\t[red]Erro![/red] Nao existem mais clientes disponiveis.\n");
        return NULL;
    }
    if(n_clientesAtivos >= Opcoes.lotacaoMaxima){
        printc("\n\t[red]Erro![/red] Loja atingiu a lotação máxima.\n");
        return NULL;
    }

    ClienteStruct *cliente;
    if(Aleatorio(1, 100) > 75){ //Existe uma probabilidade de 25% de a pessoa não ser cliente
        cliente = criarGuest();
        cliente->listaProdutos = criarLista();
    }
    else{
        cliente = (ClienteStruct *) malloc(sizeof(ClienteStruct)); 
        int indice = escolherAleatorioVetor(Clientes, n_clientesAtivos, n_clientes, sizeof(ClienteStruct), cliente); // Aleatoriamente escolhe um dos clientes do ficheiro txt e armazena os dados na varivel cliente criada acima
        Clientes[indice].ativo = 1;                                                                           
        batenteChange(&Clientes[n_clientesAtivos], &Clientes[indice], sizeof(ClienteStruct), &n_clientesAtivos, '+');   
    }

    cliente->listaProdutos = criarLista();
    criarProdutosAddCliente(cliente->listaProdutos, Aleatorio(1, 100));
    calculoTemposCliente(cliente);
    return cliente;
}

void DesocuparCliente(ClienteStruct *pessoa){
    int index = pesquisarClienteVetor(pessoa);
    batenteChange(&Clientes[index], &Clientes[n_clientesAtivos-1], sizeof(ClienteStruct), &n_clientesAtivos, '-');
    pessoa->ativo = 0;
}