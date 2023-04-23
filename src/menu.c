#include "../includes/TipoDados.h"

void menu(){
    int opcao;
    do{
        int j = 0;
        printf("**************************************************\n");
        printf("***************    Menu Principal    *************\n");
        printf("**************************************************\n");
        printf("**        [blue]%d [/blue]-> Sair                             **\n", j++);
        printf("**        [blue]%d [/blue]-> Configurações                    **\n", j++);
        printf("**        [blue]%d [/blue]-> Menu Funcionarios                **\n", j++);
        printf("**        [blue]%d [/blue]-> Ver Historico                    **\n", j++);
        printf("**************************************************\n");
        printf("Qual a opção que pretende? ");
        scanf("%d", &opcao);

        switch (opcao){
            case 0:
                printf("A sair...\n");
                break;
            case 1:
                /* menuConfiguracoes(); */
                break;
            case 2:
                /* menuFuncionarios(); */
                break;
            case 3:
                /* menuHistorico(); */
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);
    
}








