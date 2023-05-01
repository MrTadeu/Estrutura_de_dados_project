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

int minimo(int a, int b, int c) {
    int menor = a;

    if (b < menor)  menor = b;
    if (c < menor) menor = c;
    
    return menor;
}

int PesquisaParecido(char *str1, char *str2){// Levenshtein Distance é para ver a distancia de diferença entre as palavras não esquecer de po-las em maiúsculas (para a minha comparaçao dar certo)!
    int **matriz = calloc(strlen(str1) + 1, sizeof(int*));
    int custo;
    for (size_t i = 0; i < strlen(str1) + 1; i++){
        matriz[i] = calloc(strlen(str2) + 1, sizeof(int));
    }
    for (size_t i = 0; i < strlen(str1) + 1; i++){
        matriz[i][0] = i;
    }
    for (size_t i = 0; i < strlen(str2) + 1; i++){
        matriz[0][i] = i;
    }
    for (size_t i = 1; i < strlen(str1) + 1; i++){
        for (size_t j = 1; j < strlen(str2) + 1; j++){
            if (str1[i] == str2[j]) {
                custo = 0;
            } else {
                custo = 1;
            }

            matriz[i][j] = minimo(matriz[i-1][j] + 1, matriz[i][j-1] + 1, matriz[i-1][j-1] + custo);
        }
    }
    int resultado = matriz[strlen(str1)][strlen(str2)];
    for (size_t i = 0; i < strlen(str1) + 1; i++){
        free(matriz[i]);
    }
    free(matriz);
    return resultado;
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

void pesquisarProdutoID(){
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

void pesquisarProdutoNome(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    char nome[100];
    printf("Insira o nome do produto que pretende pesquisar: ");
    getchar();
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
    getchar();
    getchar();
    return;
}

void pesquisarProduto(){
    int opcao = 0;
    do{
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
        printc("[blue]0[/blue] - Voltar\n");
        printc("[blue]1[/blue] - Pesquisar por ID\n");
        printc("[blue]2[/blue] - Pesquisar por nome\n");
        printf("Opção: ");
        scanf("%d", &opcao);
    } while (opcao != 0 && opcao != 1  && opcao != 2);
    switch (opcao){
    case 0:
        return;
        break;
    case 1:
        pesquisarProdutoID();
        break;
    case 2:
        pesquisarProdutoNome();
        break;
    default:
        break;
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