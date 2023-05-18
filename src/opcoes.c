#include "../includes/TipoDados.h"

void Init(){
    setPortugues();
    importOpcoes();
    importarDados(importarClientes, CLIENTES);
    importarDados(importarFuncionarios, FUNCIONARIOS);
    importarDados(importarProdutos, PRODUTOS);
    criarCaixaInit();
    initHistorico();
    if(Opcoes.threadGlobalAranque == 1){
        changeStateThreadGlobal();
    }
}

void closeAll(){
    exportarOpcoes();
    exportarDados(guardarClienteTxt, CLIENTES);
    exportarDados(guardarFuncionarioTxt, FUNCIONARIOS);
    exportarDados(guardarProdutoTxt, PRODUTOS);
    //pensar quando é fechado o programa fazer oq com as caixas abertas/ therad global / thread tcompra
}

void editarLojaAbertaAranque(){
    
    int n;
    int invalid = 0;
    do{
        printc("\n\t[blue]Deseja que a loja esteja aberta no aranque? (0-NÃO OU 1-SIM)[/blue] ");
        invalid = scanf("%d", &n);
        invalid != 1 ? printf("Apenas pode inserir números inteiros!\n"),  bufferclear() : (void)NULL;
    }while(invalid != 1);

    if(n == 0 || n == 1){
        Opcoes.threadGlobalAranque = n;
        if(n == 0){
            printc("\n[green]A loja não vai estar aberta no aranque[/green]");
        }
        else{
            printc("\n[green]A loja vai estar aberta no aranque[/green]");
        }
    }
    else{
        printf("\n[red]A opção tem de ser 0 ou 1![/red]");
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarNumCaixas(){
    
    int n;
    int invalid = 0;
    do{
        printf("\n\t[blue]Quantos caixas deseja ter?[/blue] ");
        invalid = scanf("%d", &n);
        invalid != 1 ? printf("Apenas pode inserir números inteiros!\n"),  bufferclear() : (void)NULL;
    }while(invalid != 1);

    if(n > 0 && n <= 50){
        Opcoes.numCaixasTotal = n;
        printc("\n[green]O número de caixas foi alterado para %d[/green]", n);
    }
    else{
        printf("\n[red]O número de caixas tem de ser maior que 0 e menor que 50![/red]");
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarProbGerarPessoa(){
    
    int n;
    int invalid = 0;
    do{
        printf("\n\t[blue]Qual a probabilidade de gerar uma pessoa?[/blue] ");
        invalid = scanf("%d", &n);
        invalid != 1 ? printf("Apenas pode inserir números inteiros!\n"),  bufferclear() : (void)NULL;
    }while(invalid != 1);

    if(n > 0 && n <= 100){
        Opcoes.probGerarPessoa = n;
        printc("\n[green]A probabilidade foi alterada para %d%%[/green]", n);
    }
    else{
        printf("\n[red]A probabilidade tem de ser maior que 0%% e menor que 100%%![/red]");
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();

}

void editarLotacaoMax(){
    int n;
    int invalid = 0;
    do{
        printf("\n\t[blue]Qual a lotação máxima da loja?[/blue] ");
        invalid = scanf("%d", &n);
        invalid != 1 ? printf("Apenas pode inserir números inteiros!\n"),  bufferclear() : (void)NULL;
    }while(invalid != 1);
    if(n > 0 && n <= 1000){
        Opcoes.lotacaoMaxima = n;
        printc("\n[green]A lotação máxima foi alterada para %d[/green]", n);
    }
    else{
        printf("\n[red]A lotação máxima tem de ser maior que 0 e menor que 1000![/red]");
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarVerTransacoes(){
    if(Opcoes.lojaAberta == 1){
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
        printc("[yellow]Pressione qualquer tecla para [red]PARAR[/red] de ver as transações![/yellow]");
        printc("\n[yellow]Pressione qualquer tecla para [red]PARAR[/red] de ver as transações![/yellow]");
        printc("\n[yellow]Pressione qualquer tecla para [red]PARAR[/red] de ver as transações![/yellow]");
        printc("\n[yellow]Pressione qualquer tecla para [red]PARAR[/red] de ver as transações![/yellow]");
        printc("\n[yellow]Pressione qualquer tecla para [red]PARAR[/red] de ver as transações![/yellow]\n\n");
        Opcoes.VerTransacoes = 1;
        bufferclear();
        getchar();
        Opcoes.VerTransacoes = 0;
    }
    else{
        printc("\n[red]A loja tem de estar aberta para ver as transações![/red]");
        printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
        bufferclear();
        getchar();
    }
}