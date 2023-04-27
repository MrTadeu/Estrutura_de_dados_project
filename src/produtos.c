#include "../includes/TipoDados.h"


int encontrarIdProdutos(int id){
    for (int i = 0; i < n_produtos; i++){
        if (Produtos[i].id == id){
            return i;
        }
    }
    return -1;
}

/* int minimo(int a, int b, int c) {
    int menor = a;
    if (b < menor) {
        menor = b;
    }
    if (c < menor) {
        menor = c;
    }
    return menor;
}

int nomeIncompleto(char* str1, char* str2){ // Levenshtein Distance é para ver a distancia de diferença entre as palavras não esquecer de po-las em maiúsculas (para a minha comparaçao dar certo)
    if (str1 == NULL || str2 == NULL) return 999;
    
    int distancia, custo;
    int linha = strlen(str1) + 1; 
    int coluna = strlen(str2) + 1;

    int **matriz = calloc(linha + 1, sizeof(int));
    for (int i = 0; i <= linha; i++){
        matriz[i] = calloc(coluna + 1, sizeof(int));
    }
    for (int i = 1; i < coluna; i++){
        matriz[0][i] = i;
    }
    for (int i = 1; i < linha; i++){
        matriz[i][0] = i;
    }
    printc("[red]Passou\n[/red]");
    printf("str1: %s      %d   |str2: %s     %d\n", str1, linha, str2, coluna);
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            printf("%d ", matriz[i][j]);
            if (j >= 9 && i != 0){
                printf(" ");
            }
            
        }
        printf("\n");
    }
    getchar();
    getchar();

    for (int i = 1; i < linha; i++){ // Distancia

        for (int j = 1; j < coluna; j++){
            if (str1[i - 1] == str2[j - 1]){
                custo = 0;
            }
            else{
                custo = 1;
            }
            int num = minimo(matriz[i - 1][j] + 1, matriz[i][j - 1] + 1, matriz[i - 1][j - 1] + custo);
            printf("num: %d\n", num);
            matriz[i][j] = num;
            printc("\n\n\t\t Num:[red]%d[/red][green]i: %d j: %d[/green]\n", num, i, j);
            for (int i = 0; i < linha; i++){

                for (int j = 0; j < coluna; j++){
                    printf("%d ", matriz[i][j]);
                    if (matriz[i][j] < 10 && j >= 9 && i != 0){
                        printf(" ");
                    }
                    if (i == 0 && j > 9){
                        printf(" ");
                    }
                    
                }
                printf("\n");
            }
        }
        for (int i = 0; i < linha; i++){

        for (int j = 0; j < coluna; j++){
            printf("%d ", matriz[i][j]);
            if (j >= 9 && i != 0){
                printf(" ");
            }
            
        }
        printf("\n");
        }
        printc("[red]hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh[/red]\n");
    }
    printf("str1: %s      %d   |str2: %s     %d\n", str1, linha, str2, coluna);
    printf("-----------------------------------------Acabou-----------------------------------------------\n");
    distancia = matriz[linha][coluna];
    for (int i = 0; i <= coluna; i++){
        free(matriz[i]);
    }
    free(matriz);
    printc("[green]\nPassou[/green]");
    return distancia;
} */

int minimum(int a, int b, int c) {
    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}
int nomeIncompleto(char *s1, char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int* distance = (int*) calloc((len1+1)*(len2+1), sizeof(int));

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0) {
                distance[j] = j;
            } else if (j == 0) {
                distance[i*(len2+1)] = i;
            } else {
                int substitutionCost = (s1[i-1] == s2[j-1]) ? 0 : 1;
                distance[i*(len2+1) + j] = 
                    minimum(distance[(i-1)*(len2+1) + j] + 1, // deletion
                            distance[i*(len2+1) + j-1] + 1, // insertion
                            distance[(i-1)*(len2+1) + j-1] + substitutionCost); // substitution
            }
        }
    }

    int result = distance[len1*(len2+1) + len2];
    free(distance);
    return result;
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

    /* int id;
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
    */

    char nome[100];
    printf("Insira o nome do produto que pretende pesquisar: ");
    scanf("%s", nome);
    printf("%s\n", nome);
    printf("Resultados semelhantes: \n");
    for (int i = 0; i < n_produtos; i++){
        if (nomeIncompleto(nome, Produtos[i].nome) <= 35){
            printf("\nID: %d Nome: %s Preço: %.2f€\n", Produtos[i].id, Produtos[i].nome, Produtos[i].preco);
        }
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    getchar();
    getchar();
    return;
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