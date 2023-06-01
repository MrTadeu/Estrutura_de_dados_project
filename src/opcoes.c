#include "../includes/TipoDados.h"

void Init(){
    setPortugues();
    importOpcoes();
    importarDados(importarClientes, CLIENTES);
    importarDados(importarFuncionarios, FUNCIONARIOS);
    importarDados(importarProdutos, PRODUTOS);
    criarCaixaInit();
    checkIFfileExists("Historico") == 0 ? system("mkdir Historico") : (void)NULL;
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
    scanfv("%d", &n, "\tDeseja que a loja esteja aberta no aranque? (0-NÃO OU 1-SIM)", "A opção tem de ser 0 ou 1!", validateRange, 0, 1);
    Opcoes.threadGlobalAranque = n;
    if(n == 0){
        printc("\n[green]A loja não vai estar aberta no aranque[/green]");
    }
    else{
        printc("\n[green]A loja vai estar aberta no aranque[/green]");
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarNumCaixas(){
    int n;
    scanfv("%d", &n, "Quantos caixas deseja ter? ", "O número de caixas tem de ser maior que 1 e menor que 50!", validateRange, 1, 50);
    Opcoes.numCaixasTotal = n;
    printc("\n[green]O número de caixas foi alterado para %d[/green]", n);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarProbGerarPessoa(){
    int n;
    scanfv("%d", &n, "Qual a probabilidade de gerar uma pessoa: ", "A probabilidade tem de ser maior que 0\% e menor que 100\%!\n", validateRange, 0, 100);
    Opcoes.probGerarPessoa = n;
    printc("\n[green]A probabilidade foi alterada para %d%%[/green]", n);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarLotacaoMax(){
    int n;
    scanfv("%d", &n, "Qual a lotação máxima da loja: ", "A lotação máxima tem de ser maior que 0 e menor que 1000!\n", validateRange, 0, 1000);
    Opcoes.lotacaoMaxima = n;
    printc("\n[green]A lotação máxima foi alterada para %d[/green]", n);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarProbUsarSaldoCartao(){
    int n;
    scanfv("%d", &n, "Qual a probabilidade de usar Saldo do Cartao: ", "Número invalido 0\%-100\%!\n", validateRange, 0, 100);
    Opcoes.probUsarSaldoCartao = n;
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarTempoLimiteSuperior(){
    float min;
    scanfv("%f", &min, "Qual o tempo limite superior (min): ", "O tempo limite superior tem de ser maior que 1 min e menor que 600 min!\n", validateRangeFloat, 1.0, 600.0);
    Opcoes.TempoLimiteSuperior = (int) min*60*1000;
    char TempoLimiteSuperior[9];
    formatTime(Opcoes.TempoLimiteSuperior, TempoLimiteSuperior);
    printc("\n[green]O tempo limite superior foi alterado para %s[/green]", TempoLimiteSuperior);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarTempoLimiteInferior(){
    float min;
    scanfv("%f", &min, "Qual o tempo limite inferior (min): ", "O tempo limite inferior tem de ser maior que 1 min e menor que 600 min!\n", validateRangeFloat, 1.0, 600.0);
    Opcoes.TempoLimiteInferior = (int) min*60*1000;
    char TempoLimiteInferior[9];
    formatTime(Opcoes.TempoLimiteInferior, TempoLimiteInferior);
    printc("\n[green]O tempo limite inferior foi alterado para %s[/green]", TempoLimiteInferior);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarTempoAtrasoMaximoBrinde(){
    float min;
    scanfv("%f", &min, "Qual o tempo de atraso máximo para ganhar um brinde (min): ", "O tempo de atraso máximo para ganhar um brinde tem de ser maior que 1 min e menor que 600 min!\n", validateRangeFloat, 1.0, 600.0);
    Opcoes.tempoAtrasoMaximoBrinde = (int) min*60*1000;
    char tempoAtrasoMaximoBrinde[9];
    formatTime(Opcoes.tempoAtrasoMaximoBrinde, tempoAtrasoMaximoBrinde);
    printc("\n[green]O tempo de atraso máximo para ganhar um brinde foi alterado para %s[/green]", tempoAtrasoMaximoBrinde);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarQuantMinProd(){
    int n;
    scanfv("%d", &n, "Qual a quantidade mínima de produtos: ", "A quantidade mínima de produtos tem de ser maior que 0 e menor que 1000!\n", validateRange, 0, 1000);
    Opcoes.QuantMinProd = n;
    printc("\n[green]A quantidade mínima de produtos foi alterada para %d[/green]", n);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarPercTempoCaixaAtraso(){
    int n;
    scanfv("%d", &n, "Qual a percentagem de tempo de atraso do caixa: ", "A percentagem de tempo de atraso do caixa tem de ser maior que 0\% e menor que 100\%!\n", validateRange, 0, 100);
    Opcoes.percentagemParaAtraso = n;
    printc("\n[green]A percentagem de tempo de atraso do caixa foi alterada para %d%%[/green]", n);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarPercBonusFuncionario(){
    int n;
    scanfv("%d", &n, "Qual a percentagem de bonus para funcionários: ", "A percentagem de bonus para funcionários tem de ser maior que 0\% e menor que 100\%!\n", validateRange, 0, 100);
    Opcoes.eurosPorSegundoAdiantamentoFuncinario = n;
    printc("\n[green]A percentagem de bonus para funcionários foi alterada para %d%%[/green]", n);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarPercAcumularCartaoCli(){
    int n;
    scanfv("%d", &n, "Qual a percentagem de acumulação de saldo do cartão de cliente: ", "A percentagem de acumulação de saldo do cartão de cliente tem de ser maior que 0\% e menor que 10\%!\n", validateRange, 0, 10);
    Opcoes.percentagemPrecoAngariarSaldo = n;
    printc("\n[green]A percentagem de acumulação de saldo do cartão de cliente foi alterada para %d%%[/green]", n);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

void editarQuantMaxProd(){
    int n;
    scanfv("%d", &n, "Qual a quantidade máxima de produtos: ", "A quantidade máxima de produtos tem de ser maior que 0 e menor que 1000!\n", validateRange, 0, 1000);
    Opcoes.QuantMaxProd = n;
    printc("\n[green]A quantidade máxima de produtos foi alterada para %d[/green]", n);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
}

/* void editarMultiplicadorTempo(){
    float n;
    scanfv("%f", &n, "Qual o multiplicador de tempo: ", "O multiplicador de tempo tem de ser maior que 0 e menor que 100!\n", validateRangeFloat, 0.0, 100.0);
    Opcoes.multiplicadorTempo = n;
    printc("\n[green]O multiplicador de tempo foi alterado para %.2f[/green]", n);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
} */

void editarVerTransacoes(){
    if(Opcoes.lojaAberta == 1 /* || TRUE */){
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

