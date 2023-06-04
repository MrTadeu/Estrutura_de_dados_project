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
        printc("**        [blue]%d [/blue]-> Menu Historico                   **\n", i++);
        printc("**        [blue]%d [/blue]-> Criar Grafico                    **\n", i++);
        printc("**************************************************\n");
        scanfs("%d", &opcao, "Qual a opção que pretende? ", "Apenas pode inserir números inteiros!\n");
        
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
        if (opcao == i++){
            menuHistorico();
        }
        if (opcao == i++){
            CriarGrafico();
        }
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
    } while (opcao != 0);
}

void menuConfig(){
    int opcao;
    do{
        char TempoLimiteSuperior[9], TempoLimiteInferior[9], TempoAtrasoMaximoBrinde[9];
        formatTime(Opcoes.TempoLimiteSuperior, TempoLimiteSuperior);
        formatTime(Opcoes.TempoLimiteInferior, TempoLimiteInferior);
        formatTime(Opcoes.tempoAtrasoMaximoBrinde, TempoAtrasoMaximoBrinde);
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
        int i = 0;
        printc("************************************************************\n");
        printc("*********************    [blue]Menu Config[/blue]    ********************\n");
        printc("************************************************************\n");
        if(Opcoes.threadGlobalAranque == 1){
            printc("        [red]Loja Aberta no Arranque[/red]\n");
        }
        if(Opcoes.threadGlobalAranque == 0){
            printc("        [green]Loja não está Aberta no Arranque[/green]\n");
        }
        printc("        [blue]%d[/blue] - Número de Caixas\n", Opcoes.numCaixasTotal);
        printc("        [blue]%d%%[/blue] - Probabilidade de Gerar Pessoa 1/seg\n", Opcoes.probGerarPessoa);
        printc("        [blue]%d%%[/blue] - Probabilidade de Usar Saldo do Cartão\n", Opcoes.probUsarSaldoCartao);
        printc("        [blue]%d pessoas[/blue] -Lotação Máxima\n", Opcoes.lotacaoMaxima);
        printc("        [blue]%s[/blue] - Tempo Limite Superior por caixa\n", TempoLimiteSuperior);
        printc("        [blue]%s[/blue] - Tempo Limite Inferior por caixa\n", TempoLimiteInferior);
        printc("        [blue]%s[/blue] - Tempo de Atraso Máximo para obter o brinde\n", TempoAtrasoMaximoBrinde);
        printc("        [blue]%d[/blue] - Quantidade Mínima de Produtos por Cliente\n", Opcoes.QuantMinProd);
        printc("        [blue]%d[/blue] - Quantidade Máxima de Produtos por Cliente\n", Opcoes.QuantMaxProd);
        printc("        [blue]%d%%[/blue] - Percentagem do tempoCaixa para cálculo do atraso\n", Opcoes.percentagemParaAtraso);
        printc("        [blue]%d%%[/blue] - Bónus Funcionário = Percentagem * TempoAtraso (em segundos)\n", Opcoes.eurosPorSegundoAdiantamentoFuncinario);
        printc("        [blue]%d%%[/blue] - Percentagem do preço total a acumular no cartão\n", Opcoes.percentagemPrecoAngariarSaldo);
        printc("        [blue]%.2f[/blue] -Multiplicador de Tempo\n", Opcoes.multiplicadorTempo);
        printc("************************************************************\n");
        printc("**       [blue]%d [/blue]-> Voltar                                      **\n", i++);
        printc("**       [blue]%d [/blue]-> Editar Loja Aberta no Arranque              **\n", i++);
        printc("**       [blue]%d [/blue]-> Editar Número de Caixas                     **\n", i++);
        printc("**       [blue]%d [/blue]-> Probabilidade de Gerar Pessoa               **\n", i++);
        printc("**       [blue]%d [/blue]-> Probabilidade de Usar Saldo do Cartão       **\n", i++);
        printc("**       [blue]%d [/blue]-> Lotação Máxima                              **\n", i++);
        printc("**       [blue]%d [/blue]-> Tempo Limite Superior por caixa             **\n", i++);
        printc("**       [blue]%d [/blue]-> Tempo Limite Inferior por caixa             **\n", i++);
        printc("**       [blue]%d [/blue]-> Tempo de Atraso Máximo para obter o brinde  **\n", i++);
        printc("**       [blue]%d [/blue]-> Quantidade Mínima de Produtos por Cliente   **\n", i++);
        printc("**       [blue]%d [/blue]-> Quantidade Máxima de Produtos por Cliente   **\n", i++);
        printc("**       [blue]%d [/blue]-> Percent do tempoCaixa para cálc do atraso   **\n", i++);
        printc("**       [blue]%d [/blue]-> Bónus Funcionário = Percentagem*TempoAtraso **\n", i++);
        printc("**       [blue]%d [/blue]-> Percent do preço total a acumular no cartão **\n", i++);
        printc("**       [blue]%d [/blue]-> Multiplicador de Tempo                      **\n", i++);
        printc("************************************************************\n");
        scanfs("%d", &opcao, "Qual a opção que pretende? ", "Apenas pode inserir números inteiros!\n");

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
            editarProbUsarSaldoCartao();
        }
        if (opcao == i++){
            editarLotacaoMax();
        }
        if (opcao == i++){
            editarTempoLimiteSuperior();
        }
        if (opcao == i++){
            editarTempoLimiteInferior();
        }
        if (opcao == i++){
            editarTempoAtrasoMaximoBrinde();
        }
        if (opcao == i++){
            editarQuantMinProd();
        }
        if (opcao == i++){
            editarQuantMaxProd();
        }
        if (opcao == i++){
            editarPercTempoCaixaAtraso();
        }
        if (opcao == i++){
            editarPercBonusFuncionario();
        }
        if (opcao == i++){
            editarPercAcumularCartaoCli();
        }
        if (opcao == i++){
            menuMultiplicadorTempo();
        }
    } while (opcao != 0);
}

