#include "../includes/TipoDados.h"


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
    getchar();
    getchar();
}

void pesquisarProduto(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    int id;
    printf("Insira o ID do produto que pretende pesquisar: ");
    scanf("%d", &id);
    int pos = encontrarIdProdutos(id);
    if (pos == -1){
        printf("Produto não encontrado!\n");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        getchar();
        getchar();
    }
    else{
        printf("\nID: %d Nome: %s Preço: %.2f€\n", Produtos[pos].id, Produtos[pos].nome, Produtos[pos].preco);
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        getchar();
        getchar();
    }
}

void adicionarProduto(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    char nome[100];
    printf("Insira o nome do produto: ");
    getchar();
    scanf("%[^\n]", nome);
    Produtos[n_produtos].nome = (char*)malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(Produtos[n_produtos].nome, nome);    

    printf("Insira o preço do produto €: ");
    scanf("%f", &Produtos[n_produtos].preco);
    Produtos[n_produtos].id = generateID(encontrarIdFuncionario, -1);
    n_produtos++;
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    getchar();
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
        getchar();
        getchar();
    }
    else{
        printf("\nID: %d Nome: %s Preço: %.2f€\n", Produtos[pos].id, Produtos[pos].nome, Produtos[pos].preco);

        char nome[100];
        printf("Insira o novo nome do produto: ");
        getchar();
        scanf("%[^\n]", nome);
        Produtos[pos].nome = (char*)malloc(sizeof(char) * (strlen(nome) + 1));
        strcpy(Produtos[pos].nome, nome);

        printf("Insira o novo preço do produto €: ");
        scanf("%f", &Produtos[pos].preco);

        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        getchar();
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
        getchar();
        getchar();
    }
    else{
        for (int i = pos; i < n_produtos - 1; i++){
            Produtos[i] = Produtos[i + 1];
        }
        n_produtos--;
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        getchar();
        getchar();
    }
}