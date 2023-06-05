#include "../includes/TipoDados.h"

void Init(){
    setPortugues();
    importOpcoes();
    importarDados(importarClientes, CLIENTES);
    importarDados(importarFuncionarios, FUNCIONARIOS);
    importarDados(importarProdutos, PRODUTOS);
    criarCaixaInit();
    initHistoricoTransacoes();
    /* initHistoricoDadosEstatisticos(); */
    checkIFfileExists("Historico") == 0 ? system("mkdir Historico") : (void)NULL;
    if (Opcoes.threadGlobalAranque == 1)
    {
        changeStateThreadGlobal();
    }
}

void closeAll(){
    exportarOpcoes();
    exportarDados(guardarClienteTxt, CLIENTES);
    exportarDados(guardarFuncionarioTxt, FUNCIONARIOS);
    exportarDados(guardarProdutoTxt, PRODUTOS);
}

void editarLojaAbertaAranque(){
    int n;
    scanfv("%d", &n, "\tDeseja que a loja esteja aberta no aranque? (0-NÃO OU 1-SIM)", "A opção tem de ser 0 ou 1!", validateRange, 0, 1);
    Opcoes.threadGlobalAranque = n;
    if (n == 0)
    {
        printc("\n[green]A loja não vai estar aberta no aranque[/green]");
    }
    else
    {
        printc("\n[green]A loja vai estar aberta no aranque[/green]");
    }
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    exportarOpcoesInsta();
}

void editarNumCaixas(){
    int n, option;
    scanfv("%d", &n, "Quantos caixas deseja ter? ", "O número de caixas tem de ser maior que 1 e menor que 50!", validateRange, 1, numeroMaximoCaixasPossivel);
    Opcoes.numCaixasTotal = n;
    if (Opcoes.numCaixasTotal > n)
    {
        Elemento *caixa = Global.caixas->head;
        int i = 0;

        scanfv("%d", &option, "\nQuer remover caixas em funcionamento. Pretende fecha-las com ou sem urgência? (1 --> sem urgência | 2 --> com urgência)", "(1 --> sem urgência | 2 --> com urgência)", validateRange, 1, 2);
        while (caixa)
        {
            CaixaStruct *caixaInfo = (CaixaStruct *)caixa->Info;
            if (i++ >= Opcoes.numCaixasTotal)
            {
                if (option == 1)
                    caixaInfo->aberta = 0;
                else
                    caixaInfo->fecharUrgencia = 1;
            }
            caixa = caixa->next;
        }
    }

    printc("\n[green]O número de caixas foi alterado para %d[/green]", n);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    exportarOpcoesInsta();
}

void editarProbGerarPessoa(){
    int n;
    scanfv("%d", &n, "Qual a probabilidade de gerar uma pessoa: ", "A probabilidade tem de ser maior que 0\% e menor que 100\%!\n", validateRange, 0, 100);
    Opcoes.probGerarPessoa = n;
    printc("\n[green]A probabilidade foi alterada para %d%%[/green]", n);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    exportarOpcoesInsta();
}

void editarLotacaoMax(){
    int n;
    scanfv("%d", &n, "Qual a lotação máxima da loja: ", "A lotação máxima tem de ser maior que 0 e menor que 1000!\n", validateRange, 0, 1000);
    Opcoes.lotacaoMaxima = n;
    printc("\n[green]A lotação máxima foi alterada para %d[/green]", n);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    exportarOpcoesInsta();
}

void editarProbUsarSaldoCartao(){
    int n;
    scanfv("%d", &n, "Qual a probabilidade de usar Saldo do Cartao: ", "Número invalido 0\%-100\%!\n", validateRange, 0, 100);
    Opcoes.probUsarSaldoCartao = n;
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    exportarOpcoesInsta();
}

void editarTempoLimiteSuperior(){
    float min;
    scanfv("%f", &min, "Qual o tempo limite superior (min): ", "O tempo limite superior tem de ser maior que 1 min e menor que 600 min!\n", validateRangeFloat, 1.0, 600.0);
    Opcoes.TempoLimiteSuperior = (int)min * 60 * 1000;
    char TempoLimiteSuperior[9];
    formatTime(Opcoes.TempoLimiteSuperior, TempoLimiteSuperior);
    printc("\n[green]O tempo limite superior foi alterado para %s[/green]", TempoLimiteSuperior);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    exportarOpcoesInsta();
}

