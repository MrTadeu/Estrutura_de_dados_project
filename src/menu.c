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
            printc("**        [blue]%d [/blue]-> Abrir Loja                             **\n", i++);
        }
        else if(Global.lojaAberta == 1){
            printc("**        [blue]%d [/blue]-> Fechar Loja                             **\n", i++);
        }
        printc("**        [blue]%d [/blue]-> Configurações                    **\n", i++);
        printc("**        [blue]%d [/blue]-> Menu Clientes                **\n", i++);
        printc("**        [blue]%d [/blue]-> Menu Funcionarios                **\n", i++);
        printc("**        [blue]%d [/blue]-> Menu Produtos                **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver Transações                **\n", i++);
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
                criarExame();
            }
        }
        if (Global.lojaAberta == 1){
            if (opcao == i++){
                inscreverExame();
            }
        }
    } while (opcao != 0);
    








}