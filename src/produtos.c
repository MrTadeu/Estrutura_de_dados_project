#include "../includes/TipoDados.h"

void aumentarNumProdutosrepetidos(void *produtoArg){
    ProdutoStruct *produto = (ProdutoStruct *) produtoArg;
    produto->quantidadeProdutosRepetidos++;
}

int pesquisarProdutoListaRealizarAcao(Lista *lista, ProdutoStruct *produto, void(acao)(void *)){
    if(!lista){
        printf("\n\t[red]Error![/red] Given list is NULL\n");
        return -1;
    }
    if(!produto){
        printf("\n\t[red]Error![/red] given produto is NULL\n");
        return -1;
    }
        
    Elemento *aux = lista->head;
    while(aux){
        if(compararProduto(aux->Info, produto)){
            acao(aux->Info);
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}

int encontrarIdProdutos(int id){
    for (int i = 0; i < n_produtos; i++){
        if (Produtos[i].id == id){
            return i;
        }
    }
    return -1;
}



void verProdutos(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    for (int i = 0; i < n_produtos; i++){
        printf("\nID: %d Nome: %s Preço: %.2f€\n", Produtos[i].id, Produtos[i].nome, Produtos[i].preco);
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void pesquisarProdutoID(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    int id;
    printf("Insira o ID do produto que pretende pesquisar: ");
    scanf("%d", &id);
    int pos = encontrarIdProdutos(id);
    if (pos == -1){
        printf("Produto não encontrado!\n");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
    else{
        printf("\nID: %d Nome: %s Preço: %.2f€\n", Produtos[pos].id, Produtos[pos].nome, Produtos[pos].preco);
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    } 
   
}

void pesquisarProdutoNome(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    char nome[100];
    printf("Insira o nome do produto que pretende pesquisar: ");
    bufferclear();
    scanf("%[^\n]", nome);
    printf("%s\n", nome);
    printf("Resultados semelhantes: \n");
    int flag = 0;
    for (int i = 0; i < n_produtos; i++){
        if (PesquisaParecido(nome, Produtos[i].nome) <= 14){
            printf("\nID: %d Nome: %s Preço: %.2f€\n", Produtos[i].id, Produtos[i].nome, Produtos[i].preco);
            flag = 1;
        }
    }
    if (flag == 0){
        printc("[red]Não foram encontrados resultados semelhantes![/red]\n");
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    return;
}

void adicionarProduto(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    char nome[100];
    printf("Insira o nome do produto: ");
    bufferclear();
    scanf("%[^\n]", nome);
    Produtos[n_produtos].nome = (char*)malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(Produtos[n_produtos].nome, nome);    

    printf("Insira o preço do produto €: ");
    scanf("%f", &Produtos[n_produtos].preco);
    Produtos[n_produtos].id = generateID(encontrarIdFuncionario, -1);
    n_produtos++;
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarProduto(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    verProdutos();
    int id;
    printf("Insira o ID do Produto que pretende editar: ");
    scanf("%d", &id);
    int pos = encontrarIdProdutos(id);
    if (pos == -1){
        printf("Produto não encontrado!\n");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
    else{
        printf("\nID: %d Nome: %s Preço: %.2f€\n", Produtos[pos].id, Produtos[pos].nome, Produtos[pos].preco);

        char nome[100];
        printf("Insira o novo nome do produto: ");
        bufferclear();
        scanf("%[^\n]", nome);
        Produtos[pos].nome = (char*)malloc(sizeof(char) * (strlen(nome) + 1));
        strcpy(Produtos[pos].nome, nome);

        printf("Insira o novo preço do produto €: ");
        scanf("%f", &Produtos[pos].preco);

        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
}

void removerProduto(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    verProdutos();
    int id;
    printf("Insira o ID do Produto que pretende remover: ");
    scanf("%d", &id);
    int pos = encontrarIdProdutos(id);
    if (pos == -1){
        printf("Produto não encontrado!\n");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
    else{
        for (int i = pos; i < n_produtos - 1; i++){
            Produtos[i] = Produtos[i + 1];
        }
        n_produtos--;
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
}