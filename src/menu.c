#include "../includes/TipoDados.h"

void menu(){
    do{
        int opcao, j = 0;
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

        j = 0;
        switch (opcao){
            case j++:
                printf("A sair...\n");
                break;
            case j++:
                /* menuConfiguracoes(); */
                break;
            case j++:
                /* menuFuncionarios(); */
                break;
            case j++:
                /* menuHistorico(); */
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);
    
}








