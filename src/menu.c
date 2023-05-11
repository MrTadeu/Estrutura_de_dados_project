#include "../includes/TipoDados.h"

void menu(){
    int opcao;
    do{
        int i = 0;
        printc("**************************************************\n");
        printc("***************    [blue]Menu Principal[/blue]    *************\n");
        printc("**************************************************\n");
        printc("**        [blue]%d [/blue]-> Sair                             **\n", i++);
        if(Opcoes.lojaAberta == 0){
            printc("**        [blue]%d [/blue]-> Abrir Loja                       **\n", i++);
        }
        if(Opcoes.lojaAberta == 1){
            printc("**        [blue]%d [/blue]-> Fechar Loja                      **\n", i++);
        }
        printc("**        [blue]%d [/blue]-> Configurações                    **\n", i++);
        printc("**        [blue]%d [/blue]-> Menu Clientes                    **\n", i++);
        printc("**        [blue]%d [/blue]-> Menu Funcionarios                **\n", i++);
        printc("**        [blue]%d [/blue]-> Menu Produtos                    **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver Transações                   **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver Historico                    **\n", i++);
        printc("**************************************************\n");
        printc("Qual a opção que pretende? ");
        scanf("%d", &opcao);

        i = 1;
        if (opcao == 0){
            printf("[lw]A fechar o programa...[/lw]");
        }
        if (Opcoes.lojaAberta == 0){
            if (opcao == i++){
               changeStateThreadGlobal();
            }
        }
        if (Opcoes.lojaAberta == 1){
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
        if (opcao == i++){
            menuFuncionarios();
        }
        if (opcao == i++){
            menuProdutos();
        }
        if (opcao == i++){
            editarVerTransacoes();
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
        printc("*****************    [blue]Menu Config[/blue]    **************\n");
        printc("**************************************************\n");
        if(Opcoes.threadGlobalAranque == 1){
            printc("        [red]Loja Aberta no Aranque[/red]\n");
        }
        if(Opcoes.threadGlobalAranque == 0){
            printc("        [green]Loja não é Aberta no Aranque[/green]\n");
        }
        printc("        [blue]%d[/blue] - Numero Caixas\n", Opcoes.numCaixasTotal);
        printc("        [blue]%d%%[/blue] - Probabilidade de Gerar Pessoa 1/seg\n", Opcoes.probGerarPessoa);
        printc("        [blue]%d[/blue] - Lotaçao Maxima\n", Opcoes.lotacaoMaxima);
        printc("**************************************************\n");
        printc("**        [blue]%d [/blue]-> Voltar                           **\n", i++);
        printc("**        [blue]%d [/blue]-> Editar Loja Aberta no Aranque    **\n", i++);
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
        printc("**        [blue]%d [/blue]-> Ver Clientes Inativos            **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver Clientes Ativos              **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver Clientes na Caixa            **\n", i++);
        printc("**        [blue]%d [/blue]-> Pesquisar Clientes               **\n", i++);
        printc("**        [blue]%d [/blue]-> Adicionar Cliente                **\n", i++);
        printc("**        [blue]%d [/blue]-> Editar Cliente                   **\n", i++);
        printc("**        [blue]%d [/blue]-> Remover Cliente                  **\n", i++);
        printc("**************************************************\n");
        printc("Qual a opção que pretende? ");
        scanf("%d", &opcao);

        i = 1;
        if (opcao == i++){
            verClientes();
        }
        if (opcao == i++){
            verClientesInativos();
        }
        if (opcao == i++){
            verClientesAtivos();
        }
        if (opcao == i++){
            verClientesCaixa();
        }
        if (opcao == i++){
            pesquisarClientes();
        }
        if (opcao == i++){
            adicionarCliente();
        }
        if (opcao == i++){
            editarCliente();
        }
        if (opcao == i++){
            removerCliente();
        }
    } while (opcao != 0);
}

void pesquisarClientes(){
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
        pesquisarClienteID();
        break;
    case 2:
        pesquisarClienteNome();
        break;
    default:
        break;
    }
    
}
void menuFuncionarios(){
    int opcao;
    do{
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
        /* printf("n_caixas: %d\n", Opcoes.numCaixasTotal); */
        int i = 0;
        printc("**************************************************\n");
        printc("****************   [blue]Menu Funcionário[/blue]  *************\n");
        printc("**************************************************\n");
        printc("**        [blue]%d [/blue]-> Voltar                           **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver Funcionários Inativos        **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver Funcionários em Caixa        **\n", i++);
        printc("**        [blue]%d [/blue]-> Pesquisar Funcionários           **\n", i++);
        printc("**        [blue]%d [/blue]-> Adicionar Funcionário            **\n", i++);
        printc("**        [blue]%d [/blue]-> Editar Funcionário               **\n", i++);
        printc("**        [blue]%d [/blue]-> Remover Funcionário              **\n", i++);
        /* printc("**        [blue]%d [/blue]-> Trocar Funcionário da Caixa      **\n", i++);
        printc("**        [blue]%d [/blue]-> Alterar Salários                 **\n", i++); */
        printc("**************************************************\n");
        printc("Qual a opção que pretende? ");
        scanf("%d", &opcao);

        i = 1;
        if (opcao == i++){
            verFuncionariosInativos();
        }
        if (opcao == i++){
            verFuncionariosCaixa();
        }
        if (opcao == i++){
            pesquisarFuncionarios();
        }
        if (opcao == i++){
            adicionarFuncionario();
        }
        if (opcao == i++){
            editarFuncionarios();
        }
        if (opcao == i++){
            removerFuncionario();
        }
        /* if (opcao == i++){
            trocarFuncionario();
        }
        if (opcao == i++){
            alterarSalario();
        } */
    } while (opcao != 0);
}

void pesquisarFuncionarios(){
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
        pesquisarFuncionariosID();
        break;
    case 2:
        pesquisarFuncionariosNome();
        break;
    default:
        break;
    }
    
}

void menuProdutos(){
    int opcao;
    do{
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
        int i = 0;
        printc("**************************************************\n");
        printc("****************     [blue]Menu Produto[/blue]    *************\n");
        printc("**************************************************\n");
        printc("**        [blue]%d [/blue]-> Voltar                           **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver Produtos                     **\n", i++);
        printc("**        [blue]%d [/blue]-> Pesquisar Produto                **\n", i++);
        printc("**        [blue]%d [/blue]-> Adicionar Produto                **\n", i++);
        printc("**        [blue]%d [/blue]-> Editar Produto                   **\n", i++);
        printc("**        [blue]%d [/blue]-> Remover Produto                  **\n", i++);
        printc("**************************************************\n");
        printc("Qual a opção que pretende? ");
        scanf("%d", &opcao);

        i = 1;
        if (opcao == i++){
            verProdutos();
        }
        if (opcao == i++){
            pesquisarProduto();
        }
        if (opcao == i++){
            adicionarProduto();
        }
        if (opcao == i++){
            editarProduto();
        }
        if (opcao == i++){
            removerProduto();
        }
    } while (opcao != 0);
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