void menuMultiplicadorTempo(){
    int opcao;
    do{
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
        int i = 0;
        printc("Opcoes.multiplicadorTempo: %f\n", Opcoes.multiplicadorTempo);
        printc("**************************************************\n");
        printc("**********   [blue]Menu Multiplicador Tempo[/blue]    *********\n");
        printc("**************************************************\n");
        printc("**        [blue]%d [/blue]-> Voltar                           **\n", i++);
        float opcaoTempo[] = {2.0, 1.0, (float)1/2, (float)1/3, (float)1/4, (float)1/5, (float)1/6, (float)1/7, (float)1/8, (float)1/9, (float)1/10, (float)1/100};
        for (int j = 0; j < 12; j++){
            if (Opcoes.multiplicadorTempo == opcaoTempo[j]){
                if (j == 0){
                    printc("[green]**        [blue]%d [/blue]-> %.1fx                             **[/green]\n", j+1, 0.5);
                }
                else if (j == 9){
                    printc("**[green]        [blue]%d [/blue]-> %dx                              **[/green]\n", j+1, j);
                }
                else if (j == 10){
                    printc("[green]**        [blue]%d [/blue]-> %dx                             **[/green]\n", j+1, j);
                }
                else if (j == 11){
                    printc("**[green]        [blue]%d [/blue]-> %dx                            **[/green]\n", j+1, 100);
                }
                else
                    printc("[green]**        [blue]%d [/blue]-> %dx                               **[/green]\n", j+1, j);
                
            }
            else{
                if (j == 0){
                    printc("**        [blue]%d [/blue]-> %.1fx                             **\n", j+1, 0.5);
                }
                else if (j == 9){
                    printc("**        [blue]%d [/blue]-> %dx                              **\n", j+1, j);
                }
                else if (j == 11){
                    printc("**        [blue]%d [/blue]-> %dx                            **\n", j+1, 100);
                }
                
                else
                    j < 9 ? printc("**        [blue]%d [/blue]-> %dx                               **\n", j+1, j) : printc("**        [blue]%d [/blue]-> %dx                             **\n", j+1, j);

            }
        }
        scanfv("%d", &opcao, "Qual a opção que pretende? ", "Apenas pode inserir números entre (0 - 12)!\n", validateRange, 0, 12);

        for (int i = 0; i < 12; i++){
            if (opcao == i+1){
                printf("opcaoTempo[%d] = %f\n", i, opcaoTempo[i]);
                Opcoes.multiplicadorTempo = opcaoTempo[i];
            }
        }
        /* printf("O multiplicador de tempo foi alterado para %fx, Opçoes %d\n", Opcoes.multiplicadorTempo, opcao); */
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
        printc("**        [blue]%d [/blue]-> Ver Todos Clientes               **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver Clientes Inativos            **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver Clientes na Loja             **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver Clientes na Caixa (alterar)  **\n", i++);
        printc("**        [blue]%d [/blue]-> Pesquisar Clientes               **\n", i++);
        printc("**        [blue]%d [/blue]-> Adicionar Cliente                **\n", i++);
        printc("**        [blue]%d [/blue]-> Editar Cliente                   **\n", i++);
        printc("**        [blue]%d [/blue]-> Remover Cliente                  **\n", i++);
        printc("**        [blue]%d [/blue]-> Pesquisar Cliente Em Caixa       **\n", i++);
        printc("**************************************************\n");
        scanfs("%d", &opcao, "Qual a opção que pretende? ", "Apenas pode inserir números inteiros!\n");

        i = 1;
        if (opcao == i++){
            verClientes();
        }
        if (opcao == i++){
            verClientesInativos();
        }
        if (opcao == i++){
            verClientesEmLoja();
        }
        if (opcao == i++){
            verClientesCaixa();
        }
        if (opcao == i++){
            menuPesquisarClientes();
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
        if (opcao == i++){
            verSeClienteEspecificoEmCaixa();
        }
    } while (opcao != 0);
}

void menuPesquisarClientes(){
    int opcao;
    do{
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
        int i = 0;
        printc("**************************************************\n");
        printc("****************    [blue]Menu Clientes[/blue]    *************\n");
        printc("**************************************************\n");
        printc("**        [blue]%d [/blue]-> Voltar                           **\n", i++);
        printc("**        [blue]%d [/blue]-> Pesquisar por ID                 **\n", i++);
        printc("**        [blue]%d [/blue]-> Pesquisar por nome               **\n", i++);
        printc("**************************************************\n");
        scanfs("%d", &opcao, "Qual a opção que pretende? ", "Apenas pode inserir números inteiros!\n");

        i = 1;
        if (opcao == i++){
            pesquisarClienteID();
        }
        if (opcao == i++){
            pesquisarClienteNome();
        }
    } while (opcao != 0);
}

void menuFuncionarios(){
    int opcao;
    do{
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
        int i = 0;
        printc("**************************************************\n");
        printc("****************   [blue]Menu Funcionário[/blue]  *************\n");
        printc("**************************************************\n");
        printc("**        [blue]%d [/blue]-> Voltar                           **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver Todos Funcionários           **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver Funcionários Inativos        **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver Funcionários em Caixa        **\n", i++);
        printc("**        [blue]%d [/blue]-> Pesquisar Funcionários           **\n", i++);
        printc("**        [blue]%d [/blue]-> Adicionar Funcionário            **\n", i++);
        printc("**        [blue]%d [/blue]-> Editar Funcionário               **\n", i++);
        printc("**        [blue]%d [/blue]-> Remover Funcionário              **\n", i++);
        /* printc("**        [blue]%d [/blue]-> Trocar Funcionário da Caixa      **\n", i++);*/
        printc("**************************************************\n");
        scanfs("%d", &opcao, "Qual a opção que pretende? ", "Apenas pode inserir números inteiros!\n");

        i = 1;
        if (opcao == i++){
            verFuncionarios();
        }
        if (opcao == i++){
            verFuncionariosInativos();
        }
        if (opcao == i++){
            verFuncionariosCaixa();
        }
        if (opcao == i++){
            menuPesquisarFuncionarios();
        }
        if (opcao == i++){
            fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
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

void menuPesquisarFuncionarios(){
    int opcao;
    do{
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
        int i = 0;
        printc("**************************************************\n");
        printc("****************   [blue]Menu Funcionário[/blue]  *************\n");
        printc("**************************************************\n");
        printc("**        [blue]%d [/blue]-> Voltar                           **\n", i++);
        printc("**        [blue]%d [/blue]-> Pesquisar por ID                 **\n", i++);
        printc("**        [blue]%d [/blue]-> Pesquisar por nome               **\n", i++);
        printc("**************************************************\n");
        scanfs("%d", &opcao, "Qual a opção que pretende? ", "Apenas pode inserir números inteiros!\n");

        i = 1;
        if (opcao == i++){
            pesquisarFuncionariosID();
        }
        if (opcao == i++){
            pesquisarFuncionariosNome();
        }
    } while (opcao != 0);
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
        scanfs("%d", &opcao, "Qual a opção que pretende? ", "Apenas pode inserir números inteiros!\n");

        i = 1;
        if (opcao == i++){
            verProdutos();
        }
        if (opcao == i++){
            menuPesquisarProduto();
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

void menuPesquisarProduto(){
    int opcao = 0;
    do{
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
        printc("[blue]0[/blue] - Voltar\n");
        printc("[blue]1[/blue] - Pesquisar por ID\n");
        printc("[blue]2[/blue] - Pesquisar por nome\n");
        scanfs("%d", &opcao, "Qual a opção que pretende? ", "Apenas pode inserir números inteiros!\n");
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

void menuHistorico(){
    int opcao;
    do{
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
        int i = 0;
        printc("**************************************************\n");
        printc("****************     [blue]Menu Produto[/blue]    *************\n");
        printc("**************************************************\n");
        printc("**        [blue]%d [/blue]-> Voltar                           **\n", i++);
        printc("**        [blue]%d [/blue]-> Mostrar Histórico                **\n", i++);
        printc("**        [blue]%d [/blue]-> Pesquisar Cliente                **\n", i++);
        printc("**        [blue]%d [/blue]-> Pesquisar Caixa                  **\n", i++);
        printc("**        [blue]%d [/blue]-> Ver dados estatísticos           **\n", i++);
        printc("**************************************************\n");
        scanfs("%d", &opcao, "Qual a opção que pretende? ", "Apenas pode inserir números inteiros!\n");

        i = 1;
        if (opcao == i++){
            mostrarHistorico();
        }
        if (opcao == i++){
            pesquisarClienteNoHistorico();
        }
        if (opcao == i++){
            pesquisarCaixaNoHistorico();
        }
        if(opcao == i++){
            recolhaDadosEstatisticosHistoricoTransacoes();
            printf("olaaaaa");
            calculosRecolhas();
            printf("olaaaaa");
            destruirHistoricos();
            printf("olaaaaa");
            getchar();
            getchar();
        }
    } while (opcao != 0);
}


int menuvalidarCaixaFuncionarios(){
    if( n_funcionarios < Opcoes.numCaixasTotal){
        int opcao;
        do{
            fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
            int i = 1;
            printc("\n[yellow]AVISO:[/yellow] Não existem funcionários suficientes para todas as caixa! \nQuando o limite de funcionários for atingido não poderão ser abertas mais caixas automaticamente. \nPara resolver isso contrate mais funcionários, ou diminua número de caixas totais!\n\n");
            printc("**************************************************\n");
            printc("**        [blue]%d [/blue]-> Abrir Loja                       **\n", i++);
            printc("**        [blue]%d [/blue]-> Fechar Loja                      **\n", i++);
            printc("**        [blue]%d [/blue]-> Resolver Problema                **\n", i++);
            printc("**************************************************\n");
            scanfs("%d", &opcao, "Qual a opção que pretende? ", "Apenas pode inserir números inteiros!\n");

            i = 1;
            if (opcao == i++){
                opcao = 0;
            }
            if (opcao == i++){
                return 0;
            }
            if (opcao == i++){
                if(menuResolverCaixaFuncionario() != -1){
                    opcao = 0;
                }
            }
        } while (opcao != 0);
    }
    return 1;
}

int menuResolverCaixaFuncionario(){
    int opcao;
    do{
        fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
        int i = 1;
        printc("************************************************************\n");
        printc("****************     [blue]Menu Resolver Problema[/blue]    *************\n");
        printc("************************************************************\n");
        printc("**        [blue]%d [/blue]-> Voltar                                     **\n", i++);
        printc("**        [blue]%d [/blue]-> Adicionar Funcionarios necessarios         **\n", i++);
        printc("**        [blue]%d [/blue]-> Remover Caixas necessarias                 **\n", i++);
        printc("************************************************************\n");
        scanfs("%d", &opcao, "Qual a opção que pretende? ", "Apenas pode inserir números inteiros!\n");

        i = 1;
        if (opcao == i++){
            return -1;
        }
        if (opcao == i++){
            for(int i = n_funcionarios; i < Opcoes.numCaixasTotal; i++){
                fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
                printc("\nFaltam [red]%d[/red]\n\n", Opcoes.numCaixasTotal - i);
                adicionarFuncionario();
                opcao = 0;
                fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
            }
        }
        if (opcao == i++){
                fputs("\x1b[H\x1b[2J\x1b[3J", stdout);
                removerCaixa();
                opcao = 0;
        }
    } while (opcao != 0);
    return 1;
}