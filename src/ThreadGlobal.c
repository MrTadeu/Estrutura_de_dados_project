#include "../includes/TipoDados.h"

void *ThreadGlobal(){
    pthread_mutex_init(&PessoasAcabaramTempoDeCompraLock, NULL);
    pthread_mutex_init(&ClientesLock, NULL);
    pthread_mutex_init(&FuncionariosLock, NULL);
    pthread_mutex_init(&HistoricoDados.HistoricoTransacoesLock, NULL);

    while(n_clientesAtivos || Opcoes.lojaAberta == 1){
        if (Aleatorio(0, 100) <= Opcoes.probGerarPessoa && Opcoes.lojaAberta == 1 && Opcoes.lotacaoMaxima >= Global.n_pessoasEmLoja){ //Gerar, simular tempo de compra e inserir pessoa na fila da melhor caixa
            ClienteStruct *pessoa = escolherCliente();
            
            if(pessoa){
                if(Opcoes.VerTransacoes == 1){
                    char tempoEstimadoCompra[9], tempoEstimadoCaixa[9];
                    formatTime(pessoa->tempoEstimadoCompra, tempoEstimadoCompra);
                    formatTime(pessoa->tempoEstimadoCaixa, tempoEstimadoCaixa);
                    if (Opcoes.VerTransacoes){
                        printc("\n\n[yellow]Pessoa Gerada:[/yellow] \n Nome: [blue]%s[/blue] \n Tempo de Compra: [green]%s[/green] \n Tempo de Estimado Caixa: [green]%s[/green]\n",  pessoa->nome, tempoEstimadoCompra, tempoEstimadoCaixa);
                    }
                }
                pthread_t thread;
                pthread_create(&thread, NULL, ThreadEsperaTempoCompra, (void *)pessoa);
                pthread_detach(thread);
            }
            
        }
        SelecionarCaixa();
        dormir(1000);
    }
    return NULL;
}

void *ThreadEsperaTempoCompra(void *pessoa){
    ClienteStruct *cliente = (ClienteStruct *)pessoa;
    
    if(cliente->nome == NULL){
        printf("\n\n\t[red]ERRO: Pessoa Nula[/red]\n");
        exit(1);
    }  
    dormir(cliente->tempoEstimadoCompra);
    if(Opcoes.VerTransacoes == 1){
        char tempoEstimadoCompra[9];
        formatTime(cliente->tempoEstimadoCompra, tempoEstimadoCompra);
        printc("\n[yellow]Fim Tempo Compra:[/yellow]\n [blue]%s[/blue] acabou de comprar todos os produtos em [green]%s[/green]\n",cliente->nome, tempoEstimadoCompra);
    }
    pthread_mutex_lock(&PessoasAcabaramTempoDeCompraLock);
    AddElementoFim(Global.PessoasAcabaramTempoDeCompra, criarElemento(cliente));
    pthread_mutex_unlock(&PessoasAcabaramTempoDeCompraLock);
    return NULL;
}

void changeStateThreadGlobal(){
    if(Opcoes.lojaAberta == 0 && menuvalidarCaixaFuncionarios()){
        Opcoes.lojaAberta = 1;
        pthread_t GlobalThread;

        pthread_mutex_lock(&PessoasAcabaramTempoDeCompraLock);
        if(Global.PessoasAcabaramTempoDeCompra == NULL){
            Global.PessoasAcabaramTempoDeCompra = criarLista();
        }
        pthread_mutex_unlock(&PessoasAcabaramTempoDeCompraLock);

        if (pthread_create(&GlobalThread, NULL, ThreadGlobal, NULL) != 0){
            printc("[red]Erro[/red] ao criar thread global!!!\n");
            exit(1);
        } 
    }
    else if(Opcoes.lojaAberta == 1){
        fechamentoLoja();
        //!antes de poderes destruir o historico, todas as pessoas da caixaas tem de ser atendidas ou removidas
        //!destruirHistoricos();
    }
}

