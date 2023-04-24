#include "../includes/TipoDados.h"

void menu(){
    int opcao;
    do{
        int i = 0;
        printc("**************************************************\n");
        printc("***************    [blue]Menu Principal[/blue]    *************\n");
        printc("**************************************************\n");
        printc("**        [blue]%d [/blue]-> Sair                             **\n", i++);
        if(Global.lojaAberta == 0){
            printc("**        [blue]%d [/blue]-> Abrir Loja                       **\n", i++);
        }
        if(Global.lojaAberta == 1){
            printc("**        [blue]%d [/blue]-> Fechar Loja                      **\n", i++);
        }
        printc("**        [blue]%d [/blue]-> Configurações                  **\n", i++);
        printc("**        [blue]%d [/blue]-> Menu Clientes                    **\n", i++);
        printc("**        [blue]%d [/blue]-> Menu Funcionarios                **\n", i++);
        printc("**        [blue]%d [/blue]-> Menu Produtos                    **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver Transações                 **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver Historico                    **\n", i++);
        printc("**************************************************\n");
        printc("Qual a opção que pretende? ");
        scanf("%d", &opcao);

        i = 1;
        if (opcao == 0){
            printf("[lw]A fechar o programa...[/lw]");
        }
        if (Global.lojaAberta == 0){
            if (opcao == i++){
               changeStateThreadGlobal();
            }
        }
        if (Global.lojaAberta == 1){
            if (opcao == i++){
                changeStateThreadGlobal();
            }
        }
        if (opcao == i++){
            menuConfig();
        }
        if (opcao == i++){
            menuClientes();
        }
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    } while (opcao != 0);
}

void menuConfig(){
    int opcao;
    do{
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
        int i = 0;
        printc("**************************************************\n");
        printc("****************    [blue]Menu Config[/blue]    *************\n");
        printc("**************************************************\n");
        if(Global.threadGlobalAranque == 1){
            printc("        [red]Loja Aberta no Aranque[/red]\n");
        }
        if(Global.threadGlobalAranque == 0){
            printc("        [green]Loja não é Aberta no Aranque[/green]\n");
        }
        printc("        [blue]%d[/blue] - Numero Caixas\n", Global.numCaixasTotal);
        printc("        [blue]%d%%[/blue] - Probabilidade de Gerar Pessoa 1/seg\n", Global.probGerarPessoa);
        printc("        [blue]%d[/blue] - Lotaçao Maxima\n", Global.lotacaoMaxima);
        printc("**************************************************\n");
        printc("**        [blue]%d [/blue]-> Voltar                           **\n", i++);
        printc("**        [blue]%d [/blue]-> Editar Loja Aberta no Aranque     **\n", i++);
        printc("**        [blue]%d [/blue]-> Editar Numero Caixas             **\n", i++);
        printc("**        [blue]%d [/blue]-> Probabilidade de Gerar Pessoa    **\n", i++);
        printc("**        [blue]%d [/blue]-> Lotaçao Maxima                  **\n", i++);
        printc("**************************************************\n");
        printc("Qual a opção que pretende? ");
        scanf("%d", &opcao);

        i = 1;
        if (opcao == i++){
            editarLojaAbertaAranque();
        }
        if (opcao == i++){
            editarNumCaixas();
        }
        if (opcao == i++){
            editarProbGerarPessoa();
        }
        if (opcao == i++){
            editarLotacaoMax();
        }
    } while (opcao != 0);
}

void menuClientes(){
    int opcao;
    do{
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
        int i = 0;
        printc("**************************************************\n");
        printc("****************    [blue]Menu Clientes[/blue]    *************\n");
        printc("**************************************************\n");
        printc("**        [blue]%d [/blue]-> Voltar                           **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver Clientes                     **\n", i++);
        printc("**        [blue]%d [/blue]-> Pesquisar Clientes               **\n", i++);
        printc("**        [blue]%d [/blue]-> Adicionar Cliente                **\n", i++);
        printc("**        [blue]%d [/blue]-> Editar Cliente                   **\n", i++);
        printc("**        [blue]%d [/blue]-> Remover Cliente                  **\n", i++);
        printc("**************************************************\n");
        printc("Qual a opção que pretende? ");
        scanf("%d", &opcao);

        i = 1;
        if (opcao == 0){
        }
        if (opcao == i++){
            verClientes();
        }
        if (opcao == i++){
        }
    } while (opcao != 0);
}