void editarTempoLimiteInferior(){
    float min;
    scanfv("%f", &min, "Qual o tempo limite inferior (min): ", "O tempo limite inferior tem de ser maior que 1 min e menor que 600 min!\n", validateRangeFloat, 1.0, 600.0);
    Opcoes.TempoLimiteInferior = (int)min * 60 * 1000;
    char TempoLimiteInferior[9];
    formatTime(Opcoes.TempoLimiteInferior, TempoLimiteInferior);
    printc("\n[green]O tempo limite inferior foi alterado para %s[/green]", TempoLimiteInferior);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    exportarOpcoesInsta();
}

void editarTempoAtrasoMaximoBrinde(){
    float min;
    scanfv("%f", &min, "Qual o tempo de atraso máximo para ganhar um brinde (min): ", "O tempo de atraso máximo para ganhar um brinde tem de ser maior que 1 min e menor que 600 min!\n", validateRangeFloat, 1.0, 600.0);
    Opcoes.tempoAtrasoMaximoBrinde = (int)min * 60 * 1000;
    char tempoAtrasoMaximoBrinde[9];
    formatTime(Opcoes.tempoAtrasoMaximoBrinde, tempoAtrasoMaximoBrinde);
    printc("\n[green]O tempo de atraso máximo para ganhar um brinde foi alterado para %s[/green]", tempoAtrasoMaximoBrinde);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    exportarOpcoesInsta();
}

void editarQuantMinProd(){
    int n;
    scanfv("%d", &n, "Qual a quantidade mínima de produtos: ", "A quantidade mínima de produtos tem de ser maior que 0 e menor que 1000!\n", validateRange, 0, 1000);
    Opcoes.QuantMinProd = n;
    printc("\n[green]A quantidade mínima de produtos foi alterada para %d[/green]", n);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    exportarOpcoesInsta();
}

void editarPercTempoCaixaAtraso(){
    int n;
    scanfv("%d", &n, "Qual a percentagem de tempo de atraso do caixa: ", "A percentagem de tempo de atraso do caixa tem de ser maior que 0\% e menor que 100\%!\n", validateRange, 0, 100);
    Opcoes.percentagemParaAtraso = n;
    printc("\n[green]A percentagem de tempo de atraso do caixa foi alterada para %d%%[/green]", n);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    exportarOpcoesInsta();
}

void editarPercBonusFuncionario(){
    int n;
    scanfv("%d", &n, "Qual a percentagem de bonus para funcionários: ", "A percentagem de bonus para funcionários tem de ser maior que 0\% e menor que 100\%!\n", validateRange, 0, 100);
    Opcoes.eurosPorSegundoAdiantamentoFuncinario = n;
    printc("\n[green]A percentagem de bonus para funcionários foi alterada para %d%%[/green]", n);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    exportarOpcoesInsta();
}

void editarPercAcumularCartaoCli(){
    int n;
    scanfv("%d", &n, "Qual a percentagem de acumulação de saldo do cartão de cliente: ", "A percentagem de acumulação de saldo do cartão de cliente tem de ser maior que 0\% e menor que 10\%!\n", validateRange, 0, 10);
    Opcoes.percentagemPrecoAngariarSaldo = n;
    printc("\n[green]A percentagem de acumulação de saldo do cartão de cliente foi alterada para %d%%[/green]", n);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    exportarOpcoesInsta();
}

void editarQuantMaxProd(){
    int n;
    scanfv("%d", &n, "Qual a quantidade máxima de produtos: ", "A quantidade máxima de produtos tem de ser maior que 0 e menor que 1000!\n", validateRange, 0, 1000);
    Opcoes.QuantMaxProd = n;
    printc("\n[green]A quantidade máxima de produtos foi alterada para %d[/green]", n);
    printc("\n\n[yellow]Pressione qualquer tecla para continuar...[/yellow]");
    bufferclear();
    getchar();
    exportarOpcoesInsta();
}


void editarVerTransacoes(){
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

void fechamentoLoja(){
    Opcoes.lojaAberta = 0;
    printc("[green]A atender os ultimos clientes. Por favor aguarde...[/green]");
   /*  while(n_clientesAtivos){
        dormir(50);
    } */
    /* destruirLista(Global.caixas, destruirCaixa); // free area das caixas
    free(Global.PessoasAcabaramTempoDeCompra);
    exportarHistoricoTransacoesParaTXT("teste"); //!FALTA NOME FICHEIRO
    exportarHistoricoTransacoesParaCSV("teste"); //!FALTA NOME FICHEIRO
    destruirHistoricoTransacoes(HistoricoDados.HistoricoTransacoes);
    destruirHistoricoDadosEstatisticos();
    
    for (int i = 0; i < n_clientes; i++) // free vetor clientes
        free(Clientes[i]);
    free(Clientes);

    for (int i = 0; i < n_funcionarios; i++) // free vetor funcionarios
        free(Funcionarios[i]);
    free(Funcionarios);

    free(Produtos) */; // free vetor produtos
}