void *ThreadSchedule(){
    int flag = 1;
    DataStruct dataAnterior = formatTimeStruct(tempoEmMilisegundos);
    while (1){
        
        DataStruct dataAtual = formatTimeStruct(tempoEmMilisegundos);
        if (flag){
            dataAnterior = dataAtual;
            flag = 0;
        }
        /* if (dataAtual.segundo % 10 == 0 && dataAnterior.segundo != dataAtual.segundo){
           struct stat st;
            stat("Historico", &st) == 0 ? (void)NULL : mkdir("Historico"); // retorna 0 se existir
            dataAnterior.segundo = formatTimeStruct(tempoEmMilisegundos).segundo;
            printc("\n\n\t[green]Hora: %d:%d:%d[/green]", dataAtual.hora, dataAtual.minuto, dataAtual.segundo); 
            char dataString[100];
            sprintf(dataString, "Historico/Data_%d-%d-%d_%d_%d_%d", dataAtual.dia, dataAtual.mes, dataAtual.ano, dataAtual.hora, dataAtual.minuto, dataAtual.segundo);
            printf("%s\n", dataString);
            stat(dataString, &st) == 0 ?  (void)NULL : mkdir(dataString);
            char imgsString[100];
            sprintf(imgsString, "%s/imgs", dataString);
            printf("%s\n", imgsString);
            stat(imgsString, &st) == 0 ?  (void)NULL : mkdir(imgsString); 
        } */

        if (dataAtual.minuto % 10 == 0 && dataAnterior.minuto != dataAtual.minuto){ // bater de 10 em 10 minutos
            dataAnterior.minuto = formatTimeStruct(tempoEmMilisegundos).minuto;
            printc("\n\n\n[red]Dados recolhidos[/red]");
            recolhaDadosEstatisticosHistoricoPeriodica(dataAnterior.hora, dataAnterior.minuto);
            printc("\n[red]Dados recolhidos 222222222[/red]");
        }
       
        if (dataAtual.dia % 1 == 0 && dataAnterior.dia != dataAtual.dia){ // bater de 1 em 1 dia
            printf("dataAtual.dia: %d e dataAnterior.dia: %d", dataAtual.dia, dataAnterior.dia);
            dataAnterior.dia = formatTimeStruct(tempoEmMilisegundos).dia;
            printf("dataAtual.dia: %d e dataAnterior.dia: %d", dataAtual.dia, dataAnterior.dia);
            struct stat st;
            stat("Historico", &st) == 0 ? (void)NULL : mkdir("Historico"); // retorna 0 se existir
            dataAnterior.segundo = formatTimeStruct(tempoEmMilisegundos).segundo;
            // printc("\n\n\t[green]Hora: %d:%d:%d[/green]", dataAtual.hora, dataAtual.minuto, dataAtual.segundo); 
            char dataString[100];
            sprintf(dataString, "Historico/Data_%d-%d-%d", dataAtual.dia, dataAtual.mes, dataAtual.ano);
            //printf("%s\n", dataString);
            stat(dataString, &st) == 0 ?  (void)NULL : mkdir(dataString);
            char imgsString[100];
            sprintf(imgsString, "%s/imgs", dataString);
            //printf("%s\n", imgsString);
            stat(imgsString, &st) == 0 ?  (void)NULL : mkdir(imgsString);
            printc("\n\n\n[red]Hora passada[/red]");
            
            calculosRecolhas();
            exportarHistoricoTransacoesParaTXT(dataString);
            exportarHistoricoTransacoesParaCSV(dataString);
            exportHistoricoDadosEstatisticosParaTXT(dataString);
            exportHistoricoDadosEstatisticosParaCSV(dataString);
            /* CriarGrafico(imgsString, HistoricoDados.mediaDiaria.tempoMedioEsperaTotal_CadaHora); */
            limparHistoricoTransacoes();
            destruirHistoricoDadosEstatisticos();
            initHistoricoDadosEstatisticos();
            printc("\n[red]Hora passada 222222222[/red]");
            /* *tempoMedioEsperaTotal_CadaHora,         //[24]
>>         *tempoMedioEspera_CadaCaixa,  *numeroMedioClienteFila_CadaHora,            //[24]
>>         *numeroMedioClienteFila_CadaCaixa,  *numeroMedioCaixasAbertas_CadaHora,*numeroMedioClienteSupermercado_CadaHora, */


            //Recolha de dados estatísticos
            /* recolhaDadosEstatisticosHistoricoTransacoes();
            calculosRecolhas(); */
            /* exportHistoricoTransacoes();
            exportHistoricoDadosEstatisticos(); */

            //Criação de gráfico
            //CriarGrafico(imgsString, int *X, int *Y);
            
            
            /* limparHistoricoTransacoes();
            destruirHistoricoDadosEstatisticos();
            initHistoricoDadosEstatisticos(); */
        } 

/* recolhaDadosEstatisticosHistoricoTransacoes();
calculosRecolhas();
exportarHistoricoTransacoesParaTXT("teste");
exportarHistoricoTransacoesParaCSV("teste");
exportHistoricoDadosEstatisticosParaTXT("teste");
exportHistoricoDadosEstatisticosParaCSV("teste");
CriarGrafico();
CriarGrafico();
CriarGrafico();
CriarGrafico();
limparHistoricoTransacoes();
destruirHistoricoDadosEstatisticos();
initHistoricoDadosEstatisticos(); */
    }
    return NULL;
}

void *threadTempo(){
    tempoEmMilisegundos = getCurrentTimeMillisecounds();
    while(1){
        tempoEmMilisegundos += 1000LL;
        dormir(1000);
    }
}

