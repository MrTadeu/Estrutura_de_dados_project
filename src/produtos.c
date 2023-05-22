#include "../includes/TipoDados.h"

int pesquisarProdutoListaRealizarAcao(Lista *lista, ProdutoStruct *produto){
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
        if(((ProdutoStruct *)aux->Info)->id == produto->id){
            ((ProdutoStruct *)aux->Info)->quantidadeProdutosRepetidos++;
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}

int encontrarIdProduto(int id){
    for (int i = 0; i < n_produtos; i++){
        if (Produtos[i].id == id){
            return i;
        }
    }
    return -1;
}

void verProdutos(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    printc("[yellow]Listar Todos Produtos:[/yellow]\n");
    for (int i = 0; i < n_produtos; i++){
        printf("\nID: %d Nome: %s Preço: %.2f€", Produtos[i].id, Produtos[i].nome, Produtos[i].preco);
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void pesquisarProdutoID(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    int id;
    scanfs("%d", &id, "Insira o ID do produto que pretende pesquisar: ", "Apenas pode inserir números inteiros!\n");

    int pos = encontrarIdProduto(id);
    if (pos == -1){
        printc("[red]Produto não encontrado![/red]\n");
    }
    else{
        printf("\nID: %d Nome: %s Preço: %.2f€\n", Produtos[pos].id, Produtos[pos].nome, Produtos[pos].preco);
    } 
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void pesquisarProdutoNome(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    char nome[100];
    scanfs("%[^\n]", nome, "Insira o nome do produto que pretende pesquisar: ", "Apenas pode inserir letras!\n");
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
}

void adicionarProduto(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);

    char nome[100];
    scanfs("%[^\n]", nome, "Insira o nome do produto: ", "Apenas pode inserir letras!\n");
    Produtos[n_produtos].nome = (char*)malloc(sizeof(char) * (strlen(nome) + 1));
    strcpy(Produtos[n_produtos].nome, nome);    

    int invalid = 0;
    do{
        invalid = 1;
        scanfs("%f", &Produtos[n_produtos].preco, "Insira o preço do produto €: ", "Apenas pode inserir números do tipo float!\n");
        if(Produtos[n_produtos].preco < 0){
            printc("[red]O preço não pode ser negativo![/red]\n");
            invalid = -1;
        }
    }while(invalid != 1);

    Produtos[n_produtos].id = generateID(encontrarIdProduto);
    n_produtos++;
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarProduto(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    int id;
    scanfs("%d", &id, "Insira o ID do Produto que pretende editar: ", "Apenas pode inserir números inteiros!\n");
    int pos = encontrarIdProduto(id);
    if (pos == -1){
        printc("[red]Produto não encontrado![/red]\n");        
    }
    else{
        printc("[yellow]Listar Dados do Produto a Editar:[/yellow]\n");
        printf("\nID: %d \nNome: %s \nPreço: %.2f€", Produtos[pos].id, Produtos[pos].nome, Produtos[pos].preco);

        char nome[100];
        scanfs("%[^\n]", nome, "\nNome do produto: ", "Apenas pode inserir letras!\n");
        free(Produtos[pos].nome);
        Produtos[pos].nome = (char*)malloc(sizeof(char) * (strlen(nome) + 1));
        strcpy(Produtos[pos].nome, nome);

        int invalid = 0;
        do{
            invalid = 1;
            scanfs("%f", &Produtos[pos].preco, "Preço do produto €: ", "Apenas pode inserir números do tipo float!\n");
            if(Produtos[pos].preco < 0){
                printc("[red]O preço não pode ser negativo![/red]\n");
                invalid = -1;
            }
        }while(invalid != 1);
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}
//ver depoissssssssssss
void removerProduto(){
    fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    int id;
    scanfs("%d", &id, "Insira o ID do Produto que pretende remover: ", "Apenas pode inserir números inteiros!\n");
    int pos = encontrarIdProduto(id);
    if (pos == -1){
        printc("[red]Produto não encontrado![/red]\n");
    }
    else{
        free(Produtos[pos].nome);

        for (int i = pos; i < n_produtos - 1; i++){
            Produtos[i] = Produtos[i + 1];
        }
        n_produtos--;
        Produtos = (ProdutoStruct*)realloc(Produtos, sizeof(ProdutoStruct) * n_produtos);
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

int compareProduto(void* p1, void* p2){
    ProdutoStruct *produto1 = (ProdutoStruct*) p1, *produto2 = (ProdutoStruct*) p2;
    if(!produto1 || produto2){
        printc("\n\t[red]Error[/red] Given product is NULL\n");
        return -1;
    }
    if(produto1->id == produto2->id)
        return 1;
    return 0;
}

ProdutoStruct *escolherProduto(){
    ProdutoStruct *produto = (ProdutoStruct *) malloc(sizeof(ProdutoStruct));
    memcpy(produto, &Produtos[Aleatorio(0, n_produtos-1)], sizeof(ProdutoStruct));
    return produto;
}

void destruirProduto(void *Produto){
    free(((ProdutoStruct *)Produto)->nome);
    free(Produto);
}
